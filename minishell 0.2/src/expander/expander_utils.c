/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:31:45 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/26 13:51:15 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_repeating_dollars(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] == '$' && s[i + 1] == '$'))
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

void	remove_trailing_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (i > 0 && s[i - 1] == '$')
		s[i - 1] = '\0';
}

int	find_len_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
		i++;
	return (i);
}

void	cut_out_variable(char *s, int ind)
{
	int	j;

	j = 0;
	while (s[j] != '\0')
		j++;
	if (j <= ind || s[ind] != '$')
		return ;
	j = ind;
	ind++;
	while (s[ind] != '\0' && s[ind] != '$')
		ind++;
	while (s[ind] != '\0')
	{
		s[j] = s[ind];
		ind++;
		j++;
	}
	s[j] = '\0';
}
