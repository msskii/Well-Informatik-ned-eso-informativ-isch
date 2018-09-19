cd "$(dirname $0)"

#include platform specific download util functions
unamestr=$(uname)

if [[ $unamestr = "Darwin" ]]; then
  source "./downloadUtilMac.sh"
elif [[ $unamestr = "Linux" ]]; then
  releasestr=$(uname -r)
  echo "$releasestr"
  if [[ "$releasestr" =~ .+-Microsoft$ ]]; then
    source "./downloadUtilWin.sh"
  else
    source "./configure.sh" # setup makefile for later
    source "./downloadUtilLinux.sh"
  fi
else
  echo "No known platform: $unamestr."
  exit 0
fi

downloadLibrary "SDL2" "2.0.8" "https://www.libsdl.org/release"
downloadLibrary "SDL2_ttf" "2.0.14" "https://www.libsdl.org/projects/SDL_ttf/release"
downloadLibrary "SDL2_net" "2.0.1" "https://www.libsdl.org/projects/SDL_net/release"
downloadLibrary "SDL2_mixer" "2.0.2" "https://www.libsdl.org/projects/SDL_mixer/release"
downloadLibrary "SDL2_image" "2.0.3" "https://www.libsdl.org/projects/SDL_image/release"

curl "https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.zip" -o "./glew.zip" -L
echo -n "A" | unzip "./glew.zip"
rm -f "glew.zip"
mkdir "./Informatik/Informatik/glew/"
mv "./glew-2.1.0/src/glew.c" "./Informatik/Informatik/glew/"
 mkdir "./Informatik/Informatik/glew/GL"
mv "./glew-2.1.0/include/GL/glew.h" "./Informatik/Informatik/glew/GL/glew.h"
mv "./glew-2.1.0/include/GL/eglew.h" "./Informatik/Informatik/glew/GL/eglew.h"
mv "./glew-2.1.0/include/GL/glxew.h" "./Informatik/Informatik/glew/GL/glxew.h"
mv "./glew-2.1.0/include/GL/wglew.h" "./Informatik/Informatik/glew/GL/wglew.h"

rm -rf "./glew-2.1.0"

cd assets/fonts
# Download & unzip font
curl "https://www.1001freefonts.com/d/5455/ormont-light.zip" -o "font.zip"
echo -n "A" | unzip font.zip

curl "https://www.1001freefonts.com/d/5742/raleway.zip" -o "font.zip"
echo -n "A" | unzip font.zip

rm -f font.zip
rm -rf __MACOSX
