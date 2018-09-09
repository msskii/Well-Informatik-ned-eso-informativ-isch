a=$(find . -name *.cpp)
a="${a//.\//    }"
a="${a//.cpp/.cpp \\}"

makefile='CXX = g++
CFLAGS = -I. -I../SDL2/include/ -I../SDL2_net/ -I../SDL2_mixer/ -I../SDL2_image/ -I../SDL2_ttf/
LIBS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_net -lSDL2_image -lSDL2_mixer
LDDFLAGS = -L/usr/local/lib
DEPS ='
makefile="$makefile $a"

makefile="$makefile

prog: \$(DEPS)
	\$(CXX) -o ../Game \$(CFLAGS) \$(LDDFLAGS) \$(LIBS) \$(DEPS)

%.o: %.cpp
	\$(CXX) \$(CFLAGS) -c -o \$@ $<
"

echo "$makefile" > Makefile
