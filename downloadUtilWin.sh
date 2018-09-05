mkdir ./Informatik
mkdir ./Informatik/Debug/ # Make directory for debug stuff

function downloadLibrary()
{
  rm -rf "./$1"
  curl "$3/$1-devel-$2-VC.zip" -o "./$1.zip"
  echo -n "A" | unzip "./$1.zip"
  rm "./$1.zip"
  mv "./$1-$2" "./$1"

  find "./$1/lib/x86" -name "*.dll" -exec cp {} ./Informatik/Debug/ \;
}
