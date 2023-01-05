CXX = g++

MAIN_OBJECTS = data/src/main.cpp
MAIN_LIBS = data/object.o data/window.o data/init.o data/color.o -lSDL2
MAIN_FINAL = lgasm
MAIN_ALL = $(MAIN_OBJECTS) -o $(MAIN_FINAL) $(MAIN_LIBS)

LGASM_OBJECTS = src/lgs/object.cpp src/lgs/window.cpp src/lgs/init.cpp src/lgs/color.cpp
OBJECT_LIBS = -lSDL2
OBJECT_ALL = $(LGASM_OBJECTS) -c $(OBJECT_LIBS)

graphics:
	cd data; g++ ${OBJECT_ALL}


compiler:
	g++ ${MAIN_ALL}
