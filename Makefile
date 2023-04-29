NAME	=	minishell

LIBFT	=	./lib/libft/libft.a

SRC_DIR	=	./src/

INC		=	./inc

SRC		=	main.c
SRC		:=	$(addprefix $(SRC_DIR)/,$(SRC))

OBJ		=	$(SRC:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ) $(OMAIN) $(LIBFT)
			$(CC) $(OBJ) $(OMAIN) $(CFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
			make -C ./lib/libft/

.c.o:
			cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./inc

clean:
			rm -f $(OBJ)
			make clean -C ./lib/libft/

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./lib/libft/

re:			fclean all

.PHONY:		all, clean, fclean, re
