/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:07:34 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/13 17:14:55 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_redirections(t_cmd_tbl *cmd_tbl)
{
	if (cmd_tbl->in != -1)
	{
		close(cmd_tbl->in);
		cmd_tbl->in = -1;
	}
	if (cmd_tbl->out != -1)
	{
		close(cmd_tbl->in);
		cmd_tbl->out = -1;
	}
}

int	open_file(const char *pathname, t_type type, int n_cmd_tbl, t_shell *shell)
{
	int	fd;

	if (type == FT_LESS && access(pathname, R_OK) == -1)
	{
		write_file_error_message(pathname);
		return (FALSE);
	}
	if (type == FT_LESS)
		fd = open(pathname, O_RDONLY);
	else if (type == FT_DGREAT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == FT_GREAT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd <= -1)
	{
		write_file_error_message(pathname);
		clean_exit(shell, TRUE);
	}
	if (type == FT_LESS)
	{
		if (shell->cmd_tbls[n_cmd_tbl].in != -1)
			close(shell->cmd_tbls[n_cmd_tbl].in);
		shell->cmd_tbls[n_cmd_tbl].in = fd;
	}
	else if (type == FT_GREAT || type == FT_DGREAT)
	{
		if (shell->cmd_tbls[n_cmd_tbl].out != -1)
			close(shell->cmd_tbls[n_cmd_tbl].out);
		shell->cmd_tbls[n_cmd_tbl].out = fd;
	}
	return (TRUE);
}

