
all: three_pigs_makers.exe

run: all
	three_pigs_makers.exe

clean:
	rm -fr three_pigs_makers.exe

three_pigs_makers.exe: three_pigs_makers.cpp wolf_attack_story.cpp
	g++ -o three_pigs_makers.exe three_pigs_makers.cpp wolf_attack_story.cpp

three_pigs_makers.cpp: abstract_factory_housemaker.h
three_pigs_makers.cpp: concrete_factory_stone_housemaker.h
three_pigs_makers.cpp: concrete_factory_straw_housemaker.h
three_pigs_makers.cpp: concrete_factory_wood_housemaker.h
wolf_attack_story.cpp: abstract_factory_housemaker.h
