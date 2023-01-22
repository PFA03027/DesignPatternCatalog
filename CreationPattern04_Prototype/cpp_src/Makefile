
all: three_pigs_house_type.exe

run: all
	./three_pigs_house_type.exe

clean:
	rm -fr three_pigs_house_type.exe

three_pigs_house_type.exe: three_pigs_house_type.cpp main.cpp
	g++ -o three_pigs_house_type.exe three_pigs_house_type.cpp main.cpp

three_pigs_house_type.cpp: house_design_prototype.hpp
three_pigs_house_type.cpp: three_pigs_house_type.hpp
main.cpp : house_design_prototype.hpp
main.cpp : three_pigs_house_type.hpp
