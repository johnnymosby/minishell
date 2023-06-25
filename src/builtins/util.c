/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:40:44 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 18:51:17 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	nb_of_rows(char **ss)
{
	int	i;

	i = 0;
	if (!ss)
		return (0);
	while (ss[i])
		i++;
	return (i);
}

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
	{
		res[i] = ss[i];
	}
	res[i] = str;
	res[i + 1] = NULL;
	//free(ss);
	return (res);
}

char	**ft_remove_line(char **ss, char *str)
{
	char	**res;
	int		len_of_ss;
	int		i[2];

	if (!ss)
		return (NULL);
	else if (!str)
		return (ss);
	res = NULL;
	len_of_ss = nb_of_rows(ss);
	res = (char **)malloc(len_of_ss * sizeof(char *));
	if (!res)
		return (ss);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < len_of_ss)
	{
		if (is_in_envsv(str, ss))
			i[1]++;
		res[i[0]] = ss[i[0] + i[1]];
	}
	res[i[0]] = NULL;
	free(ss);
	return (res);
}
