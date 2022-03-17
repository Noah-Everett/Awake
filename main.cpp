#include <iostream>
#include <string>

using namespace std;

int main( int argc, char** argv )
{
    for( int i = 0; i < argc; i++ )
        if( strcmp( argv[ i ], "-h" ) == 0 || strcmp( argv[ i ], "--help" ) == 0 )
        {
            cout << "awake has no command line arguments (besides help)." << endl;
            cout << "If you encounter PUT ERROR HERE, make sure the PASSWORD envornmental variable is set."

            return 0;
        }

    string password = getenv( "PASSWORD" );
    if( password != getenv( "PASSWORD" ) ) // this will never run as is PASSWORD is not set the resulting error will terminate the program
    {
        cout << "Please set PASSWORD environmental variable" << endl;
        cout << "Example: export $PASSWORD=\"xxxx\"" << endl;

        return -1;
    }

    string on = "echo " + password + " | sudo -S pmset -b sleep 0 2>/dev/null; echo " + password + " | sudo -S pmset -b disablesleep 0 2>/dev/null";
    string off = "echo " + password + " | sudo -S pmset -b sleep 5 2>/dev/null; echo " + password + " | sudo -S pmset -b disablesleep 0 2>/dev/null";

    cout << "Turning sleep off with command: sudo pmset -b sleep 0; sudo pmset -b disablesleep 0" << endl;
    system( on.c_str() );

    cout << "Do not terminate program" << endl;
    cout << "Unplug Mac then enter anything to continue: ";
    string unpluged;
    cin >> unpluged;

    cout << "Turning sleep off with command: sudo pmset -b sleep 5; sudo pmset -b disablesleep 0" << endl;
    system( off.c_str() );

    cout << "Program ran successfully. Bye bye!" << endl;

    return 0;
}
