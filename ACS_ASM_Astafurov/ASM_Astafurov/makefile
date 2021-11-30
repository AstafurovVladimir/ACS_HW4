task: main.cpp Plant.cpp Tree.cpp Bush.cpp Flower.cpp functions.o
	g++ -g -o task main.cpp Plant.cpp Tree.cpp Bush.cpp Flower.cpp functions.o -no-pie
functions.o: functions.asm
	nasm -f elf64 -g -F dwarf functions.asm -l functions.lst
