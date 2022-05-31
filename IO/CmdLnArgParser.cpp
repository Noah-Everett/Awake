#include "CmdLnArgParser.hpp"
#include "Messenger.hpp"

using std::invalid_argument;
using std::find;

string ctos( char* cstr )
{
    string str( cstr );

    return str;
}

parser::parser( int t_argc, char** t_argv,
                const vector< string >& t_optsWArg_req, const vector< string >& t_optsWArg_opt,
                const vector< string >& t_optsNArg_req, const vector< string >& t_optsNArg_opt )
{
    m_optsWArg_req = t_optsWArg_req;
    m_optsWArg_opt = t_optsWArg_opt;
    m_optsNArg_req = t_optsNArg_req;
    m_optsNArg_opt = t_optsNArg_opt;

    // Read opts and args into member (m) data, checking for opt arg pair validity
    messenger_c( k_pNotice, LOCATION ) << "Parsing command line arguments.";
    for( int i = 1; i < t_argc; i++ ) { // exclude i = 0 (exe path)
        if( t_argv[ i ][ 0 ] == '-' )
            m_optsArgs.push_back( { t_argv[ i ], "" } );
        else {
            if( ( --m_optsArgs.end() )->arg == "" ) // If option doesn't have argument
                ( --m_optsArgs.end() )->arg = t_argv[ i ];
            else if( ( --m_optsArgs.end() )->arg.back() == '\\' ) { // Catch directories with "abc\ def"
                ( --m_optsArgs.end() )->arg.erase( ( --m_optsArgs.end() )->arg.size() - 1 ) += " " + string( t_argv[ i ] );
            } else { // If last option alread has argument
                messenger_c( k_pFatal, LOCATION ) << "Missing option for command line argument \"" << t_argv[ i ] << "\".";
                throw invalid_argument( "Missing option for command line argument \"" + ctos( t_argv[ i ] ) + "\"." );
            }
        }
    }

    // Check all opts are valid options
    for( optArg m_optArg : m_optsArgs ) {
        if( find( m_optsWArg_req.begin(), m_optsWArg_req.end(), m_optArg.opt ) == m_optsWArg_req.end() &&
            find( m_optsWArg_opt.begin(), m_optsWArg_opt.end(), m_optArg.opt ) == m_optsWArg_opt.end() &&
            find( m_optsNArg_req.begin(), m_optsNArg_req.end(), m_optArg.opt ) == m_optsNArg_req.end() &&
            find( m_optsNArg_opt.begin(), m_optsNArg_opt.end(), m_optArg.opt ) == m_optsNArg_opt.end() ) {
            messenger_c( k_pFatal, LOCATION ) << "Unknown command line option \"" << m_optArg.opt << "\".";
            throw invalid_argument( "Unknown command line option \"" + m_optArg.opt + "\"." );
        } else if( m_optArg.arg == "" &&
                   find( m_optsNArg_req.begin(), m_optsNArg_req.end(), m_optArg.opt ) == m_optsNArg_req.end() &&
                   find( m_optsNArg_opt.begin(), m_optsNArg_opt.end(), m_optArg.opt ) == m_optsNArg_opt.end() ) {
            messenger_c( k_pFatal, LOCATION ) << "Missing argument for command line option \"" << m_optArg.opt << "\".";
            throw invalid_argument( "Missing argument for command line option \"" + m_optArg.opt + "\"." );
        } else if( m_optArg.arg != "" &&
                   find( m_optsWArg_req.begin(), m_optsWArg_req.end(), m_optArg.opt ) == m_optsWArg_req.end() &&
                   find( m_optsWArg_opt.begin(), m_optsWArg_opt.end(), m_optArg.opt ) == m_optsWArg_opt.end() ) {
            messenger_c( k_pFatal, LOCATION ) << "Given argument for command line option \"" << m_optArg.opt
                                                             << "\" which should not have an argument.";
            throw invalid_argument( "Given argument for command line option \"" + m_optArg.opt +
                                    "\" which should not have an argument." );
        }
    }

    // Check all required opts are present
    for( string opt : m_optsWArg_req )
        if( find( m_optsWArg_req.begin(), m_optsWArg_req.end(), opt ) == m_optsWArg_req.end() &&
            find( m_optsNArg_req.begin(), m_optsNArg_req.end(), opt ) == m_optsNArg_req.end() ) {
            messenger_c( k_pFatal, LOCATION ) << "Missing required command line option \"" + opt + "\".";
            throw invalid_argument( "Missing reqwuired command line option \"" + opt + "\"." );
        }
}

parser::~parser()
{
}

bool parser::hasOpt( const string& opt ) const
{
    for( optArg m_optArg : m_optsArgs )
        if( m_optArg.opt == opt )
            return true;

    return false;
}

bool parser::getArg_bool( const string& opt ) const
{
    for( optArg m_optArg : m_optsArgs )
        if( m_optArg.opt == opt ) {
            if( m_optArg.arg == "true" || m_optArg.arg == "TRUE" )
                return true;
            else if( m_optArg.arg == "false" || m_optArg.arg == "FALSE" )
                return false;
            else {
                messenger_c( k_pFatal, LOCATION ) << "\"" << m_optArg.opt << "\" should have a boolean argument. It does not.";
                throw invalid_argument( "\"" + m_optArg.opt + "\" should have a boolean argument. It does not." );
            }
        }

    messenger_c( k_pFatal, LOCATION ) << "Missing command line option \"" << opt << "\".";
    throw invalid_argument( "Missing command line option \"" + opt + "\"." );
}

int parser::getArg_int( const string& opt ) const
{
    for( optArg m_optArg : m_optsArgs )
        if( m_optArg.opt == opt )
            return stoi( m_optArg.arg );

    messenger_c( k_pFatal, LOCATION ) << "Missing command line option \"" << opt << "\".";
    throw invalid_argument( "Missing command line option \"" + opt + "\"." );
}

string parser::getArg_string( const string& opt ) const
{
    for( optArg m_optArg : m_optsArgs )
        if( m_optArg.opt == opt )
            return m_optArg.arg;

    messenger_c( k_pFatal, LOCATION ) << "Missing command line option \"" << opt << "\".", LOCATION;
    throw invalid_argument( "Missing command line option \"" + opt + "\"." );
}

string parser::getOptsArgs_string() const
{
    string out = "User given command line options and arguments (-option argument):";

    for( optArg m_optArg : m_optsArgs )
        out += "\n  " + m_optArg.opt + " " + m_optArg.arg;

    return out;
}
