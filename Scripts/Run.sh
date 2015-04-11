#!/bin/bash

. ~/Scripts/defineColors.sh

ME=`basename $0`

num=1
if [ $# -ge 1 ]; then
	num=$1
fi

if [ ! -f ./bin ]; then
	${SD}/Compile.sh
	if [ "$?" != "0" ]; then
		exit 2
	fi
fi

if [ ! -f input${num}.txt ]; then
	echo -e "${CLRED}Input file   ${CYELLOW}input${num}.txt${CLRED}   not found.${CEND}"
	exit 3
fi

startTS=`date +%s%N | cut -b1-13`
cat input${num}.txt | grep -v "^##" | ./bin > .tmp
if [ "$?" != "0" ]; then
	exit 1
fi
endTS=`date +%s%N | cut -b1-13`

grep -v "^##" .tmp > .tmp2
grep -v "^##" output${num}.txt > .tmp4

diff .tmp4 .tmp2 -y -s > .tmp3

if [ "$?" != "0" ]; then
	echo -e "${CLRED}TEST FAILED!!${CEND}"
	echo -e "${CYELLOW}==================================== ${CLRED}DIFF${CYELLOW} ====================================${CEND}"
	cat .tmp3
	echo -e "${CYELLOW}=================================== ${CLRED}OUTPUT${CYELLOW} ===================================${CEND}"
	cat .tmp
	echo -e "${CYELLOW}==============================================================================${CEND}"
	echo -e "${CLRED}TEST FAILED!! Check diff above!${CEND}"
else
	colorOutput=${CGREEN}
	echo -e "${CGREEN}TEST PASSED!${CEND}"
	echo -e "${CYELLOW}=================================== ${CGREEN}OUTPUT${CYELLOW} ===================================${CEND}"
	cat .tmp
	echo -e "${CYELLOW}==============================================================================${CEND}"
	echo -e "${CGREEN}TEST PASSED!${CEND}"
fi

echo -e "${CCYAN}Runtime: ${CYELLOW}$(( (endTS - startTS) )) uSeconds${CEND}"

rm .tmp .tmp2 .tmp3 .tmp4

echo -e "${CYELLOW}Done.${CEND}"

