#    Copyright (C) 2016 Jake Richard Backer. All Rights Reserved.
#    DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#	 
#    This code is free software; you may not modify the software and/or
#    redistribute it under the terms of the BSD 3-Clause License only, as it is
#    published by the University of California, Berkeley.
#    
#    This code is distributed WITHOUT the
#    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
#    See the BSD 3-Clause License for more details (a copy is
#    included in the LICENSE file that accompanied this code).
#    
#    Please contact the author, Jake Backer, at <jbacker42@gmail.com> with any
#    questions.

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
	$(RM) out/ulpm
