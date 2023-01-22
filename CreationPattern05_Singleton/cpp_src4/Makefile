
all: single_house_maker4.exe

run: all
	-./single_house_maker4.exe
	SELECT_HOUSEMAKER=elder ./single_house_maker4.exe
	SELECT_HOUSEMAKER=second ./single_house_maker4.exe
	SELECT_HOUSEMAKER=youngest ./single_house_maker4.exe
	-SELECT_HOUSEMAKER=wolf ./single_house_maker4.exe

clean:
	rm -fr single_house_maker4.exe

single_house_maker4.exe: single_house_maker4.cpp main.cpp
	g++ -o single_house_maker4.exe single_house_maker4.cpp main.cpp

