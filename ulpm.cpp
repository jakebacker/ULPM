#include <iostream>
#include <cstdlib>

using namespace std;

string args[10];

bool hasProgram (string program) {
    string command = "which " + program;
    if (system(command.c_str()) == 0) {
        return true;
    } else {
        return false;
    }
}

//WINDOWS VERSION
int main(int argc, char* argv[])
{
    for (int i=1; i<argc; i++) {
        args[i] = argv[i];
    }

    for (int i=1; i<argc; i++) {
        if (args[i][0] == '-') {
            cout << "Option: " << args[i] << endl;
        } else if (args[i] == "install") {
            if (!hasProgram(args[i+1])){
                cout << "Install: " << args[i + 1] << endl;
            }
        }
    }

   return 0;
}

