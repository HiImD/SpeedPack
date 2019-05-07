ifeq ($(OS),Windows_NT) 
    detected_OS := WINDOWS
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
	ifeq ($(detected_OS),Linux)
        detected_OS = LINUX
    endif
endif

ifeq ($(detected_OS), WINDOWS)
	EXEC =$(EXECDIR)/main.exe
endif
ifeq ($(detected_OS), LINUX)
	EXEC =$(EXECDIR)/main
endif


CC = g++
CFLAG = -Wall -std=c++11 -Wl,-subsystem,windows
LFLAG = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRCDIR = ./src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
EXECDIR = ./bin



BUILDDIR = ./build
INCLUDE_PATH = -I./include -I./include/SDL2 -I./include/SDL2_TFF -I./include/SDL2_image
LIBRARY_PATH = -L./lib


OBJS = $(subst $(SRCDIR),$(BUILDDIR),$(SRCS))
OBJS := $(OBJS:cpp=o)

.PHONY: compile Build clean run proj

Build : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC)  $(OBJS) $(LIBRARY_PATH) $(LFLAG)  -o $@

compile : $(OBJS)


./build/%.o : ./src/%.cpp
	$(CC) $(INCLUDE_PATH) -g -c $(CFLAG) $< -o $@


run : 
	$(EXEC)

clean :
	rm -rf build
	mkdir build




#Creat project folder
bin: 
	mkdir bin
build:
	mkdir build
include:
	mkdir include
lib: 
	mkdir lib
src: 
	mkdir src
./src/main.cpp: src
	touch ./src/main.cpp

proj: bin build include lib src ./src/main.cpp 