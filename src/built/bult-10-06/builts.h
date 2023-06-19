/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:43:57 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/19 16:20:20 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_H
# define BUILTS_H

# define PATH_MAX 256

/*typedef struct s_shell
{
	int			argc;
	char		**argv;
	char		**envs;
	char		*prompt;
	char		*input;
	char		*trimmed_input;
	int			exit_code;
	int			if_history_exists;
	t_tkn_tbl	*tkn_tbl;
	int			n_cmd_tbls;
	t_cmd_tbl	*cmd_tbls;
}	t_shell;*/

//#include "../../inc/minishell.h"
#include "structs.h"
#include "./libft/libft.h"
#include <stdio.h>
  
#include <stdlib.h>
#include <stddef.h>

#include <string.h>


int nb_of_rows(char **ss);
char **free_n_lines(char **ss, char **ss1, int n);
char **ft_add_line(char **ss, char *str);
char **ft_set_new_env(char **env, char *var, char *value);
static int 	is_in_envs(char *var, char **env);

#endif
