/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:43:57 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 17:40:16 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_H
# define BUILTS_H

# define PATH_MAX 256

//#include "../../inc/minishell.h"
# include "./libft/libft.h"
# include "structs.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char		**free_n_lines(char **ss, char **ss1, int n);
char		**ft_add_line(char **ss, char *str);
char		**ft_remove_line(char **ss, char *str);
char		**ft_set_new_env(char **env, char *var, char *value);
char		*ft_getenv(char **env, char *var);
static int	is_in_envs(char *var, char **env);

int			nb_of_rows(char **ss);
int			ft_echo(char **ss);
int			ft_cd_init(t_shell *shell);
int			ft_exit(t_shell *shell, int *exit_code);
int			ft_export(t_shell *cmd, char **args);
int			ft_pwd(void);
int			ft_unset(t_shell *cmd, char **args);
int			ft_built(t_shell *shell);
int			error_message(char *name_of_func, char *mess);

char		**free_n_lines(char **ss, char **ss1, int n);
void		n_lines_free(char **ss, int n);

#endif
