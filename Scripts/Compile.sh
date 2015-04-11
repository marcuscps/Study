#!/bin/bash

. ~/Scripts/defineColors.sh

ME=`basename $0`

g++ -Wall -o bin *.cpp -std=c++11

if [ "$?" == "0" ]; then
	echo -e "${CYELLOW}Done.${CEND}"
else
	echo -e "${CRED}Error(s) found.${CEND}"
fi

