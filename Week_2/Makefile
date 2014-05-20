CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp texture_loader.cpp texture_loader.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lGL -lGLU -lglut

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -lGL -lGLU -lglut
