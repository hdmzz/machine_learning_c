O = objs/
S = src/

NAME =	machine_learning_c

HEADER = includes/model.h

SRC = $Smain.c

OBJ = $(SRC:$S%=$O%.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

.PHONY: all fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -I ./includes

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
