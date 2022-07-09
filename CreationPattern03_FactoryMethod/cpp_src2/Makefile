
all: three_pigs_makers.exe

run:
	three_pigs_makers.exe

clean:
	rm -fr three_pigs_makers.exe

three_pigs_makers.exe: three_pigs_makers.cpp
	g++ -o three_pigs_makers.exe three_pigs_makers.cpp

three_pigs_makers.exe: construct_custom_home.h
three_pigs_makers.exe: stone_housemaker.h
three_pigs_makers.exe: straw_housemaker.h
three_pigs_makers.exe: wood_housemaker.h
