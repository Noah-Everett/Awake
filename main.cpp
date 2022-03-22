#include <iostream>
#include <string>

using namespace std;

int main( int argc, char** argv )
{
    if( argc != 1 )
    {
        cout << "awake has no command line arguments (besides help (-h || --help))." << endl;
        cout << "If you encounter \"zsh: segmentation fault awake\", make sure the PASSWORD envornmental variable is set." << endl;

        return 0;
    }

    string password = getenv( "PASSWORD" );

    string on = "echo " + password + " | sudo -S pmset -a sleep 0 2>/dev/null && sudo pmset -a hibernatemode 0 2>/dev/null && sudo pmset -a disablesleep 1 2>/dev/null";
    string off = "echo " + password + " | sudo -S pmset -a sleep 1 2>/dev/null && sudo pmset -a hibernatemode 3 2>/dev/null && sudo pmset -a disablesleep 0 2>/dev/null";

    cout << "Turning sleep off with: sudo pmset -b sleep 0 && sudo pmset -a hibernatemode 0 && sudo pmset -a disablesleep 1" << endl;
    system( on.c_str() );

    cout << "Do not terminate program" << endl;
    cout << "Unplug Mac then enter anything to continue: ";
    string unpluged;
    cin >> unpluged;

    cout << "Turning sleep on with: sudo pmset -b sleep 1 && sudo pmset -a hibernatemode 3 && sudo pmset -a disablesleep 0" << endl;
    system( off.c_str() );

    cout << "Program ran successfully. Bye bye!" << endl;

    return 0;
}
