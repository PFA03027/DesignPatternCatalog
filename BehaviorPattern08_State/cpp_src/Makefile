
all: three_pigs_story.exe

run: all
	three_pigs_story.exe

clean:
	rm -fr three_pigs_story.exe

three_pigs_story.exe: three_pigs_story.cpp three_pigs_story.h main.cpp
	g++ -g -o three_pigs_story.exe three_pigs_story.cpp main.cpp

