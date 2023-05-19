/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:13:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/19 14:25:42 by rbasyrov         ###   ########.fr       */
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
	int		if_history_exists;
}	t_shell;

#endif