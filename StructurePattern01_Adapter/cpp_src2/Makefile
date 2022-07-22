
all: housing_exhibition_hall.exe

run: all
	housing_exhibition_hall.exe

clean:
	rm -fr housing_exhibition_hall.exe

housing_exhibition_hall.exe: housing_exhibition_hall.cpp
	g++ -o housing_exhibition_hall.exe housing_exhibition_hall.cpp

housing_exhibition_hall.cpp: reception_desk_adapter.h

reception_desk_adapter.h: straw_housemaker.h

reception_desk_adapter.h: wood_housemaker.h

reception_desk_adapter.h: stone_housemaker.h
