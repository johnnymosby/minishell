/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:40:44 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 18:20:28 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_add_line(char **ss, char *str)
{
	char	**res;
	int		len_of_ss;
	int		i;

	if (!ss && !str)
		return (NULL);
	else if (!str)
		return (ss);
	res = NULL;
	len_of_ss = nb_of_rows(ss);
	res = (char **)malloc((len_of_ss + 2) * sizeof(char *));
	if (!res)
		return (ss);
	i = -1;
	while (++i < len_of_ss)
	{	res[i] = ss[i];
		free(ss[i]);
	}
	res[i] = str;
	free(str);
	res[i + 1] = NULL,
	free(ss);
	return(res);
}

char	**ft_remove_line(char **ss, char *str)
{
	char	**res;
	int		len_of_ss;
	int		i;
	int		j;

	if (!ss)
		return (NULL);
	else if (!str)
		return (ss);
	res = NULL;
	len_of_ss = nb_of_rows(ss);
	res = (char **)malloc(len_of_ss * sizeof(char *));
	if (!res)
		return (ss);
	i = -1;
	j = 0;
	while (++i < len_of_ss)
	{
		j = i;
		if (is_in_envs(str, ss))
			j++;
		res[i] =  ss[j];
		free(ss[j]);
	}
	res[i] = NULL;
	free(ss);
	return (res);
}
