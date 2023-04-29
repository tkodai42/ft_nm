#!/bin/bash

FILE_NAME=a.out
if [ $# != 0 ]
then
	FILE_NAME=$1
fi

nm $FILE_NAME > txt1 -a
./ft_nm $FILE_NAME > txt2 -a

diff txt1 txt2
