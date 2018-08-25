cd "$(dirname $0)"

# Delete old & Download & Install SDL2
rm -rf SDL2/
curl "https://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip" -o "SDL2.zip"
echo -n "A" | unzip SDL2.zip
rm SDL2.zip
mv SDL2-2.0.8/ SDL2

# Delete old & Download & Install SDL2_ttf
rm -rf SDL2_ttf/
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip" -o "SDL2_ttf.zip"
echo -n "A" | unzip SDL2_ttf.zip
rm SDL2_ttf.zip
mv SDL2_ttf-2.0.14/ SDL2_ttf

# Download & unzip fonts
curl "https://www.1001freefonts.com/d/5455/ormont-light.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip

curl "https://www.1001freefonts.com/d/5742/raleway.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip
