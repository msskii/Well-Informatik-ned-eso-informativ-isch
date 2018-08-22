# Download & Install SDL2
curl "https://www.libsdl.org/release/SDL2-2.0.8.dmg" -o "SDL2.dmg"
hdiutil mount SDL2.dmg
cp -r /Volumes/SDL2/SDL2.framework .
hdiutil eject /Volumes/SDL2
rm SDL2.dmg

# Download & Install SDL2_ttf
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg" -o "SDL2_ttf.dmg"
hdiutil mount SDL2_ttf.dmg
cp -r /Volumes/SDL2_ttf/SDL2_ttf.framework .
hdiutil eject /Volumes/SDL2_ttf
rm SDL2_ttf.dmg

# Download & unzip font
curl "https://www.1001freefonts.com/d/5455/ormont-light.zip" -o "font.zip"
unzip font.zip
rm -rf __MACOSX
rm -f font.zip
