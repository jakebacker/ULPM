all: ulpm.cpp
	g++ ulpm.cpp -o out/ulpm
	chmod +x out/ulpm
	sudo install out/ulpm /usr/bin

clean: 
	$(RM) out/ulpm

setup:
	mkdir out