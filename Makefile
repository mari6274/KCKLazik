CC=g++
CFLAGS=-Wall -g -Iinclude -std=c++11
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lmorfeusz2
OBJDIR=obj
OBJS=$(OBJDIR)/main.o $(OBJDIR)/Game.o $(OBJDIR)/Helper.o $(OBJDIR)/Object.o $(OBJDIR)/AStarVector2f.o $(OBJDIR)/Console.o $(OBJDIR)/Aiml.o $(OBJDIR)/Interpreter.o $(OBJDIR)/TaskManager.o $(OBJDIR)/InfoBox.o

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
$(OBJDIR)/AStarVector2f.o: src/AStarVector2f.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/AStarVector2f.cpp -o $(OBJDIR)/AStarVector2f.o
$(OBJDIR)/Console.o: src/Console.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Console.cpp -o $(OBJDIR)/Console.o
$(OBJDIR)/Aiml.o: src/Aiml.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Aiml.cpp -o $(OBJDIR)/Aiml.o
$(OBJDIR)/Interpreter.o: src/Interpreter.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/Interpreter.cpp -o $(OBJDIR)/Interpreter.o
$(OBJDIR)/TaskManager.o: src/TaskManager.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/TaskManager.cpp -o $(OBJDIR)/TaskManager.o
$(OBJDIR)/InfoBox.o: src/InfoBox.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c src/InfoBox.cpp -o $(OBJDIR)/InfoBox.o
$(OBJDIR):
	mkdir -p $(OBJDIR)
