valgrind:
gcc -Wall -Wextra -Werror -g *.c -o codexion

valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./codexion 5 800 200 100 100 3 0 fifo