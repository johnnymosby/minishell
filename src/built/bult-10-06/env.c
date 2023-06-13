/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:15:08 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/11 18:18:20 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"
//#include "../inc/minishell.h"

/*
This function tries to extract a environtment variable from **envs in *cmd
*/
char	*ft_getenv(t_shell  *cmd, char *var)
{
	int	i;
	int	j;

	i = 0;
	if(ft_strchr(var, '='))
		return (NULL);
	j = ft_strlen(var);
	if (j == 0)		// check??
		return (NULL);
	while (cmd->envs && cmd->envs[i])
	{
		//j = ft_strlen(var);
		//if (j < ft_strchr(cmd->envs[i], '='))
		//	j = ft_strchr(cmd->envs[i], '=');
		if (!ft_strncmp(cmd->envs[i], var, j))
			return (ft_substr(cmd->envs[i], j + 1, ft_strlen(cmd->envs[i])));
		i++;
	}
	return (NULL);
}

char *join_with_equal(char *s1, char *s2)
{
	char *str;
	char *tmp;

	if (!s1)
		return (NULL);
	tmp = ft_strjoin(s1, '=');
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

/*
This function inserts a values of an environmental vairable to the existing list of variables
*/
char **ft_set_new_env(t_shell *cmd, char *var, char *value)
{
	int i[2];
	char *str;
	char *tmp;

	if(ft_strchr(var, '=') || !var)
		return (NULL);
	str = join_with_equal(var, value);
	i[0] = 0;
	while(cmd->envs && cmd->envs[i[0]])
	{
		i[1] = ft_strlen(var);
		//if (i[1] < ft_strchr(cmd->envs[i[0]], '='))
		//	i[1] = ft_strchr(cmd->envs[i[0]], '=');
		if (!ft_strncmp(cmd->envs[i[0]], var, i[1]))
		{
			tmp = cmd->envs[i[0]];
			cmd->envs[i[0]] = str;
			free(tmp);
			return (cmd->envs[i[0]]);
		}
		i[0]++;
	}
	cmd->envs = ft_add_line(cmd->envs, str); 
	free(str);
	return (cmd->envs);
}

/* 
This function checks if a given variable *var exists in the list **env of environmental variables
*/
static int 	is_in_envs(char *var, char **env)
{
	int i;
	int n;

	if (!var|| !env || !*env)
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


