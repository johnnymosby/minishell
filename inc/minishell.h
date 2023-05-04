/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:13:56 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/03 12:16:54 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../lib/libft/libft.h"
# include "structs.h"
// macros:		EXIT_SUCCESS, EXIT_FAILURE
// functions:	exit
# include <stdlib.h>

// functions:	printf
# include <stdio.h>

// utils/...
//	 .../check_argc.c
void	check_argc(int argc);

#endif