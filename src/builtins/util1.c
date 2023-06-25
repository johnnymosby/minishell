/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:52:49 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 19:14:44 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_message(char *name_of_func, char *mess)
{
	ft_putendl_fd(mess, STDERR_FILENO);
	return (2);
}


void	n_lines_free(char **ss)
{
	int	i;

	while (ss)
	{
		free(ss[i]);
		ss++;
	}
	free(ss);
}

int	is_in_envsv(char *var, char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (FALSE);
	n = 0;
	while (var[n] != '\0' && var[n] != '=')
		n++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
/*
This function tries to extract the value of environment variable from **envs in *cmd

char	*ft_getenv(char **env, char *var, )
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	if (!ft_strchr(var, '='))
		return (NULL);
	j = ft_strlen(var);
	if (j == 0)
		return (NULL);
	while (env && env[i])
	{
		j = ft_strlen(var);
		if (j < ft_strchr(cmd->envs[i], '='))
			j = ft_strchr(cmd->envs[i], '=');
		if (!ft_strncmp(env[i], var, j))
			z = ft_substr(env[i], j + 1, ft_strlen(env[i])));
			if ()
		i++;
	}
	return (NULL);
}

char	*join_with_equal(char *s1, char *s2)
{
	char	*str;
	char	*tmp;

	if (!s1)
		return (NULL);
	tmp = ft_strjoin(s1, '=');
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

This function inserts a value of an environmental 
vairable to the existing list of variables
char	**ft_set_new_env(char **env, char *var, char *value)
{
	int		i[2];
	char	*str;
	char	*tmp;

	if (ft_strchr(var, '=') || !var)
		return (NULL);
	str = join_with_equal(var, value);
	i[0] = 0;
	while (env && env[i[0]])
	{
		i[1] = ft_strlen(var);
		if (!ft_strncmp(env[i[0]], var, i[1])
			&& env[i[0]][i[1]] == '=')
		{
			tmp = env[i[0]];
			env[i[0]] = str;
			free(tmp);
			return (env[i[0]]);
		}
		i[0]++;
	}
	env = ft_add_line(env, str);
	free(str);
	return (env);
}*/
