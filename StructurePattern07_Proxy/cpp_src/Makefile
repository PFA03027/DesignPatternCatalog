
all: three_pings_text_object.exe

run: all
	./three_pings_text_object.exe

clean:
	rm -fr three_pings_text_object.exe

three_pings_text_object.exe: main.cpp three_pings_text_object.cpp
	g++ -o three_pings_text_object.exe  main.cpp three_pings_text_object.cpp

main.cpp: three_pings_text_object.hpp

three_pings_text_object.cpp: three_pings_text_object.hpp

