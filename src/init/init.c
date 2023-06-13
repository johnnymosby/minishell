/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:40:35 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/13 12:01:33 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*construct_prompt(t_shell *shell, char *username)
{
	char	*prompt;
	char	*prompt_tail;
	int		prompt_length;

	prompt_tail = "@minishell % ";
	prompt_length = ft_strlen(username) + ft_strlen(prompt_tail) + 1;
	prompt = malloc(sizeof(char) * prompt_length);
	exit_if_true(shell, prompt == NULL, FT_ERROR);
	prompt[0] = '\0';
	ft_strlcat(prompt, username, prompt_length);
	ft_strlcat(prompt, prompt_tail, prompt_length);
	return (prompt);
}

char	*return_prompt(t_shell *shell)
{
	char	*username;
	char	*prompt;

	username = getenv("USER");
	if (username == NULL)
		username = "user";
	prompt = construct_prompt(shell, username);
	return (prompt);
}

/*
**exit the program if STDIN_FILENO does not refer to a terminal device
**initialise arguments
*/

void	dup_std_in_out(t_shell *shell)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	exit_if_true(shell, in == -1, FT_ERROR);
	out = dup(STDOUT_FILENO);
	if (out == -1)
	{
		close(in);
		exit_if_true(shell, TRUE, FT_ERROR);
	}
	shell->std_in_out[0] = in;
	shell->std_in_out[1] = out;
}

void	init_minishell(t_shell *shell, char **envs)
{
	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	shell->envs = envs;
	shell->prompt = return_prompt(shell);
	dup_std_in_out(shell);
}
