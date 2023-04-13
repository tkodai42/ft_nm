# ft_nm

docker run -ti --name wwp debian:latest

CTRL-D

docker start -i wwp

apt update

apt install vim gcc file

echo "int main() { int i; }" > main.c

gcc main.c

CTRL-D

docker cp wwp:a.out .

