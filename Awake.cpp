////////////////////////////////////////////////////////////////////////////////////
/// Awake                                                                        ///
/// by Noah Everett                                                              ///
///                                                                              ///
/// Awake is an application to keep your Mac awake while in clamshell mode.      ///
/// For more information, please visit https://github.com/Noah-Everett/Awake.    ///
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <time.h>

#include "CmdLnArgParser.hpp"
#include "Messenger.hpp"

using std::cout;
using std::string;
using std::vector;

using Base::CmdLnArgParser::parser;
using Base::Messenger::Verbosity::fatal_int;
using Base::Messenger::Verbosity::info_int;
using Base::Messenger::messenger_c;

// Function templates
string exec( string cmd );
bool isCharging();

// Constant messages
const string k_welcome = " ----------------------- \n"
                         "| Awake by Noah Everett |\n"
                         " ----------------------- \n ";
const string k_help    = "Program Usage (<> denotes required arguments, [] denotes optional arguments):\n"
                         "  awake [-h               -> display usage statement]\n"
                         "        [-p <password>    -> system password for sudo]\n"
                         "Other Information\n"
                         "  You must use either the -p <password> or set the PASSWORD environmental variable\n"
                         "  If you encounter \"zsh: segmentation fault awake\", make sure the PASSWORD environmental variable is set.";

// Global console messenger
namespace Base::Messenger {
messenger messenger_c( cout, k_welcome, LOCATION );
}

// Possible arguments
vector< string > optsWArg_req = {};
vector< string > optsWArg_opt = { "-p" };
vector< string > optsNArg_req = {};
vector< string > optsNArg_opt = { "-h", "--help" };

// User given arguments
string password;

int main( int argc, char** argv )
{
    ///////////////////////////////////////////////////////////////////////////////
    ///                         Command Line Arguments                          ///
    ///////////////////////////////////////////////////////////////////////////////
    parser parser( argc, argv, optsWArg_req, optsWArg_opt, optsNArg_req, optsNArg_opt );

    if( parser.hasOpt( "-h" ) || parser.hasOpt( "--help" ) ) {
        messenger_c( fatal_int, LOCATION ) << '\n' << k_help;
        return 0;
    }

    if( parser.hasOpt( "-p" ) )
        password = parser.getArg_string( "-p" );
    else
        password = getenv( "PASSWORD" );



    ///////////////////////////////////////////////////////////////////////////////
    ///                              Main Method                                ///
    ///////////////////////////////////////////////////////////////////////////////
    messenger_c( info_int, LOCATION ) << "Turning sleep off with: `sudo pmset -b sleep 0 && "
                                         "sudo pmset -a hibernatemode 0 && sudo pmset -a disablesleep 1`";
    exec( "echo " + password + " | sudo -S pmset -a sleep 0 2>/dev/null && sudo pmset -a hibernatemode 0 2>/dev/null && "
                               "sudo pmset -a disablesleep 1 2>/dev/null" );

    messenger_c( info_int, LOCATION ) << "Program will terminate when computer stops sharging.";
    time_t start, cur;
    time( &start );
    time( &cur );
    while( isCharging() && int( cur - start ) < 300 ) {
        time( &cur );
    }
    messenger_c( info_int, LOCATION ) << "Charging stopped.";

    messenger_c( info_int, LOCATION ) << "Turning sleep on with: `sudo pmset -b sleep 1 && "
                                         "sudo pmset -a hibernatemode 3 && "
                                         "sudo pmset -a disablesleep 0`";
    exec( "echo " + password + " | sudo -S pmset -a sleep 1 2>/dev/null && "
                               "sudo pmset -a hibernatemode 3 2>/dev/null && "
                               "sudo pmset -a disablesleep 0 2>/dev/null" );



    ///////////////////////////////////////////////////////////////////////////////
    ///                                End Program                              ///
    ///////////////////////////////////////////////////////////////////////////////
    messenger_c( info_int, LOCATION ) << "Program ran successfully. Bye bye!";

    return 0;
}

// Function declarations
string exec( string cmd ) {
    char buffer[ 256 ];
    string out = "";

    FILE* pipe = popen( cmd.c_str(), "r" );
    if( !pipe )
        return "\0";

    while( !feof( pipe ) )
        if( fgets( buffer, 256, pipe ) != NULL )
            out += buffer;

    pclose( pipe );
    return out;
}

bool isCharging() {
    string out = exec( "echo " + password + "| sudo -S pmset -g ps 2>/dev/null" );
    if( out.find( "discharging" ) != string::npos )
        return false;

    return true;
}
