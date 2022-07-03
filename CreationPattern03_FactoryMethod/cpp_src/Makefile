
all: three_pigs_makers.exe

run: all
	three_pigs_makers.exe

clean:
	rm -fr three_pigs_makers.exe

three_pigs_makers.exe: three_pigs_makers.cpp
	g++ -o three_pigs_makers.exe three_pigs_makers.cpp

three_pigs_makers.cpp: construct_custom_home.h
three_pigs_makers.cpp: stone_housemaker.h
three_pigs_makers.cpp: straw_housemaker.h
three_pigs_makers.cpp: wood_housemaker.h
