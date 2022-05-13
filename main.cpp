#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;

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

bool isCharging( const string& password ) {
    string out = exec( "echo " + password + "| sudo -S pmset -g ps 2>/dev/null" );
    if( out.find( "discharging" ) != string::npos )
        return false;

    return true;
}

int main( int argc, char** argv )
{
    if( argc != 1 )
    {
        cout << "awake has no command line arguments (besides help (-h || --help))." << endl;
        cout << "If you encounter \"zsh: segmentation fault awake\", make sure the PASSWORD envornmental variable is set." << endl;

        return 0;
    }

    string password = getenv( "PASSWORD" );

    cout << "Turning sleep off with: sudo pmset -b sleep 0 && sudo pmset -a hibernatemode 0 && sudo pmset -a disablesleep 1" << endl;
    string out = exec( "echo " + password + " | sudo -S pmset -a sleep 0 2>/dev/null && sudo pmset -a hibernatemode 0 2>/dev/null && sudo pmset -a disablesleep 1 2>/dev/null" );

    cout << "Program will terminate when computer stops sharging." << endl;
    while( isCharging( password ) ) {}
    cout << "Charging stopped." << endl;

    cout << "Turning sleep on with: sudo pmset -b sleep 1 && sudo pmset -a hibernatemode 3 && sudo pmset -a disablesleep 0" << endl;
    exec( "echo " + password + " | sudo -S pmset -a sleep 1 2>/dev/null && sudo pmset -a hibernatemode 3 2>/dev/null && sudo pmset -a disablesleep 0 2>/dev/null" );

    cout << "Program ran successfully. Bye bye!" << endl;

    return 0;
}
