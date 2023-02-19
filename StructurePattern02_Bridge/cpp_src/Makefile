
all: wolf_attack_three_little_pigs_house.exe

run: all
	./wolf_attack_three_little_pigs_house.exe

clean:
	rm -fr wolf_attack_three_little_pigs_house.exe

wolf_attack_three_little_pigs_house.exe: main.cpp house_impl.cpp house_redefinedabst.cpp
	g++ -o wolf_attack_three_little_pigs_house.exe main.cpp house_impl.cpp house_redefinedabst.cpp

main.cpp: house_abst.hpp

house_redefinedabst.cpp: house_impl.hpp house_abst.hpp

house_impl.cpp: house_impl.hpp
