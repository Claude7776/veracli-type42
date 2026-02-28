NAME = veracli
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -std=c11
SRC = src/main.c src/utils.c src/header.c src/kdf.c src/crypto.c
OBJ = $(SRC:.c=.o)
LIBS = -lcrypto -largon2

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
