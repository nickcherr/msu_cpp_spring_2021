CC=g++
FLAGS=-std=c++17 -Wall -Werror -fsanitize=address -Wextra

test: task.cpp
	$(CC) $(FLAGS) task.cpp -o test
	./test

.PHONY: clean
clean:
	rm test
