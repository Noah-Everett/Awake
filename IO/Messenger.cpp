#include "Messenger.hpp"

messenger::messenger( ostream& t_ostream, const string& welcome,
                      const string& file, const string& function, const int& line )
{
    m_ostream = &t_ostream;

    *m_ostream << welcome << endl;
    m_thread = new thread( &messenger::outputMethod, this, "NOTICE", "Instance of \`messager\` class created.",
                           file, function, line );
}

messenger::~messenger()
{
    m_thread->join();
    delete m_thread;
}

void messenger::print( const string& priority, const string& message,
                       const string& file, const string& function, const int& line )
{
    m_thread->join();
    *m_thread = thread( &messenger::outputMethod, this, priority, message,
                        file, function, line );
}

void messenger::outputMethod( const string& priority, const string& message,
                              const string& file, const string& function, const int& line )
{
    *m_ostream << priority << " <" << file << "::" << function
               << " (" << line << ")> : " << message << endl;
}
