INCLUDES = -I lib
CFLAGS = -O2 ${INCLUDES} -std=c++17 -Werror
LIBS = -lm -lGLEW -lGL -lGLU -lglut
TARGET = main sphere shader triangle particule contrainte flag cube skybox
TARGET_OBJECT = $(addprefix bin/, $(addsuffix .o, $(TARGET)))

vpath %.cpp src/
vpath %.hpp include/

Flag: $(TARGET_OBJECT)
	g++ $(CFLAGS) $^ $(LIBS) -o $@

bin/shader.o: shader.cpp shader.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/sphere.o: sphere.cpp sphere.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/particule.o: particule.cpp particule.hpp includes.hpp 
	g++ $(CFLAGS) -c $< -o $@

bin/triangle.o: triangle.cpp triangle.hpp particule.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/contrainte.o: contrainte.cpp contrainte.hpp includes.hpp particule.hpp 
	g++ $(CFLAGS) -c $< -o $@

bin/cube.o: cube.cpp cube.hpp shader.hpp contrainte.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/skybox.o: skybox.cpp skybox.hpp shader.hpp contrainte.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/flag.o: flag.cpp flag.hpp includes.hpp particule.hpp contrainte.hpp triangle.hpp
	g++ $(CFLAGS) -c $< -o $@

bin/main.o: main.cpp includes.hpp shader.hpp flag.hpp sphere.hpp freeflycamera.hpp cube.hpp skybox.hpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	-rm bin/*.o
	-rm Flag