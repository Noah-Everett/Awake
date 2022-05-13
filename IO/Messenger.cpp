#include "Messenger.hpp"

messager::messager( ostream& t_ostream, const string& welcome,
                    const string& file, const string& function, const int& line )
{

    m_ostream = &t_ostream;

    *m_ostream << welcome << endl;
    m_thread = new thread( &messager::outputMethod, this, "NOTICE", "Instance of \`messager\` class created.",
                           file, function, line );
}

messager::~messager()
{
    m_thread->join();
    delete m_thread;
}

void messager::print( const string& priority, const string& message,
                      const string& file, const string& function, const int& line )
{
    m_thread->join();
    *m_thread = thread( &messager::outputMethod, this, priority, message,
                        file, function, line );
}

void messager::outputMethod( const string& priority, const string& message,
                             const string& file, const string& function, const int& line )
{
    *m_ostream << priority << " <" << file << "::" << function
               << " (" << line << ")> : " << message << endl;
}
