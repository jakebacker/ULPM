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

string getBasicCommand (string commands[]) {
	if (packMan == "apt") {
		
		if (commands[1].substr(0, 9) == "Install: ") {
			string command = "sudo apt-get -y install " + commands[1].substr(9);
			return command;
		} else if (commands[1].substr(0, 8) == "Remove: ") {
			string command = "sudo apt-get -y remove " + commands[1].substr(8);
			return command;
		} else if (commands[1].substr(0, 7) == "Update") {
			return "sudo apt-get -y update";
		} else if (commands[1].substr(0, 7) == "Upgrade") {
			string command = "sudo apt-get -y upgrade";
			return command;
		} else if (commands[1].substr(0, 6) == "Deps: ") {
			string command = "apt-cache depends " + commands[1].substr(6);
			return command;
		}
		
	} else if (packMan == "dnf") {
		
		if (commands[1].substr(0, 9) == "Install: ") {
			string command = "sudo dnf -y install " + commands[1].substr(9);
			return command;
		} else if (commands[1].substr(0, 8) == "Remove: ") {
			string command = "sudo dnf -y remove " + commands[1].substr(8);
			return command;
		} else if (commands[1].substr(0, 7) == "Update") {
			return "sudo dnf -y distro-sync";
		} else if (commands[1].substr(0, 7) == "Upgrade") {
			string command = "sudo dnf -y upgrade";
			return command;
		} else if (commands[1].substr(0, 6) == "Deps: ") {
			string command = "dnf repoquery --requires " + commands[1].substr(6); 
			return command;
		}
			
	} else if (packMan == "pacman") {
		
		if (commands[1].substr(0, 9) == "Install: ") {
			string command = "sudo pacman --noconfirm -S " + commands[1].substr(9);
			return command;
		} else if (commands[1].substr(0, 8) == "Remove: ") {
			string command = "sudo pacman --noconfirm -R " + commands[1].substr(8);
			return command;
		} else if (commands[1].substr(0, 7) == "Update") {
			return "sudo pacman -Syu";
		} else if (commands[1].substr(0, 7) == "Upgrade") {
			string command = "sudo pacman --noconfirm -U";
			return command;
		} else if (commands[1].substr(0, 6) == "Deps: ") {
			string command = "pacman -Qi " + commands[1].substr(6) + " |grep Depends";
			return command;
		}
			
	} else if (packMan == "aptitude") {
		
		if (commands[1].substr(0, 9) == "Install: ") {
			
			cout << "####################### WARNING #######################" <<
			endl << "aptitude has a know bug with versions older than 0.7.6-1 which will cause ULPM to inproperly work." <<
			endl << "USE AT YOUR OWN RISK" << endl;
			
			string command = "sudo aptitude -y install " + commands[1].substr(9);
			return command;
		} else if (commands[1].substr(0, 8) == "Remove: ") {
			string command = "sudo aptitude -y remove " + commands[1].substr(8);
			return command;
		} else if (commands[1].substr(0, 7) == "Update") {
			return "sudo aptitude -y update&&sudo aptitude -y full-upgrade"; // This isnt either
		} else if (commands[1].substr(0, 7) == "Upgrade") {
			string command = "sudo aptitude -y install"; // This is not right 
			return command;
		} else if (commands[1].substr(0, 6) == "Deps: ") {
			string command = "aptitude -q show " + commands[1].substr(6) + " |grep Depends"; //Not working
			//return command;
		}
			
	} else if (packMan == "solus") {
		
		if (commands[1].substr(0,9) == "Install: ") {
			string command = "sudo eopkg it " + commands[1].substr(9);
			return command;
		} else if (commands[1].substr(0, 8) == "Remove: ") {
			string command = "sudo eopkg rm " + commands[1].substr(8);
			return command;
		} else if (commands[1].substr(0, 7) == "Update") {
			return "sudo eopkg ur";
		} else if (commands[1].substr(0, 7) == "Upgrade") {
			string command = "sudo eopkg up";
			return command;
		} else if (commands[1].substr(0, 6) == "Deps: ") {
			string command = "eopkg info " + commands[1].substr(6) + "|grep Dependencies";
			return command;
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

string getPythonPackage(string commands[]) {
	if (commands[1].substr(0, 9) == "Install: ") {
		string command = "sudo pip install " + commands[1].substr(9);
		return command;
	} else if (commands[1].substr(0, 8) == "Remove: ") {
		string command = "sudo pip uninstall " + commands[1].substr(8);
		return command;
	} else if (commands[1].substr(0, 7) == "Update") {
		return "invalid";
	} else if (commands[1].substr(0, 7) == "Upgrade") {
		return "invalid";
	} else if (commands[1].substr(0, 6) == "Deps: ") {
		return "invalid"; // Currently no good way to do this
	} else {
		return "err";
	}
}

string getRubyPackage(string commands[]) {
	if (commands[1].substr(0, 9) == "Install: ") {
		string command = "sudo gem install " + commands[1].substr(9);
		return command;
	} else if (commands[1].substr(0, 8) == "Remove: ") {
		string command = "sudo gem uninstall " + commands[1].substr(8);
		return command;
	} else if (commands[1].substr(0, 7) == "Update") {
		return "invalid";
	} else if (commands[1].substr(0, 7) == "Upgrade") {
		return "sudo gem update `gem list | cut -d ' ' -f 1`";
	} else if (commands[1].substr(0, 6) == "Deps: ") {
		string command = "sudo gem dependency " + commands[1].substr(9);
		return command;
	} else {
		return "err";
	}
}

string getNpmPackage(string commands[]) {
	if (commands[1].substr(0, 9) == "Install: ") {
		string command = "sudo npm install " + commands[1].substr(9);
		return command;
	} else if (commands[1].substr(0, 8) == "Remove: ") {
		string command = "sudo npm remove " + commands[1].substr(8);
		return command;
	} else if (commands[1].substr(0, 7) == "Update") {
		return "invalid";
	} else if (commands[1].substr(0, 7) == "Upgrade") {
		return "sudo npm update -g`";
	} else if (commands[1].substr(0, 6) == "Deps: ") {
		string command = "sudo npm view " + commands[1].substr(9) + " dependencies";
		return command;
	} else {
		return "err";
	}
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
		cout << argv[i] << endl;
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
		if (args[i] == "install") {
			commands[i] = "Install: " + args[i + 1];
			cout << commands[i] << endl;
			break;
		} else if (args[i] == "remove") {
			commands[i] = "Remove: " + args[i + 1];
			cout << commands[i] << endl;
			break;
		} else if (args[i] == "upgrade") {
			commands[i] = "Upgrade";
			cout << commands[i] << endl;
			break;
		} else if (args[i] == "update") {
			commands[i] = "Update" + args[i + 1];
			cout << commands[i] << endl;
			break;
		} else if (args[i] == "dependencies") {
			commands[i] = "Deps: " + args[i + 1];
			cout << commands[i] << endl;
			break;
		}
	}
	
	for (int i=1; i < argc; i++) {
		cout << commands[i] << endl;
	}
	
	
	
	
	runBasicCommand:
	
	
	if (commands[1].substr(0, 6) == "Update" || commands[1].substr(0, 7) == "Upgrade") {
		while (newPackMan != "none") {
			cout << packMan << endl;
			cout << newPackMan << endl;
			
			string command = getBasicCommand(commands);
			
			if (command == "invalid") {
				cout << "Invalid parameter!!!" << endl;
				return 200; // Invalid command
			}
			
			packOut = system(command.c_str());
			
			packOut = 25000; // Spoofing an error for now
			
			cout << packOut << endl;
			
			upNewPackMan:
			newPackMan = getNewPackMan();
			cout << newPackMan << endl;
			
			if (newPackMan == "new") {
				goto upNewPackMan; // STOP WITH THE GOTOS!!!
			}
			
			if (newPackMan == "none") {
				break;
			}
			
			if (newPackMan != "ok") {
				packMan = newPackMan;
			} else {
				break;
			}
		}
		return 0;
	} else {
		
		string command = getBasicCommand(commands);
		if (command == "invalid") {
			cout << "Invalid parameter!!!" << endl;
			return 200; // Invalid command
		}
		packOut = system(command.c_str());
	}
	
	cout << packOut << endl;
	
	newPack:
	newPackMan = getNewPackMan();
	
	cout << newPackMan << endl;
	
	if (newPackMan == "new") {
		goto newPack;
	}
	
	if (newPackMan == "none") {
		cout << "No standard package manager" << endl;
		
		// pip, gem, and npm code here
		
		bool needNewPackMan = false;
		
		if (hasProgram("pip")) {
			string command = getPythonPackage(commands);
			
			if (command == "invalid") {
				cout << "This command is invalid for pip" << endl;
				packOut = 25000; // This is to show that there is an error and to continue with other package managers
			} else {
				packOut = system(command.c_str());
				cout << packOut << endl;
			}
			
			if (packOut != 0) {
				needNewPackMan = true;
			} else {
				return 0;
			}
		} else {
			needNewPackMan = true;
		}
		
		if (needNewPackMan == true && hasProgram("gem")) {
			
			needNewPackMan = false;
			string command = getRubyPackage(commands);
			
			if (command == "invalid") {
				cout << "This command is invalid for gem" << endl;
				packOut = 25000;
			} else {
				packOut = system(command.c_str());
				cout << packOut << endl;
			}
			
			if (packOut != 0) {
				needNewPackMan = true;
			} else {
				return 0;
			}
		} else {
			needNewPackMan = true;
		}
		
		if (needNewPackMan == true && hasProgram("npm")) {
			
			needNewPackMan = false;
			string command = getNpmPackage(commands);
			
			if (command == "invalid") {
				cout << "This command is invalid for npm" << endl;
				packOut = 25000;
			} else {
				packOut = system(command.c_str());
				cout << packOut << endl;
			}
			
			if (packOut != 0) {
				needNewPackMan = true;
			} else {
				return 0;
			}
		} else {
			needNewPackMan = true;
		}
		
		if (needNewPackMan == true) {
			return 1; // Placeholder
		}
		
	}
	
	if (newPackMan != "ok") {
		packMan = newPackMan;
		goto runBasicCommand; // TODO: Remove this goto statment and the label
	} else {
		return 0;
	}
	
	
	return 0;
}