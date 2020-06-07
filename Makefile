CXX = g++
# Update these paths as necessary to match your installation
SDL_LIB = -LC:/Users/akash/Desktop/C++\ Nanodegree/SDL2-2.0.12/i686-w64-mingw32/lib -lSDL2main -lSDL2
SDL_INCLUDE = -IC:/Users/akash/Desktop/C++\ Nanodegree/SDL2-2.0.12/i686-w64-mingw32/include 

SDL_IMAGE_LIB = -LC:/Users/akash/Desktop/C++\ Nanodegree/SDL2_image-2.0.5/i686-w64-mingw32/lib -lSDL2_image
SDL_IMAGE_INCLUDE = -IC:/Users/akash/Desktop/C++\ Nanodegree/SDL2_image-2.0.5/i686-w64-mingw32/include
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE) $(SDL_IMAGE_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB) $(SDL_IMAGE_LIB)
EXE = anime.exe

all: $(EXE)

# $@ is the name of the file being generated, and $< the first prerequisite (usually the source file).
$(EXE): main.o game.o renderer.o animation.o character.o wolf.o coin.o

	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.cpp game.h renderer.h

	$(CXX) $(CXXFLAGS) $< -o $@

game.o: game.cpp game.h renderer.h animation.h character.h coin.h wolf.h 

	$(CXX) $(CXXFLAGS) $< -o $@

renderer.o: renderer.cpp renderer.h character.h wolf.h coin.h

	$(CXX) $(CXXFLAGS) $< -o $@

animation.o: animation.cpp animation.h

	$(CXX) $(CXXFLAGS) $< -o $@

character.o: character.cpp character.h animation.h

	$(CXX) $(CXXFLAGS) $< -o $@

wolf.o: wolf.cpp wolf.h animation.h

	$(CXX) $(CXXFLAGS) $< -o $@

coin.o: coin.cpp coin.h animation.h

	$(CXX) $(CXXFLAGS) $< -o $@

clean:

	rm *.o && rm $(EXE)

