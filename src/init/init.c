/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:40:35 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/18 16:29:26 by rbasyrov         ###   ########.fr       */
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
	exit_if_true(shell, prompt == NULL);
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
void	init_minishell(t_shell *shell, char **envs)
{
	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	shell->envs = envs;
	shell->prompt = return_prompt(shell);
}