int	open_heredoc(t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
{
	int		fd;
	char	*pathname;
	char	*file_id;

	file_id = ft_itoa(n_cmd_tbl);
	if (file_id == NULL)
		clean_exit(shell, TRUE);
	pathname = ft_strjoin("/tmp/tmp_heredoc_", file_id);
	free(file_id);
	if (pathname == NULL)
		clean_exit(shell, TRUE);
	if (access(pathname, R_OK) != 0)
	{
		write_file_error_message(pathname);
		free(pathname);
		return (FALSE);
	}
	fd = open(pathname, O_RDONLY);
	if (fd <= -1)
	{
		write_file_error_message(pathname);
		free(pathname);
		clean_exit(shell, TRUE);
	}
	if (cmd_tbls[n_cmd_tbl].in != -1)
		close(cmd_tbls[n_cmd_tbl].in);
	cmd_tbls[n_cmd_tbl].in = fd;
	return (TRUE);
}

int	open_redirection(t_tkn_tbl *tkn_tbl, int n_cmd_tbl,
	int i, t_shell *shell)
{
	int		if_no_error;
	t_type	type;
	char	*pathname;

	type = tkn_tbl->tkns[i].type;
	pathname = tkn_tbl->tkns[i + 1].cntnt;
	if (type == FT_LESS || type == FT_GREAT || type == FT_DGREAT)
		if_no_error = open_file(pathname, type, n_cmd_tbl, shell);
	else if (type == FT_DLESS)
		if_no_error = open_heredoc(shell->cmd_tbls, n_cmd_tbl, shell);
	if (if_no_error == FALSE)
		return (FALSE);	
	return (TRUE);
}

int	handle_redirections(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls, int n_cmd_tbl, t_shell *shell)
{
	int		i;
	t_type	type;

	i = 0;
	while (i != tkn_tbl->n_tkns)
	{
		type = tkn_tbl->tkns[i].type;
		if (type == FT_LESS || type == FT_DLESS
			|| type == FT_GREAT || type == FT_DGREAT)
		{
			if (open_redirection(tkn_tbl, n_cmd_tbl, i, shell) == FALSE)
				return (FALSE);
			i += 2;
		}
		else
			i += 1;
	}
	return (TRUE);
}

int	find_path_variable(char **envs)
{
	int	i;

	i = 0;
	while (envs[i] != NULL)
	{
		if (ft_strncmp(envs[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_folder(const char *path, int n,  t_shell *shell)
{
	int		len;
	char	*folder;
	int		i;

	len = 0;
	while (path[n + len] != '\0' && path[n + len] != ':')
		len++;
	folder = malloc(sizeof(char) * (len + 2));
	if (folder == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		clean_exit(shell, TRUE);
	}
	i = 0;
	while (i != len)
	{
		folder[i] = path[n + i];
		i++;
	}
	folder[i] = '/';
	folder[i + 1] = '\0';
	return (folder);
}

char *get_next_folder_from_path(const char *path, int i, t_shell *shell)
{
	int		j;
	int		n;

	j = 0;
	n = 0;
	while (path[n] != '\0')
	{
		if (path[n] == '/')
			break ;
		n++;
	}
	while (j < i && path[n] != '\0')
	{
		if (path[n] == ':')
			j++;
		n++;
	}
	if (j != i)
		return (NULL);
	else
		return (extract_folder(path, n, shell));
}

char	*find_folder_with_command(char *cmd, const char *path, t_shell *shell)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*folder;
	int				i;

	i = 0;
	folder = get_next_folder_from_path(path, i, shell);
	while (folder != NULL)
	{
		if (access(folder, X_OK) != -1)
		{
			dir = opendir(folder);
			if (dir == NULL)
			{
				write_file_error_message(folder);
				free(folder);
				clean_exit(shell, TRUE);
			}
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (ft_strcmp(entry->d_name, cmd) == 0)
				{
					closedir(dir);
					return (folder);
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		free(folder);
		i++;
		folder = get_next_folder_from_path(path, i, shell);
	}
	return (NULL);
}

char	*construct_pathname(char *cmd, t_shell *shell)
{
	char	*pathname;
	char	*folder;
	int		path_ind;

	path_ind = find_path_variable(shell->envs);
	if (path_ind < 0)
		return (NULL);
	folder = find_folder_with_command(cmd, shell->envs[path_ind], shell);
	if (folder == NULL)
		return (NULL);
	pathname = ft_strjoin(folder, cmd);
	free(folder);
	if (pathname == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		clean_exit(shell, TRUE);
	}
	return (pathname);
}

void	add_command_to_args(char *pathname, int i, t_shell *shell)
{
	char		**new_argv;
	t_cmd_tbl	*cmd_tbl; 
	int			n;

	cmd_tbl = &(shell->cmd_tbls[i]);
	cmd_tbl->n_args += 1;
	new_argv = ft_calloc(cmd_tbl->n_args + 1, sizeof(char *));
	if (new_argv == NULL)
	{
		free(new_argv);
		clean_exit(shell, TRUE);
	}
	new_argv[0] = pathname;
	n = 1;
	while (n < cmd_tbl->n_args)
	{
		new_argv[n] = cmd_tbl->args[n - 1];
		n++;
	}
	free(cmd_tbl->args);
	cmd_tbl->args = new_argv;
}

void	execute_without_pipes(t_shell *shell)
{
	pid_t	pid;
	char	*pathname;
	int		status;

	if (handle_redirections(shell->tkn_tbl, shell->cmd_tbls, 0, shell) == FALSE)
		return ;
	pathname = construct_pathname(shell->cmd_tbls[0].cmd, shell);
	if (pathname == NULL)
	{
		write_file_error_message(shell->cmd_tbls[0].cmd);
		return ;
	}
	add_command_to_args(pathname, 0, shell);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		clean_exit(shell, TRUE);
	}
	else if (pid == 0)
	{
		if (shell->cmd_tbls[0].in != -1)
		{
			close(STDIN_FILENO);
			dup(shell->cmd_tbls[0].in);
		}
		if (shell->cmd_tbls[0].out != -1)
		{
			close(STDOUT_FILENO);
			dup(shell->cmd_tbls[0].out);
		}
		if (execve(pathname, shell->cmd_tbls->args, shell->envs) < 0)
			exit (1);
	}
	else
		waitpid(pid, &status, 0);
}

void	execute(t_shell *shell)
{
	if (shell->n_cmd_tbls <= 1)
	{
		execute_without_pipes(shell);
	}
}

int	execute_cmd(t_shell *shell, t_cmd_tbl *cmd_tb)
{
	return (TRUE);
}
