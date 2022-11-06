
all: wolf_attack.exe

run: all
	wolf_attack.exe

clean:
	rm -fr wolf_attack.exe

wolf_attack.exe: wolf_attack.cpp chain_of_responsibility3.h
	g++ -o wolf_attack.exe wolf_attack.cpp

wolf_attack.cpp: chain_of_responsibility3.h
