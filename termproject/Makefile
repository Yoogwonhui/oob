.SUFFIXES: .cpp .o

OBJECTS = Block.o GameLogic.o myio.o 
TEST_FILE = main.o $(OBJECTS)

CXX = g++

TARGET = test
TEST = test

$(TEST) : $(TEST_FILE)
		$(CXX) -o $(TEST) $(TEST_FILE)

clean :
		rm -rf $(TEST) $(TEST_FILE)

main.o : main.cpp
Block.o : Block.cpp
GameLogic.o : GameLogic.cpp
myio.o : myio.cpp
