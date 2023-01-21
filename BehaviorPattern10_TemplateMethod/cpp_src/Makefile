
all: house_builder_template.exe

run: all
	./house_builder_template.exe

clean:
	rm -fr house_builder_template.exe

house_builder_template.exe: house_builder_template.cpp house_maker_template.h
	g++ -o house_builder_template.exe house_builder_template.cpp

