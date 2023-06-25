/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:19:40 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 19:26:27 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

/*
Unset without options
*/
int	ft_unset(t_shell *shell, char **args)
{
	char	*tmp;
	char	**ss;
	int		i;
	int		j;

	if (!shell->envs || !args || !args[0])
		return (0);
	i = -1;
	while (args[++i])
	{
		if (args[ft_strlen(args) - 1] != '=')
		{
			tmp = ft_strjoin(args[i], "=");
			if (tmp == NULL)
			{
				n_lines_free(args);
				clean_exit(shell, FT_ERROR);
			}
			free(args[i]);
			args[i] = tmp;
		}
		if (is_in_envsv(args[i], shell->envs))
			ss = ft_remove_line(shell->envs, args[i]);
		n_lines_free(shell->envs);
		shell->envs = ss;
		ss = NULL;
	}
	return (0);
}
