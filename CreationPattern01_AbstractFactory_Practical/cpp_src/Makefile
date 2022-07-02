
all: elder_pig_makers.exe second_pig_makers.exe youngest_pig_makers.exe

run: all
	elder_pig_makers.exe
	second_pig_makers.exe
	youngest_pig_makers.exe

clean:
	rm -fr elder_pig_makers.exe second_pig_makers.exe youngest_pig_makers.exe

elder_pig_makers.exe: reuse_client/main.cpp reuse_client/wolf_attack_story.cpp housemaker/straw_housemaker/concrete_factory_straw_housemaker.cpp
	g++ -I./housemaker -o $@ $^

second_pig_makers.exe: reuse_client/main.cpp reuse_client/wolf_attack_story.cpp housemaker/wood_housemaker/concrete_factory_wood_housemaker.cpp
	g++ -I./housemaker -o $@ $^

youngest_pig_makers.exe: reuse_client/main.cpp reuse_client/wolf_attack_story.cpp housemaker/stone_housemaker/concrete_factory_stone_housemaker.cpp
	g++ -I./housemaker -o $@ $^

reuse_client/main.cpp: housemaker/abstract_factory_housemaker.h
reuse_client/wolf_attack_story.cpp: housemaker/abstract_factory_housemaker.h

housemaker/stone_housemaker/concrete_factory_stone_housemaker.cpp : housemaker/abstract_factory_housemaker.h
housemaker/straw_housemaker/concrete_factory_straw_housemaker.cpp : housemaker/abstract_factory_housemaker.h
housemaker/wood_housemaker/concrete_factory_wood_housemaker.cpp : housemaker/abstract_factory_housemaker.h


