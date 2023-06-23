/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:26 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/24 00:16:31 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
This function prints the address of currenct directory 
*/
int	ft_pwd(void)
{
	char	path[FT_PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, STDOUT_FILENO);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}
