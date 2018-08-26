cd "$(dirname $0)"

# Download & Install SDL2
rm -rf SDL2.framework/
curl "https://www.libsdl.org/release/SDL2-2.0.8.dmg" -o "SDL2.dmg"
hdiutil mount SDL2.dmg
cp -r /Volumes/SDL2/SDL2.framework .
hdiutil eject /Volumes/SDL2
rm SDL2.dmg

# Download & Install SDL2_ttf
rm -rf SDL2_ttf.framework/
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg" -o "SDL2_ttf.dmg"
hdiutil mount SDL2_ttf.dmg
cp -r /Volumes/SDL2_ttf/SDL2_ttf.framework .
hdiutil eject /Volumes/SDL2_ttf
rm SDL2_ttf.dmg

# Download & Install SDL2_net
rm -rf SDL2_net.framework/
curl "https://www.libsdl.org/projects/SDL_net/release/SDL2_net-2.0.1.dmg" -o "SDL2_net.dmg"
hdiutil mount SDL2_net.dmg
cp -r /Volumes/SDL2_net/SDL2_net.framework .
hdiutil eject /Volumes/SDL2_net
rm SDL2_net.dmg

# Download & Install SDL2_mixer
rm -rf SDL2_mixer.framework/
curl "https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.2.dmg" -o "SDL2_mixer.dmg"
hdiutil mount SDL2_mixer.dmg
cp -r /Volumes/SDL2_mixer/SDL2_mixer.framework .
hdiutil eject /Volumes/SDL2_mixer
rm SDL2_mixer.dmg

# Download & Install SDL2_image
rm -rf SDL2_mixer.framework/
curl "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.dmg" -o "SDL2_image.dmg"
hdiutil mount SDL2_image.dmg
cp -r /Volumes/SDL2_image/SDL2_image.framework .
hdiutil eject /Volumes/SDL2_image
rm SDL2_image.dmg

# Download & unzip font
curl "https://www.1001freefonts.com/d/5455/ormont-light.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip

curl "https://www.1001freefonts.com/d/5742/raleway.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip
