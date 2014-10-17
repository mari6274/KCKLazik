CC=g++
CFLAGS=-Iinclude -Isrc
LFLAGS=-Lsrc -lsfml-graphics -l-sfml-window -lsfml-system
OBJS=obj/Game.o obj/SFMLPhysics.o

program: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) main.cpp $(OBJS) -o program 
	
obj/Game.o: src/Game.cpp
	$(CC) $(CFLAGS) $(LFLAGS) src/Game.cpp -o obj/Game.o
	
obj/SFMLPhysics.o: src/SFMLPhysics.cpp
	$(CC) $(CFLAGS) $(LFLAGS) src/SFMLPhysics.cpp -o obj/SFMLPhysics.o
	
