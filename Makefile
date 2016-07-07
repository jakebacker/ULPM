#	    ULPM is a simple Unified Linux Package Manager with minimum requirements and works on all linux distributions.
#		Copyright (C) 2016  Jake Backer <jbacker42@gmail.com>

CXX?=g++
CXXFLAGS?=-Wall -Wextra -O2 -pipe

all: ulpm.cpp
	mkdir -p out
	$(CXX) ulpm.cpp $(CXXFLAGS) -o out/ulpm
	chmod +x out/ulpm

install: all
	install out/ulpm /usr/bin

uninstall:
	rm /usr/bin/ulpm

clean:
	rm out/ulpm
