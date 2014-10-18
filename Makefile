CC=g++
CFLAGS=-Wall -g -Iinclude -std=c++11
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OBJS=obj/main.o obj/Game.o obj/SFMLPhysics.o obj/Object.o

program: $(OBJS)
	$(CC) $(OBJS) -o program $(LFLAGS)  

obj/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o obj/main.o
	
obj/Game.o: src/Game.cpp
	$(CC) $(CFLAGS) -c src/Game.cpp -o obj/Game.o
	
obj/SFMLPhysics.o: src/SFMLPhysics.cpp
	$(CC) $(CFLAGS) -c src/SFMLPhysics.cpp -o obj/SFMLPhysics.o
obj/Object.o: src/Object.cpp
	$(CC) $(CFLAGS) -c src/Object.cpp -o obj/Object.o
