#include <chrono>
#include <math.h>

#include "Messenger.hpp"

using std::endl;

messenger::messenger( ostream& t_ostream, const string& t_welcome,
                      const string& t_file, const string& t_function, const int& t_line )
{
    m_ostream = &t_ostream;

    *m_ostream << t_welcome << endl;
    m_thread = new thread( &messenger::main, this );
    m_message_incomplete = { k_pNotice, "Instance of \`messager\` class created.",
                             t_file, t_function, t_line };
}

messenger::~messenger()
{
    m_queue.push( m_message_incomplete );
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
    m_end = true;
    m_thread->join();
    delete m_thread;
}

void messenger::main()
{
    while( !m_end ) {
        if( !m_queue.empty() ) {
            output( m_queue.front() );
            m_queue.pop();
        }
    }
}

void messenger::print( const string& t_priority, const string& t_message,
                       const string& t_file, const string& t_function, const int& t_line )
{
    m_queue.push( { t_priority, t_message,
                    t_file, t_function, t_line } );
}

messenger& messenger::operator()( const string& t_priority,
                                  const string& t_file, const string& t_function, const int& t_line )
{
    m_queue.push( m_message_incomplete );
    m_message_incomplete = { "", "", "", "", 0 };

    m_message_incomplete.m_priority = t_priority;
    m_message_incomplete.m_file = t_file;
    m_message_incomplete.m_function = t_function;
    m_message_incomplete.m_line = t_line;

    return *this;
}

void messenger::output( const string& t_priority, const string& t_message,
                        const string& t_file, const string& t_function, const int& t_line )
{
    *m_ostream << t_priority << " <" << t_file << "::" << t_function
               << " (" << t_line << ")> : " << t_message << endl;
}

void messenger::output( const message& t_message )
{
    *m_ostream << t_message.m_priority << " <" << t_message.m_file << "::" << t_message.m_function
               << " (" << t_message.m_line << ")> : " << t_message.m_message << endl;
}

messenger& messenger::operator<<( const int& t_message )
{
    int message_int = t_message;
    string message_str = "";

    int digits = 0;
    while( t_message / int( pow( 10, digits ) ) != 0 )
        ++digits;

    for( int i = digits - 1; i > -1 ; i-- ) {
        message_str += message_int / int( pow( 10, i ) ) + 48;
        message_int -= message_int / int( pow( 10, i ) ) * int( pow( 10, i ) );
    }

    m_message_incomplete.m_message += message_str;

    return *this;
}

messenger& messenger::operator<<( const double& t_message )
{
    // Integer
    int message_int = t_message;
    string message_str = "";

    int digits = 0;
    while( message_int / int( pow( 10, digits ) ) != 0 )
        ++digits;

    for( int i = digits - 1; i > -1 ; i-- ) {
        message_str += message_int / int( pow( 10, i ) ) + 48;
        message_int -= message_int / int( pow( 10, i ) ) * int( pow( 10, i ) );
    }

    // Decimal
    message_str += ".";
    double message_double = t_message - int( t_message );

    while( message_double > 0.1 ) {
        message_str += int( message_double * 10.0 ) + 48;
        message_double = message_double * 10.0 - floor( message_double * 10 );
    }

    m_message_incomplete.m_message += message_str;

    return *this;
}

messenger& messenger::operator<<( const pair< double, int >& t_message )
{
    // Integer
    int message_int = t_message.first;
    string message_str = "";

    int digits = 0;
    while( message_int / int( pow( 10, digits ) ) != 0 )
        ++digits;

    for( int i = digits - 1; i > -1 ; i-- ) {
        message_str += message_int / int( pow( 10, i ) ) + 48;
        message_int -= message_int / int( pow( 10, i ) ) * int( pow( 10, i ) );
    }

    // Decimal
    message_str += ".";
    double message_double = t_message.first - int( t_message.first );

    for( int i = 0; i < t_message.second && message_double > 0.1; i++ ) {
        message_str += int( message_double * 10.0 ) + 48;
        message_double = message_double * 10.0 - floor( message_double * 10 );
    }

    m_message_incomplete.m_message += message_str;

    return *this;
}

messenger& messenger::operator<<( const bool& t_message )
{
    if( t_message )
        m_message_incomplete.m_message += "1";
    else
        m_message_incomplete.m_message += "0";

    return *this;
}

//// This function and specifically the object it creates
//// are only used to avoid a link error
//void fixLinkError()
//{
//    messenger doNotUse;
//}