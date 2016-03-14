#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

copy: copy.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o copy copy.c -L ../../library50/ -lcs50 -lm

whodunit: whodunit.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o whodunit whodunit.c -L ../../library50/ -lcs50 -lm

resize: resize.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o resize resize.c -L ../../library50/ -lcs50 -lm

clean:
	rm -f *.o a.out core copy whodunit  resize
