#include <iostream>

using namespace std;

string args[10];

int main(int argc, char* argv[])
{
    for (int i=1; i<argc; i++) {
        args[i] = argv[i];
    }

    for (int i=1; i<argc; i++) {
        if (args[i][0] == '-') {
            cout << "Option: " << args[i] << endl;
        } else if (args[i] == "install") {
            cout << "Install: " << args[i + 1] << endl;
        }
    }

   return 0;
}

