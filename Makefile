NAME	=	minishell

LIBFT	=	./lib/libft/libft.a

SRC_DIR	=	src/
OBJ_DIR	=	obj/

MAIN	=	main
MAIN	:=	$(addprefix main/, $(MAIN))

UTILS	=	check_argc
UTILS	:=	$(addprefix utils/, $(UTILS))

SIG		=	check_signals
SIG		:=	$(addprefix signals/, $(SIG))

LOOP	=	minishell_loop
LOOP	:=	$(addprefix loop/, $(LOOP))

INIT	=	init
INIT	:=	$(addprefix init/, $(INIT))

SOURCE	=	$(MAIN) $(UTILS) $(LOOP) $(INIT) $(SIG)
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			make -C ./lib/libft/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
			@mkdir -p $(@D)
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJ)
			make clean -C ./lib/libft/
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./lib/libft/

re:			fclean all

.PHONY:		all, clean, fclean, re
