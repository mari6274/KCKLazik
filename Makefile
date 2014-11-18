CC=g++
CFLAGS=-Wall -g -Iinclude -std=c++11
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OBJDIR=obj
OBJS=$(OBJDIR)/main.o $(OBJDIR)/Game.o $(OBJDIR)/Helper.o $(OBJDIR)/Object.o $(OBJDIR)/AStarVector2f.o

program.out: $(OBJS)
	$(CC) $(OBJS) -o program.out $(LFLAGS)

$(OBJDIR)/main.o: main.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c main.cpp -o $(OBJDIR)/main.o
$(OBJDIR)/Game.o: src/Game.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Game.cpp -o $(OBJDIR)/Game.o
$(OBJDIR)/Helper.o: src/Helper.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Helper.cpp -o $(OBJDIR)/Helper.o
$(OBJDIR)/Object.o: src/Object.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Object.cpp -o $(OBJDIR)/Object.o
$(OBJDIR)/AStarVector2f.o:
	$(CC) $(CFLAGS) -c src/AStarVector2f.cpp -o $(OBJDIR)/AStarVector2f.o
$(OBJDIR):
	mkdir -p $(OBJDIR)
