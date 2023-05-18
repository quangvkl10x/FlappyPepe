set OBJS=main.cpp bird.cpp game.cpp land.cpp texture.cpp pipe.cpp sound.cpp
set OBJ_NAME=FlappyPepe.exe
set COMPILER_FLAGS=-std=c++11 
set ARGS=-w -Wl,-subsystem,windows
set LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
set INCLUDE_DIR=-ISDL\INCLUDE
set LIB_DIR=-LSDL\LIB

g++ %COMPILER_FLAGS% %INCLUDE_DIR% %LIB_DIR% %OBJS% %ARGS% %LINKER_FLAGS% -o %OBJ_NAME%