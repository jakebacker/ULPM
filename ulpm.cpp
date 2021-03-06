/*
    Copyright (C) 2016 Jake Richard Backer. All Rights Reserved.
    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This code is free software; you may not modify the software and/or
    redistribute it under the terms of the BSD 3-Clause License only, as it is
    published by the University of California, Berkeley.
    
    This code is distributed WITHOUT the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the BSD 3-Clause License for more details (a copy is
    included in the LICENSE file that accompanied this code).
    
    Please contact the author, Jake Backer, at <jbacker42@gmail.com> with any
    questions.
*/

#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

string args[10];

string packMan; // lol
string newPackMan;

int packOut;

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
    } else {
        cout << "No standard package manager. Skipping..." << endl;
        return "none";
    }
}

string getBasicCommand (int argc, string commands[]) {
    if (packMan == "apt") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo apt-get -y install " + commands[i].substr(9);
                return command;
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo apt-get -y remove " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 7) == "Update") {
                return "sudo apt-get -y update";
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo apt-get -y upgrade " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "apt-cache depends " + commands[i].substr(6);
                return command;
            }
        }
        
    } else if (packMan == "dnf") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo dnf -y install " + commands[i].substr(9);
                return command;
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo dnf -y remove " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 7) == "Update") {
                return "sudo dnf -y distro-sync";
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo dnf -y upgrade " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "dnf repoquery --requires " + commands[i].substr(6); 
                return command;
            }
        }
    } else if (packMan == "pacman") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                string command = "sudo pacman --noconfirm -S " + commands[i].substr(9);
                return command;
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo pacman --noconfirm -R " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 7) == "Update") {
                return "sudo pacman -Syu";
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo pacman --noconfirm -U " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "pacman -Qi " + commands[i].substr(6) + " |grep Depends";
                return command;
            }
        }
    } else if (packMan == "aptitude") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0, 9) == "Install: ") {
                cout << "####################### WARNING #######################" <<
                endl << "aptitude has a know bug with versions older than 0.7.6-1 which will cause ULPM to inproperly work." <<
                endl << "USE AT YOUR OWN RISK" << endl;
                string command = "sudo aptitude -y install " + commands[i].substr(9);
                return command;
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo aptitude -y remove " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 7) == "Update") {
                return "sudo aptitude -y update&&sudo aptitude -y full-upgrade";
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo aptitude -y install " + commands[i].substr(8);   
                return command;
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "aptitude -q show " + commands[i].substr(6) + " |grep Depends"; //Not working
                //return command;
            }
        }
    } else if (packMan == "solus") {
        for (int i=0; i < argc; i++) {
            if (commands[i].substr(0,9) == "Install: ") {
                string command = "sudo eopkg it " + commands[i].substr(9);
                return command;
            } else if (commands[i].substr(0, 8) == "Remove: ") {
                string command = "sudo eopkg rm " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 7) == "Update") {
                return "sudo eopkg ur";
            } else if (commands[i].substr(0, 8) == "Upgrade: ") {
                string command = "sudo eopkg up " + commands[i].substr(8);
                return command;
            } else if (commands[i].substr(0, 6) == "Deps: ") {
                string command = "eopkg info " + commands[i].substr(6) + "|grep Dependencies";
                return command;
            }
        }
    }
    return "invalid";
}


string getNewPackMan() {
    if (packOut != 0) {
        if (packMan == "apt") {
            packMan = "dnf";
            if (hasProgram("dnf")) {
                return "dnf";   
            } else {
                return "new";
            }
        } else if (packMan == "dnf") {
            packMan = "pacman";
            if (hasProgram("pacman")) {
                return "pacman";
            } else {
                return "new";
            }
        } else if (packMan == "pacman") {
            packMan = "aptitude";
            if (hasProgram("aptitude")) {
                return "aptitude";
            } else {
                return "new";
            }
        } else if (packMan == "aptitude") {
            packMan = "solus";
            if (hasProgram("eopkg")) {
                return "solus";
            } else {
                return "new";
            }
        } else if (packMan == "solus") {
            packMan = "none";
            return "none";
        } else {
            packMan = "err";
            return "err";
        }
        
    }
    
    return "ok";
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
    
    //This will be changed
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
    
    runBasicCommand:
    packOut = system(getBasicCommand(argc, commands).c_str());
    cout << packOut << endl;
    
    newPack:
    newPackMan = getNewPackMan();
    
    cout << newPackMan << endl;
    
    if (newPackMan == "new") {
        goto newPack;
    }
    
    if (newPackMan == "none") {
        cout << "No standard package manager" << endl;
        return 1;
    }
    
    if (newPackMan != "ok") {
        packMan = newPackMan;
        goto runBasicCommand; // TODO: Remove this goto statment and the label
    } else {
        return 0;
    }
    
    
    return 0;
}