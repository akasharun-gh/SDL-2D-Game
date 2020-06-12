CXX = g++
# Update these paths as necessary to match your installation
SDL_LIB = -L{ path to SDL2 lib folder } -lSDL2main -lSDL2
SDL_INCLUDE = -I{ path to SDL2 include folder } 

SDL_IMAGE_LIB = -L{ path to SDL2_image lib folder } -lSDL2_image
SDL_IMAGE_INCLUDE = -I{ path to SDL2_image include folder }
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE) $(SDL_IMAGE_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB) $(SDL_IMAGE_LIB)
EXE = CoinCollector.exe

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

	rm *.o && rm $(EXE) && rm game_metadata/highscore.txt

