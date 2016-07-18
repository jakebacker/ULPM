/*
    Copyright (C) 2016 Jake Richard Backer. All Rights Reserved.
    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This code is free software; you may not modify the software and/or
    redistribute it under the terms of the BSD 3-Clause License only, as it is
    published by the University of California, Berkeley.
    
    This code is distributed with the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the BSD 3-Clause License for more details (a copy is
    included in the LICENSE file that accompanied this code).
    
    Please contact the author, Jake Backer, at <jbacker42@gmail.com> with any
    questions.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

string args[10];

string packMan; // lol
string out;

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
    } else if (hasProgram("aptitude")) {
        return "aptitude";
    /*} else if (hasProgram("fpm")) {
        return "fpm";*/
    } else if (hasProgram("eopkg")) {
        return "solus";
    } else if (hasProgram("wget")) {
        return "wget";
    } else {
        cout << "No standard package manager. Skipping..." << endl;
        return "none";
    }
}

string getPythonPackage() {
    return "null";
}

string getRubyPackage() {
    return "null";
}

string getNpmPackage() {
    return "null";
}

string wgetGet() {
    return "null";
}

string curlGet() {
    //This will be used in wget
    return "null";
}



int main(int argc, char* argv[])
{
    string commands[argc];
    
    for (int i=1; i<argc; i++) {
        args[i] = argv[i];
    }
    
    if (getPackageManager() == "none") {
        if (hasProgram("pip")) {
            packMan = "python";
        } else if (hasProgram("gem")) {
            packMan = "ruby";
        } else {
            return 1;
        }
    } else {
        packMan = getPackageManager();   
    }

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
            
            commands[i] = "Upgrade: ";
            cout << commands[i] << endl;
            
        } else if (args[i] == "update") {
            
            commands[i] = "Update" + args[i + 1];
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
                out = system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo apt-get -y -qq remove " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Update") {
                out = system ("sudo apt-get -y -qq update");
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo apt-get -y -qq upgrade " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "apt-cache depends " + commands[i].substr(6);
                out = system (command.c_str());
            }
        }
    } else if (packMan == "dnf") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo dnf -yq install " + commands[i].substr(9);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo dnf -yq remove " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Update") {
                out = system ("sudo dnf -yq distro-sync");
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo dnf -yq upgrade " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "dnf repoquery --requires " + commands[i].substr(6); 
                out = system (command.c_str());
            }
        }
    } else if (packMan == "pacman") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo pacman -q --noconfirm -S " + commands[i].substr(9);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo pacman -q --noconfirm -R " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Update") {
                out = system ("sudo pacman -q -Syu");
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo pacman -q --noconfirm -U " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "pacman -q -Qi " + commands[i].substr(6) + " |grep Depends";
                out = system (command.c_str());
            }
        }
    } else if (packMan == "aptitude") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo aptitude -yq install " + commands[i].substr(9);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo aptitude -yq remove " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Update") {
                out = system ("sudo aptitude -yq update");
                out = system ("sudo aptitude -yq full-upgrade");
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo aptitude -yq install " + commands[i].substr(8);   
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "aptitude -q show " + commands[i].substr(6) + " |grep Depends"; //Not working
            }
        }
    } else if (packMan == "solus") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0,9) == "Install: ") {
                string command = "sudo eopkg it " + commands[i].substr(9);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo eopkg rm " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 7) == "Update") {
                out = system ("sudo eopkg ur");
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo eopkg up " + commands[i].substr(8);
                out = system (command.c_str());
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "eopkg info " + commands[i].substr(6) + "|grep Dependencies";
                out = system (command.c_str());
            }
        }
    }
    
   return 0;
}
