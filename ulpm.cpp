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

//This can be condensed
string getPackageManager () {
    if (hasProgram("apt-get")) {
        return "apt-get";
    } else if (hasProgram("deb")) {
        return "deb";
    } else if (hasProgram("dnf")) {
        return "dnf";
    } else if (hasProgram("pacman")) { //This will also have aur stuff
        return "pacman";
    } else if (hasProgram("dpkg")) {
        return "dpkg";
    } else if (hasProgram("aptitude")) {
        return "aptitude";
    } else if (hasProgram("rpm")) {
        return "rpm";
    } else if (hasProgram("fpm")) {
        return "fpm";
    } else if (hasProgram("wget")) {
        return "wget";
    } else if (hasProgram("curl")) {
        return "curl";
    } else {
        cout << "Cannot find package! Are you on Windows?" << endl;
    }
}

int main(int argc, char* argv[])
{
    for (int i=1; i<argc; i++) {
        args[i] = argv[i];
    }
    
    cout << getPackageManager() << endl;

    for (int i=1; i<argc; i++) {
        if (args[i][0] == '-') {
            cout << "Option: " << args[i] << endl;
        } else if (args[i] == "install") {
            cout << "Install: " << args[i + 1] << endl;
        }
    }

   return 0;
}
