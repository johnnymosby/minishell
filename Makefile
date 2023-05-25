NAME	=	minishell

USER	=	$(shell whoami)

LIBFT	=	./lib/libft/libft.a

OS		=	$(shell uname)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

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

INIT	=	init init_tkn_tbl
INIT	:=	$(addprefix init/, $(INIT))

LEXER	=	lexer add_token
LEXER	:=	$(addprefix lexer/, $(LEXER))

EXPAND	=	expander
EXPAND	:=	$(addprefix expander/, $(EXPAND))

PARSER	=	parser
PARSER	:=	$(addprefix parser/, $(PARSER))

EXEC	=	execute
EXEC	:=	$(addprefix execute/, $(EXEC))

EXIT	=	exit
EXIT	:=	$(addprefix exit/, $(EXIT))

SOURCE	=	$(MAIN) $(UTILS) $(LOOP) $(INIT) $(SIG) $(LEXER) $(EXPAND) $(PARSER) $(EXEC) $(EXIT)
SRC		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

#tests:
SRCTESTDIR	=	tests/src/
OBJTESTDIR	=	tests/obj/
SOURCETEST	=	test
SRCTEST		=	$(addprefix $(SRCTESTDIR), $(addsuffix .cpp, $(SOURCETEST)))
OBJTEST		=	$(addprefix $(OBJTESTDIR), $(addsuffix .o, $(SOURCETEST)))

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

$(OBJTESTDIR)%.o : $(SRCTESTDIR)%.cpp
			@mkdir -p $(@D)
			c++ -std=c++14 $(RDL_HEAD) -c $< -o $@

clean:
			make clean -C ./lib/libft/
			rm -rf $(OBJ_DIR)
			rm -rf $(OBJTESTDIR)

fclean:		clean
			rm -f $(NAME)
			rm -f test
			make fclean -C ./lib/libft/

ifeq ($(OS), Darwin)
test:		$(OBJ) $(LIBFT) $(OBJTEST)
			c++ -std=c++14 $(filter-out obj/main/main.o,$(OBJ)) $(OBJTEST) $(CFLAGS) $(RDL_LIB) $(LIBFT) \
			-lreadline -lgtest -o test
endif

re:			fclean all

.PHONY:		all, clean, fclean, re
