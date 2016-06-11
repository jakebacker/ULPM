#	Copyright (C) 2016 Jake Richard Backer. All Rights Reserved.
#   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#
#   This code is free software; you may not modify the software although you may
#   redistribute it under the terms of the GNU General Public License version 2
#   only, as it is published by the Free Software Foundation.
#    
#   This code is distributed in the hope that it will be useful, but WITHOUT
#   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#   version 2 for more details (a copy is included in the LICENSE file that
#   accompanied this code).
#    
#   You should have received a copy of the GNU General Public License version
#   2 along with this work; if not, write to the Free Software Foundation,
#   Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
#    
#   Please contact the author, Jake Backer, at <jbacker42@gmail.com> with any
#   questions.

all: ulpm.cpp
	g++ ulpm.cpp -o out/ulpm
	chmod +x out/ulpm
	sudo install out/ulpm /usr/bin

clean: 
	$(RM) out/ulpm

setup:
	mkdir out