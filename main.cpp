#include <iostream>
#include <string>

using namespace std;

int main( int argc, char** argv )
{
    string password = getenv( "PASSWORD" );
    if( password != getenv( "PASSWORD" ) )
    {
        cout << "Please set PASSWORD environmental variable" << endl;
        cout << "Example: export $PASSWORD=\"xxxx\"" << endl;

        return -1;
    }

    string on = "echo " + password + " | sudo -S pmset -b sleep 0 2>nul; echo " + password + " | sudo -S pmset -b disablesleep 0 2>nul";
    string off = "echo " + password + " | sudo -S pmset -b sleep 5 2>nul; echo " + password + " | sudo -S pmset -b disablesleep 0 2>nul";
    string unpluged;
    cout << "Turning sleep off with command: sudo pmset -b sleep 0; sudo pmset -b disablesleep 0" << endl;

    system( on.c_str() );

    cout << "Do not terminate program" << endl;
    cout << "Unplug Mac then enter anything to continue: ";
    cin >> unpluged;

    cout << "Turning sleep off with command: sudo pmset -b sleep 5; sudo pmset -b disablesleep 0" << endl;
    system( off.c_str() );

    cout << "Program ran successfully. Bye bye!" << endl;

    return 0;
}
