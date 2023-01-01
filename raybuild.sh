gcc -g $1.c -fno-stack-protector -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ./build/$1
if [[ $? != 0 ]]
then
exit 1
#Usage: bash raybuild.sh <name>
fi
