/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:26:33 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/21 11:43:57 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_status;

int	check_access_to_file(const char *pathname, t_shell *shell)
{
	if (access(pathname, R_OK | W_OK | X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((char *)pathname, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (set_exit_code(shell, 1), FALSE);
	}
	return (TRUE);
}

int	fill_heredoc(char *stopword, int fd, t_shell *shell)
{
	char	*input;

	g_status = 1;
	while (TRUE)
	{
		input = readline("> ");
		if (g_status == 130)
		{
			g_status = 1;
			return (free(input), close(fd), set_exit_code(shell, 130), FALSE);
		}
		if (input == NULL)
			return (close(fd), TRUE);
		if (ft_strcmp(input, stopword) == 0)
		{
			free(input);
			close(fd);
			return (TRUE);
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	return (close(fd), TRUE);
}

int	add_heredoc(char *stopword, t_cmd_tbl *cmd_tbl, int j, t_shell *shell)
{
	int		fd;
	char	*pathname;
	char	*file_id;

	if (check_access_to_file("/tmp/", shell) == FALSE)
		return (set_exit_code(shell, 1), FALSE);
	file_id = ft_itoa(j);
	if (file_id == NULL)
		clean_exit(shell, FT_ERROR);
	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
	free(file_id);
	if (pathname == NULL)
		clean_exit(shell, FT_ERROR);
	fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		write_file_error_message(pathname);
		free(pathname);
		clean_exit(shell, FT_ERROR);
	}
	free(pathname);
	if (fill_heredoc(stopword, fd, shell) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	handle_heredoc(int *last_heredoc_ind, int *i, int *j, t_shell *shell)
{
	t_cmd_tbl	*cmd_tbls;
	t_tkn_tbl	*tkn_tbl;

	cmd_tbls = shell->cmd_tbls;
	tkn_tbl = shell->tkn_tbl;
	*last_heredoc_ind = find_last_heredoc_in_cmd(tkn_tbl, *i);
	if (*last_heredoc_ind != -1 && *i != *last_heredoc_ind)
	{
		if (imitate_heredocs(tkn_tbl, *i, *last_heredoc_ind, shell) == FALSE)
			return (FALSE);
		*i = *last_heredoc_ind;
	}
	else
	{
		if (*last_heredoc_ind != -1 && *i == *last_heredoc_ind
			&& add_heredoc(tkn_tbl->tkns[*last_heredoc_ind + 1].cntnt,
				&cmd_tbls[*j], *j, shell) == FALSE)
			return (FALSE);
		*i = skip_cmd(tkn_tbl, *i);
	}
	return (TRUE);
}

int	handle_heredocs(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, t_shell *shell)
{
	int	i;
	int	j;
	int	last_heredoc_ind;

	i = 0;
	j = 0;
	while (i != tkn_tbl->n_tkns)
	{
		if (tkn_tbl->tkns[i].type == FT_PIPE)
		{
			i++;
			j++;
			continue ;
		}
		if (handle_heredoc(&last_heredoc_ind, &i, &j, shell) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
