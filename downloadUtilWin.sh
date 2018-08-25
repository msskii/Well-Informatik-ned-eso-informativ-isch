cd "$(dirname $0)"

# Delete old & Download & Install SDL2
rm -rf SDL2/
curl "https://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip" -o "SDL2.zip"
echo -n "A" | unzip SDL2.zip
rm SDL2.zip
mv SDL2-2.0.8/ SDL2

mkdir Informatik/Debug/
cp SDL2/lib/x86/SDL2.dll Informatik/Debug/

# Delete old & Download & Install SDL2_ttf
rm -rf SDL2_ttf/
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip" -o "SDL2_ttf.zip"
echo -n "A" | unzip SDL2_ttf.zip
rm SDL2_ttf.zip
mv SDL2_ttf-2.0.14/ SDL2_ttf

cp SDL2_ttf/lib/x86/SDL2_ttf.dll Informatik/Debug/
cp SDL2_ttf/lib/x86/zlib1.dll Informatik/Debug/
cp SDL2_ttf/lib/x86/libfreetype-6.dll Informatik/Debug/

# Delete old & Download & Install SDL2_net
rm -rf SDL2_net/
curl "https://www.libsdl.org/projects/SDL_net/release/SDL2_net-devel-2.0.1-VC.zip" -o "SDL2_net.zip"
echo -n "A" | unzip SDL2_net.zip
rm SDL2_net.zip
mv SDL2_net-2.0.1/ SDL2_net

cp SDL2_net/lib/x86/SDL2_net.dll Informatik/Debug/

# Download & Install SDL2_mixer
rm -rf SDL2_mixer/
curl "https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-VC.zip" -o "SDL2_mixer.zip"
echo -n "A" | unzip SDL2_mixer.zip
rm SDL2_mixer.zip
mv SDL2_mixer-2.0.2/ SDL2_mixer

cp SDL2_mixer/lib/x86/SDL2_mixer.dll Informatik/Debug/
cp SDL2_mixer/lib/x86/libogg-0.dll Informatik/Debug/
cp SDL2_mixer/lib/x86/libvorbis-0.dll Informatik/Debug/
cp SDL2_mixer/lib/x86/libvorbisfile-3.dll Informatik/Debug/
cp SDL2_mixer/lib/x86/libmpg123-0.dll Informatik/Debug/

# Download & unzip fonts
curl "https://www.1001freefonts.com/d/5455/ormont-light.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip

curl "https://www.1001freefonts.com/d/5742/raleway.zip" -o "font.zip"
echo -n "A" | unzip font.zip
rm -rf __MACOSX
rm -f font.zip
