F ?= main.c 
I ?= test/open1.txt

perf:
	gcc -Wall -Wextra -std=gnu11 -O2 $(F)

top:
	gcc -Wall -Wextra -std=gnu11 -march=native -O3 $(F)

perf2:
	gcc -Wall -Wextra -std=gnu11 -O2 $(F)
	./a.out <$(I)

c++:
	g++ -Wall -Wextra -std=c++23 -O2 $(F)

static:
	gcc -Wall -Wextra -std=gnu11 -O2 --static $(F)

asan:
	gcc -std=gnu11 -O0 -Wall -Werror -Wextra -fsanitize=address,undefined -g3 $(F)
	./a.out <$(I)

valgrind:
	gcc -std=gnu11 -O0 -Wall -Werror -Wextra -g3 $(F)
	valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./a.out <$(I)

callgrind:
	gcc -std=gnu11 -O2 -Wall -Werror -Wextra -g3 $(F)
	valgrind --tool=callgrind ./a.out <$(I)

massif:
	gcc -std=gnu11 -O2 -Wall -Werror -Wextra -g3 $(F)
	valgrind --tool=massif ./a.out <$(I)

clean:
	rm -f a.out
	rm -f callgrind.out.*
	rm -f massif.out.*
	rm -f vgcore.*
