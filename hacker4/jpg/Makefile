#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

recover: recover.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o recover recover.c -L ../../library50/ -lcs50 -lm

clean:
	rm -f *.o a.out core recover
