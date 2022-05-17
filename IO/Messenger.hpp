#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <iostream>
#include <string>
#include <thread>

using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::thread;

#define LOCATION __FILE__, __FUNCTION__, __LINE__

const string k_pNull    = "";
const string k_pInfo    = "INFO";
const string k_pNotice  = "NOTICE";
const string k_pWarning = "WARNING";
const string k_pError   = "ERROR";
const string k_pFatal   = "FATAL";

class messenger {
    public:
        messenger( ostream& t_ostream = cout, const string& welcome = "",
                  const string& file = __FILE__, const string& function = __FUNCTION__, const int& line = __LINE__ );
       ~messenger();

        void print( const string& priority, const string& message,
                    const string& file, const string& function, const int& line );

    private:
        ostream* m_ostream;
        thread* m_thread;

        void outputMethod( const string& priority, const string& message,
                           const string& file, const string& function, const int& line );
};

extern messenger messenger_c;

#endif
