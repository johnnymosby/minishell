/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:43:57 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 19:17:54 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_H
# define BUILTS_H

# define PATH_MAX 256

# include "../../lib/libft/libft.h"
# include "../../inc/defines.h"
# include "../../inc/structs.h"


int is_in_envs(const char *var, const char **env);
int is_in_envsv(char *var, char **env);
void	add_new_env(char *env_var, t_shell *shell);
char	*construct_env_var(const char *name, char *value, int to_free_value,
		t_shell *shell);
void	change_env_value(const char *name, char *value, int to_free_value,
		t_shell *shell);
void	set_new_value(const char *name, char *value, int to_free_value,
		t_shell *shell);
void	change_pwd_and_oldpwd(char *oldpwd_val, t_shell *shell);
void		n_lines_free(char **ss);

char		**ft_add_line(char **ss, char *str);
char		**ft_remove_line(char **ss, char *str);
char		**ft_set_new_env(char **env, char *var, char *value);
char		*ft_getenv(char **env, char *var);

int			nb_of_rows(char **ss);
int			ft_echo(char **ss);
int			ft_export(t_shell *, char **args);
int			ft_pwd(void);
int			ft_unset(t_shell *cmd, char **args);
int			ft_built(t_shell *shell);
int			error_message(char *name_of_func, char *mess);

char		**free_n_lines(char **ss, char **ss1, int n);


#endif
