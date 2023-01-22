
all: three_pigs_makers.exe

run: all
	./three_pigs_makers.exe

clean:
	rm -fr three_pigs_makers.exe

three_pigs_makers.exe: three_pigs_makers.cpp main.cpp
	g++ -o three_pigs_makers.exe three_pigs_makers.cpp main.cpp

three_pigs_makers.cpp: house_design_order_and_build.hpp
three_pigs_makers.cpp: three_pigs_makers.hpp
main.cpp : house_design_order_and_build.hpp
main.cpp : three_pigs_makers.hpp
