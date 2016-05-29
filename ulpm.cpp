/*
    ULPM is a simple Unified Linux Package Manager with minimum requirements and works on all linux distributions.
    Copyright (C) 2016  Jake Backer <jbacker42@gmail.com>
*/

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
            
            commands[i] = "Option: " + args[i];
            cout << commands[i] << endl;
            
        } else if (args[i] == "install") {
            
            commands[i] = "Install: " + args[i + 1];
            cout << commands[i] << endl;
            
        } else if (args[i] == "remove") {
            
            commands[i] = "Remove: " + args[i + 1];
            cout << commands[i] << endl;
            
        } else if (args[i] == "upgrade") {
            
            commands[i] = "Upgrade";
            cout << commands[i] << endl;
            
        } else if (args[i] == "update") {
            
            commands[i] = "Update: " + args[i + 1];
            cout << commands[i] << endl;
            
        } else if (args[i] == "dependencies") {
            
            commands[i] = "Deps: " + args[i + 1];
            cout << commands[i] << endl;
            
        }
    }
    
    for (int i=1; i < argc; i++) {
        cout << commands[i] << endl;
    }

    if (packMan == "apt") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo apt-get -y -qq install " + commands[i].substr(9);
                system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo apt-get -y -qq remove " + commands[i].substr(8);
                system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Upgrade") {
                system ("sudo apt-get -y -qq update"); //Yes, this is correect
            } else if (commands[i].substr(0, 8) == "Update: ") {
                string command = "sudo apt-get -y -qq upgrade " + commands[i].substr(8);
                system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "apt-cache depends " + commands[i].substr(6);
                system (command.c_str());
            }
        }
    } else if (packMan == "dnf") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo dnf -yq install " + commands[i].substr(9);
                system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo dnf -yq remove " + commands[i].substr(8);
                system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Upgrade") {
                system ("sudo dnf -yq distro-sync");
            } else if (commands[i].substr(0, 8) == "Update: ") {
                string command = "sudo dnf -yq upgrade " + commands[i].substr(8);
                system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "rpm -qR " + commands[i].substr(6);
                system (command.c_str());
            }
        }
    }
    
   return 0;
}
