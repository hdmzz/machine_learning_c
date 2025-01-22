O = objs/
S = src/

NAME =	machine_learning_c

HEADER = includes/model.h

SRC = $Smain.c

SRC_GATE = $Sgates.c

OBJ = $(SRC:$S%=$O%.o)
OBJ_GATES = $(SRC_GATE:$S%=$O%gates.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra

.PHONY: all fclean re

all: $(NAME)

gates: $(OBJ_GATES)
	$(CC) $(CFLAGS) $(SRC_GATE) -o gates -I ./includes -lm

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(OBJ_GATES): $O%gates.o: $Sgates.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -I ./includes

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)

fclean:	clean
	rm -rf $(NAME)
	rm -rf twice
	rm -rf gates

re:	fclean all

run: all
	./$(NAME)
