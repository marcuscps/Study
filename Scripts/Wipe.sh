#!/bin/bash

. ~/Scripts/defineColors.sh

for iii in `find ./ -name bin`; do
	rm ${iii}
	if [ "$?" == "0" ]; then
		echo -e "    ${CLPURPLE}${iii}${CGREEN} deleted${CEND}"
	else
		echo -e "    ${CLPURPLE}${iii}${CYELLOW} delete failed${CEND}"
	fi
done

echo -e "${CYELLOW}Done.${CEND}"

