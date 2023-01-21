
all: stone_house_observer.exe

run: all
	./stone_house_observer.exe

clean:
	rm -fr stone_house_observer.exe

stone_house_observer.exe: stone_house_observer.cpp observer_pattern.h
	g++ -o stone_house_observer.exe stone_house_observer.cpp

stone_house_observer.cpp: observer_pattern.h
