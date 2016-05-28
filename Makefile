#	    ULPM is a simple Unified Linux Package Manager with minimum requirements and works on all linux distributions.
#		Copyright (C) 2016  Jake Backer <jbacker42@gmail.com>

all: ulpm.cpp
	g++ ulpm.cpp -o out/ulpm
	chmod +x out/ulpm
	sudo install out/ulpm /usr/bin

clean: 
	$(RM) out/ulpm

setup:
	mkdir out