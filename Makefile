EXE = pa2

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o convexhull.o convexintersection.o drawingio.o main.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm 
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : pa2

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

#object files
RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

convexhull.o : convexhull.h orderingstructure.h stack.h stack.cpp convexhull.cpp
	$(CXX) $(CXXFLAGS) convexhull.cpp -o $@

convexintersection.o : convexintersection.h convexintersection.cpp
	$(CXX) $(CXXFLAGS) convexintersection.cpp -o $@

drawingio.o : drawingio.h drawingio.cpp
	$(CXX) $(CXXFLAGS) drawingio.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/RGBAPixel.h convexhull.h convexintersection.h drawingio.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE)
