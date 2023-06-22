/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:38:19 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/22 22:33:04 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"
//#include "../inc/minishell.h"

/*
This function tries to extract an environment variable from **envs in *cmd
*/
char	*ft_getenv(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(var, '='))
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
			return (ft_substr(env[i], j + 1, ft_strlen(env[i])));
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

/*This function inserts a value of an environmental 
vairable to the existing list of variables*/
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
}

/* This function checks if a given variable *var
exists in the list **env of environmental variables
*/
static	int	is_in_envs(char *var, char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (-1);
	n = ft_strchr(var, '=');
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n + 1))
			return (i);
		i++;
	}
	return (-1);
}
