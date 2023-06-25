/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:40:31 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 22:44:15 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
