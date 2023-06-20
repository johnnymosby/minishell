/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:52:49 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 15:45:43 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builts.h"

int error_message(char *name_of_func, char *mess)
{
    int STDERR_FILENO = 2;
    
    ft_putendl_fd(mess, STDERR_FILENO);
    return (2);
}