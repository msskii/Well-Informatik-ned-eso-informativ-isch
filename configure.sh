cd Informatik

a="$(find . -name *.cpp)"
a="$a
$(find . -name *.c)"

# echo "$a"

a="${a//.\//    }"
# a="${a//.cpp/.cpp \\}"
a="${a//.c /.c \\}"
a="${a//.cpp/.cpp \\}"


# echo "$a"
# exit 0

makefile='CXX = g++
GCC = gcc
CFLAGS = -I. -I../SDL2/include/ -I../SDL2_net/ -I../SDL2_mixer/ -I../SDL2_image/ -I../SDL2_ttf/ -I./Informatik/glew/ -fpermissive
LIBS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_net -lSDL2_image -lSDL2_mixer -lGL
LDDFLAGS = -L/usr/local/lib
DEPS ='
makefile="$makefile $a"

makefile="$makefile

prog: \$(DEPS)
	\$(CXX) -o ../Game \$(CFLAGS) \$(LDDFLAGS) \$(LIBS) \$(DEPS)

%.o: %.cpp
	\$(CXX) \$(CFLAGS) -c -o \$@ $<

%.o: %.c
	\$(GCC) \$(CFLAGS) -c -o \$@ $<
"

echo "$makefile" > Makefile

cd ..
