/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:13:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:13:34 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_cmd_table
{
	char	*cmd;
	char	**args;
}	t_cmd_table;

typedef struct s_shell
{
	int		argc;
	char	**argv;
	char	**envs;
	char	*prompt;
	char	*input;
	char	*trimmed_input;
	int		exit_code;
}	t_shell;

#endif