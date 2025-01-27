O = objs/
S = src/

NAME =	machine_learning_c

HEADER = includes/model.h

SRC = $Smain.c

SRC_GATE = $Sgates.c

SRC_XOR = $Sxor.c

OBJ = $(SRC:$S%=$O%.o)
OBJ_GATES = $(SRC_GATE:$S%=$O%gates.o)
OBJ_XOR = $(SRC_XOR:$S%=$O%xor.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror


all: $(NAME)

$O:
	@mkdir -p $@
	@mkdir -p $@/gates
	@mkdir -p $@/xor

$(OBJ): | $O
$(OBJ_GATES): | $O
$(OBJ_XOR): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(OBJ_GATES): $O%gates.o: $Sgates.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(OBJ_XOR): $O%xor.o: $Sxor.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -I ./includes

gates: $(OBJ_GATES)
	$(CC) $(CFLAGS) $(SRC_GATE) -o gates -I ./includes -lm

xor: $(OBJ_XOR)
	$(CC) $(CFLAGS) $(SRC_XOR) -o xor -I ./includes -lm

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)
	rm -rf objs

fclean:	clean
	rm -rf $(NAME)
	rm gates
	rm xor
	rm twice

re:	fclean all

run: all
	./$(NAME)

.PHONY: all fclean re
