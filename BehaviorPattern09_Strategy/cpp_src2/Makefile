
all: house_maker_strategy.exe

run: all
	house_maker_strategy.exe

clean:
	rm -fr house_maker_strategy.exe

house_maker_strategy.exe: house_maker_strategy.cpp house_maker_strategy.h main.cpp
	g++ -g -o house_maker_strategy.exe house_maker_strategy.cpp main.cpp

