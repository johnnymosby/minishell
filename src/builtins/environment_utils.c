/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:40:31 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/26 16:32:06 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_env_variable(t_shell *shell, int i)
{
	free(shell->envs[i]);
	while (shell->envs[i] != NULL)
	{
		shell->envs[i] = shell->envs[i + 1];
		i++;
	}
}

int	is_in_envs(char *var, char **env)
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

char	*get_env_var_name(t_shell *shell, char *var)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	s = ft_substr(var, 0, j);
	if (!s)
	{
		free(var);
		clean_exit(shell, FT_ERROR);
	}
	return (s);
	i++;
	return (NULL);
}

int	return_env_var_index(char *var, char **env)
{
	int	i;
	int	n;

	if (!var || !env)
		return (-1);
	n = 0;
	while (var[n] != '\0' && var[n] != '=')
		n++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, n))
			return (i);
		i++;
	}
	return (-1);
}

void	add_new_env(char *env_var, t_shell *shell)
{
	int		len;
	int		i;
	char	**new_envs;

	len = 0;
	while (shell->envs[len] != NULL)
		len++;
	new_envs = ft_calloc(len + 2, sizeof(char *));
	if (new_envs == NULL)
	{
		free(env_var);
		clean_exit(shell, FT_ERROR);
	}
	i = 0;
	while (i < len)
	{
		new_envs[i] = shell->envs[i];
		i++;
	}
	new_envs[i] = env_var;
	new_envs[i + 1] = NULL;
	free(shell->envs);
	shell->envs = new_envs;
}
