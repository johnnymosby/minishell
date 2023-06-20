/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:40:44 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 17:44:38 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"



char	**free_n_lines(char **ss, char **ss1, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (!ss[i])
			free(ss[i]);
	}
	if (!ss)
		free(ss);
	return (ss1);
}

void	n_lines_free(char **ss, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (!ss[i])
			free(ss[i]);
	}
	if (!ss)
		free(ss);
}

char	**ft_add_line(char **ss, char *str)
{
	char	**res;
	int		i[4];

	if (!ss && !str)
		return (NULL);
	res = NULL;
	i[3] = nb_of_rows(ss);
	res = (char **)malloc((i[3] + 2) * sizeof(char *));
	if (!res || !str)
		return (ss);
	i[0] = -1;
	while (++i[0] < i[3])
	{
		i[1] = ft_strlen(ss[i[0]]) + 1;
		res[i[0]] = (char *)malloc(i[1] * sizeof(char));
		if (!res[i[0]])
			free_n_lines(res, ss, i[0] + 1);
		ft_strlcpy(res[i[0]], ss[i[0]], i[1]);
	}
	i[2] = ft_strlen(str) + 1;
	res[i[3]] = (char *)malloc(i[2] * sizeof(char));
	if (!res[i[3]])
		free_n_lines(res, ss, i[3]);
	ft_strlcpy(res[i[3]], str, i[2]);
	return (res[i[3] + 1] = NULL, res);
}

int	ft_strchr_p(char *s, unsigned char ch)
{
	int	i;

	if (!s)
		i = 0;
	while (s[i] != ch)
		i++;
	return (i);
}
static int	is_in_envs(char *var, char **env)
{
	int		i;
	char	*var1;

	if (!var || !env || !*env)
		return (-1);
	var1 = (char *)malloc((ft_strlen(var) + 2) * sizeof(char));
	if (!var1)
		return (-1);
	ft_strlcpy(var1, var, ft_strlen(var));
	ft_strlcat(var1, "=", ft_strlen(var) + 1);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var1, ft_strlen(var1)))
		{
			free(var1);
			return (i);
		}
		i++;
	}
	free(var1);
	return (-1);
}
char	**ft_remove_line(char **ss, char *str)
{
	char	**res;
	int		i[3];

	if (!ss)
		return (NULL);
	else if (!str)
		return (ss);
	res = NULL;
	i[0] = nb_of_rows(ss);
	res = (char **)malloc(i[0] * sizeof(char *));
	if (!res)
		return (ss);
	i[1] = -1;
	while (++i[1] < i[0])
	{
		if (i[1] == is_in_envs(str, ss))
			i[1]++;
		i[2] = ft_strlen(ss[i[1]]) + 1;
		res[i[1]] = (char *)malloc(i[2] * sizeof(char));
		if (!res[i[1]])
			free_n_lines(res, ss, i[1] + 1);
		ft_strlcpy(res[i[1]], ss[i[1]], i[2]);
	}
	res[i[0]] = NULL;
	return (res);
}

/*
tmp= *ft_remove_line(env, str);
free(env);
env = tmp; 
*/
