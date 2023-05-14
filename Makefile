NAME	=	minishell

USER	=	$(shell whoami)

LIBFT	=	./lib/libft/libft.a

OS		=	$(shell uname)

SRC_DIR	=	src/
OBJ_DIR	=	obj/

MAIN	=	main
MAIN	:=	$(addprefix main/, $(MAIN))

UTILS	=	
UTILS	:=	$(addprefix utils/, $(UTILS))

SIG		=	check_signals
SIG		:=	$(addprefix signals/, $(SIG))

LOOP	=	minishell_loop
LOOP	:=	$(addprefix loop/, $(LOOP))

INIT	=	init
INIT	:=	$(addprefix init/, $(INIT))

LEXER	=	lexer
LEXER	:=	$(addprefix lexer/, $(LEXER))

SOURCE	=	$(MAIN) $(UTILS) $(LOOP) $(INIT) $(SIG) $(LEXER)
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

ifeq ($(OS), Darwin)
RDL_HEAD	=	-I /Users/$(USER)/.brew/opt/readline/include
RDL_LIB		=	-L /Users/$(USER)/.brew/opt/readline/lib
endif

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(OBJ) $(CFLAGS) $(RDL_LIB) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
			make -C ./lib/libft/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
			@mkdir -p $(@D)
			$(CC) $(RDL_HEAD) -c $< -o $@

clean:
			rm -f $(OBJ)
			make clean -C ./lib/libft/
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./lib/libft/

re:			fclean all

.PHONY:		all, clean, fclean, re
