.SUFFIXS: .cpp .o

OBJECTS = print.o student_id.o main.o

CXX = g++
CPPFLAGS = -c

TARGET = test

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET)

print.o : print.cpp
student_id.o : student_id.cpp
main.o : main.cpp


