#!/bin/bash

# Colors
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
CLEAR='\033[0m'

test_cases=(
	""
	"1"
	"1 2"
	"1 2 3"
	"1 2 3 4 5 6"
	"-1 2 3 4"
	"1 2 3 -4"
	"1 0 3 -4"
	"1 150 2147483648 -4"
	"1 2 3 4"
	"1 2 3 4 5"
	)

philo_expected=(
	"Wrong number of arguments."
	"Wrong number of arguments."
	"Wrong number of arguments."
	"Wrong number of arguments."
	"Wrong number of arguments."
	"Arguments have to contain only digits."
	"Arguments have to contain only digits."
	"Arguments have to be positive integers."
	"Integer overflow."
	"Hello, I am philosopher number 1."
	"Hello, I am philosopher number 1."
	)

valgr_expected="All heap blocks were freed -- no leaks are possible"

ERROR=0

make

for i in ${!test_cases[@]}
do
	echo -e "${YELLOW}INPUT:${CLEAR} ${test_cases[i]}"
	echo -e "${YELLOW}EXP_OUTPOUT:${CLEAR} ${philo_expected[i]}"
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgr.log ./philo ${test_cases[i]} > philo.log 2>&1
	if grep "${philo_expected[i]}" philo.log > /dev/null
	then
		echo -e "philo_output: ${GREEN}OK${CLEAR}"
	else
		echo -e "philo_output: ${RED}KO${CLEAR}"
		ERROR=1
	fi
	if grep "$valgr_expected" valgr.log > /dev/null
	then
		echo -e "valgr_output: ${GREEN}OK${CLEAR}"
	else
		echo -e "valgr_output: ${RED}KO${CLEAR}"
		ERROR=1
	fi
	echo
done
if [ $ERROR -eq 0 ]
then
	echo -e "All tests passed."
else
	echo -e "${RED}ERROR:${CLEAR} check outputs."
fi


