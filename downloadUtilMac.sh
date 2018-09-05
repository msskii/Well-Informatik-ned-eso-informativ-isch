function downloadLibrary()
{
  rm -rf "./$1.framework"
  curl "$3/$1-$2.dmg" -o "./$1.dmg"
  hdiutil mount "./$1.dmg"
  cp -r "/Volumes/$1/$1.framework" .
  hdiutil eject "/Volumes/$1"
  rm "./$1.dmg"
}
