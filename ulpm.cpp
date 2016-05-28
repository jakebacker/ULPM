#include <iostream>
#include <cstdlib>

using namespace std;

string args[10];

string packMan; // lol

bool hasProgram (string program) {
    string command = "which " + program;
    if (system(command.c_str()) == 0) {
        return true;
    } else {
        return false;
    }
}

//This can be condensed
//Needs python and stuff like that
string getPackageManager () {
    if (hasProgram("apt-get")) {
        return "apt";
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
        cout << "Cannot find package manager! Are you on Windows?" << endl;
        return "none";
    }
}

int main(int argc, char* argv[])
{
    string commands[argc];
    
    for (int i=1; i<argc; i++) {
        args[i] = argv[i];
    }
    
    if (getPackageManager() == "none") {
        return 1;
    }
    
    packMan = getPackageManager();

    for (int i=1; i<argc; i++) {
        if (args[i][0] == '-') {
            cout << "Option: " << args[i] << endl;
            commands[i] = "Option: " + args[i];
        } else if (args[i] == "install") {
            cout << "Install: " << args[i + 1] << endl;
            commands[i] = "Install: " + args[i + 1];
        } else if (args[i] == "remove") {
            cout << "Remove: " << args[i + 1] << endl;
            commands[i] = "Remove: " + args[i + 1];
        } else if (args[i] == "upgrade") {
            cout << "Upgrade" << endl;
            commands[i] = "Upgrade";
        } else if (args[i] == "update") {
            cout << "Update: " << args[i + 1] << endl;
            commands[i] = "Update: " + args[i + 1];
        }
    }
    
    for (int i=1; i < argc; i++) {
        cout << commands[i] << endl;
    }

    
    
   return 0;
}
