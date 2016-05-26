all: ulpm.cpp
	g++ ulpm.cpp -o out/ulpm
	chmod +x out/ulpm

clean: 
	$(RM) out/ulpm

setup:
	mkdir out