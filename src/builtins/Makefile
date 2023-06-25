# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 13:15:57 by maruzibo          #+#    #+#              #
#    Updated: 2023/06/25 12:00:31 by maruzibo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = built

SRC = util.c ft_cd.c ft_export.c util1.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
		@cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft
	
clean:
		@rm -f $(OBJ)
		@make clean -C libft

fclean: clean
				@make fclean -C libft
				@rm -f $(NAME)
re: fclean all

.PHONY:			all clean fclean re