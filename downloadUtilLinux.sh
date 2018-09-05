function downloadLibrary() # args: library, version
{
  curl "$3/$1-$2.zip" -o "./$1.zip"
  echo -n "A" | unzip "./$1.zip"
  mv "./$1-$2" "./$1"
  rm -rf "./$1.zip"

  cd "./$1"
  ./configure
  make
  cd ..
}
