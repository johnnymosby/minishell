/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:55:22 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/03 11:27:52 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Minishell does not accept any arguments\n");
		exit(EXIT_FAILURE);
	}
}
