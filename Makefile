NAME	=	minishell

USER	=	$(shell whoami)

LIBFT	=	./lib/libft/libft.a

OS		=	$(shell uname)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC_DIR	=	src/
OBJ_DIR	=	obj/

MAIN	=	main
MAIN	:=	$(addprefix main/, $(MAIN))

UTILS	=	general_utils history
UTILS	:=	$(addprefix utils/, $(UTILS))

SIG		=	check_signals
SIG		:=	$(addprefix signals/, $(SIG))

LOOP	=	minishell_loop
LOOP	:=	$(addprefix loop/, $(LOOP))

INIT	=	init init_tkn_tbl init_cmd_and_args
INIT	:=	$(addprefix init/, $(INIT))

LEXER	=	lexer add_token add_space
LEXER	:=	$(addprefix lexer/, $(LEXER))

EXPAND	=	expander expander_utils put_value expand_exit_code
EXPAND	:=	$(addprefix expander/, $(EXPAND))

PARSER	=	parser concatenate_words check_syntax check_syntax_utils check_access construct_cmd_tables \
			handle_heredocs imitate_heredocs heredocs_utils
PARSER	:=	$(addprefix parser/, $(PARSER))

EXEC	=	execute construct_pathname execute_with_pipes handle handle_redirections execute_last_cmd
EXEC	:=	$(addprefix execute/, $(EXEC))

BUILTINS	=	builtins_entrypoint ft_cd ft_echo
BUILTINS	:=	$(addprefix builtins/, $(BUILTINS))

EXIT	=	exit clean_shell error free_cmd_tbl
EXIT	:=	$(addprefix exit/, $(EXIT))

SOURCE	=	$(MAIN) $(UTILS) $(LOOP) $(INIT) $(SIG) $(LEXER) $(EXPAND) $(PARSER) $(EXEC) $(EXIT) $(BUILTINS)
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

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
			make clean -C ./lib/libft/
			rm -rf $(OBJ_DIR)
			rm -rf $(OBJTESTDIR)

fclean:		clean
			rm -f $(NAME)
			rm -f test
			make fclean -C ./lib/libft/

re:			fclean all

.PHONY:		all, clean, fclean, re
