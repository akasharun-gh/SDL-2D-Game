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


$(EXE): main.o

	$(CXX) $< $(LDFLAGS) -o $@

main.o: main.cpp character.cpp

	$(CXX) $(CXXFLAGS) $< -o $@

clean:

	del *.o && del $(EXE)