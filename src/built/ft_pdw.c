/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pdw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:26 by maruzibo          #+#    #+#             */
/*   Updated: 2023/05/31 17:55:54 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pwd.h"

/*
This function prints the address of currenct directory 
*/

int ft_pwd(void)
{
    char    p[PATH_MAX];
    if(getcwd(path, sizeof(path)))
        ft_putendl_fd(path, STDOUT_FILENO);
    else
    {
        ft_putstr_fd(ss[i], STDOUT_FILENO);
        return(1);
    }
    return (0);
}