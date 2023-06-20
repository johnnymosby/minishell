/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:26 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 18:21:32 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_pwd.h"
#include "builts.h"

/*
This function prints the address of currenct directory 
*/
int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_putendl_fd(path, STDOUT_FILENO);
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}
