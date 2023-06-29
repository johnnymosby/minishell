/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:13:56 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/29 22:22:05 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "structs.h"
# include "defines.h"
// macros:		EXIT_SUCCESS, EXIT_FAILURE
// functions:	exit, getenv
# include <stdlib.h>

// functions:	printf, perror
# include <stdio.h>

// macros:		STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO
// functions:	execve, unlink, access
# include <unistd.h>

// functions:	readline
# include <readline/readline.h>

// macros:		SIGINT, SIGQUIT, SIG_IGN
// functions:	signal
# include <signal.h>

// functions:	rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
				//add_history
# include <readline/history.h>

// variable:		errno
# include <errno.h>

// functions:	strerror
# include <string.h>

# include <sys/ioctl.h>
# include <termios.h>

// macros:		S_IRWXU (user read, write, and execute permissions)
# include <sys/stat.h>

// functions:	open
# include <fcntl.h>

// functions:	opendir, readdir, closedir
# include <dirent.h>

// functions:	wait, waitpid
# include <sys/wait.h>

// main/...
//	 .../main.c

// utils/...
//		.../general_utils.c
void	free_if_not_null(void **data);
//		.../history.c
void	history(t_shell *shell);

// signals/...
//	 .../check_signals.c
void	check_signals(t_shell *shell);
void	check_signals_in_parent(struct termios *termios);
void	check_signals_in_child(struct termios *mirror_termios);

// loop/...
//	 .../minishell_loop.c
void	minishell_loop(t_shell *shell);

// init/...
//	 .../init.c
void	init_minishell(t_shell *shell, char **envs);
//	 .../init_tkn_tbl.c
void	init_tkn_tbl(t_shell *shell);
void	increase_tkn_tbl(t_shell *shell);
//	 .../init_cmd_and_args.c
int		init_cmd_and_args(t_tkn_tbl *tkn_tbl, t_shell *shell, int i, int j);

// lexer/...
//	 .../lexer.c
int		lexer(t_shell *shell);
void	lexer_loop(t_shell *shell);
int		add_token(t_shell *shell, int i);
int		add_quote(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell);
int		add_dquote(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell);
//	 .../add_token.c
int		add_word(t_tkn_tbl *tkn_tbl, const char *inp, int i, t_shell *shell);
int		add_less(t_tkn_tbl *tkn_tbl, const char *inp, int i);
int		add_great(t_tkn_tbl *tkn_tbl, const char *inp, int i);
int		add_pipe(t_tkn_tbl *tkn_tbl);
//	 .../add_space.c
int		add_space(t_tkn_tbl *tkn_tbl, const char *inp, int i);

// expander/...
//	 .../expander.c
char	*find_env_value(char **envs, char *var, int len, t_shell *shell);
int		expander(t_shell *shell);
//	 .../expander_utils.c
int		env_finishes_with_equal_sign(char *var, int len);
void	remove_repeating_dollars(char *s);
void	remove_trailing_dollar(char *s);
int		find_len_var(char *s);
void	cut_out_variable(char *s, int ind);
//	 .../put_value.c
void	put_value(char *value, int ind, t_tkn *tkn, t_shell *shell);
//	 .../expand_exit_code.c
int		expand_exit_code(int ind, t_tkn *tkn, t_shell *shell);
int		skip_dollar_number(char *s);
//	 .../expand_variables_in_heredoc.c
void	expand_variables(char *s, int fd, t_shell *shell);

// parser/...
//	 .../parser.c
int		parser(t_shell *shell);
//	 .../concatenate_words.c
void	shift_array_by_one_to_left(t_tkn_tbl *tkn_tbl, int i);
void	concatenate_words(t_tkn_tbl *tkn_tbl, t_shell *shell);
//	 .../check_syntax.c
void	print_syntax_error(char *error);
int		handle_redirection(t_tkn_tbl *tkn_tbl, int *i);
int		handle_pipe(t_tkn_tbl *tkn_tbl, int *i);
void	skip_words(t_tkn_tbl *tkn_tbl, int *i);
int		check_syntax(t_tkn_tbl *tkn_tbl, t_shell *shell);
//	 .../check_syntax_utils.c
char	*tkn_type_to_str(t_type tkn_type);
int		if_redirection(t_type tkn_type);
//	 .../check_access.c
int		check_access(t_tkn_tbl *tkn_tbl, t_shell *shell);
//	 .../construct_cmd_tables.c
void	construct_cmd_tables(t_tkn_tbl *tkn_tbl, t_shell *shell);
//	 .../handle_heredocs.c
int		handle_heredocs(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls,
			t_shell *shell);
int		find_last_heredoc_in_cmd(t_tkn_tbl *tkn_tbl, int i);
//	 .../imitate_heredocs.c
int		imitate_heredocs(t_tkn_tbl *tkn_tbl, int i, int last_heredoc_ind,
			t_shell *shell);
//	 .../heredocs_utils.c
int		find_last_heredoc_in_cmd(t_tkn_tbl *tkn_tbl, int i);
int		skip_cmd(t_tkn_tbl *tkn_tbl, int i);

// execute/...
//	 .../execute.c
void	execute(t_shell *shell);
//	 .../handle_redirections.c
int		handle_redirections(t_tkn_tbl *tkn_tbl, t_cmd_tbl *cmd_tbls,
			int n_cmd_tbl, t_shell *shell);
//	 .../handle.c
void	close_fd(int *fd);
void	handle_fd(int *fd);
int		handle_infile(int i, int *prevpipe, t_shell *shell);
int		handle_outfile(int *fd, int i, int *prevpipe, t_shell *shell);
//	.../execute_with_pipes.c
void	execute_with_pipes(t_shell *shell);
//	.../execute_last_cmd.c
int		execute_last_cmd(t_shell *shell, int i, int prevpipe);
//	 .../construct_pathname.c
char	*construct_pathname(char *cmd, t_shell *shell);
//	 .../operate_with_filepaths.c
char	*find_folder_with_command(char *cmd, const char *path,
			t_shell *shell);
int		is_directory(char *cmd, t_shell *shell);
//	 .../execute_utils.c
void	add_command_to_args(char *pathname, int i, t_shell *shell);
void	enable_redirections(t_cmd_tbl *cmd_tbls, int i);
void	finalise_exit_code(t_shell *shell, int status);
//	 .../execute_without_pipes.c
void	execute_without_pipes(t_shell *shell);

// builtins/...
//	 .../builtins_entrypoint.c
t_cmd	what_command(char *cmd);
int		execute_builtin(t_cmd_tbl *cmd_tbl, t_shell *shell);
//	 .../ft_cd.c
void	change_pwd_and_oldpwd(char *oldpwd_val, t_shell *shell);
int		ft_cd(t_cmd_tbl *cmd_tbl, t_shell *shell);
//	 .../ft_echo.c
int		ft_echo(char **ss);
//	 .../ft_pwd.c
int		ft_pwd(void);
//	 .../ft_exit.c
int		ft_exit(t_shell *shell, t_cmd_tbl *cmd_tbl);
//	 .../ft_env.c
int		ft_env(t_shell *shell, char **args);
//	 .../ft_export.c
int		ft_export(t_shell *shell, char **args);
//	 .../ft_unset.c
int		ft_unset(t_shell *shell, char **args);
//	 .../environment_utils.c
void	remove_env_variable(t_shell *shell, int i);
char	*get_env_var_name(t_shell *shell, char *var);
int		return_env_var_index(char *var, char **env);
int		is_in_envs(char *var, char **env);
void	add_new_env(char *env_var, t_shell *shell);
//	 .../check_environment_identifier.c
int		is_valid_identifier(char *cmd, char *s);
void	write_identifier_error_message(char *cmd, char *s);
//	 .../go_to_a_directory.c
int		go_to_dir(char *pathname, t_shell *shell);
int		go_to_old_dir(t_shell *shell);
int		go_to_home(t_shell *shell);

// 	exit/...
//	 .../exit.c
void	clean_exit(t_shell *shell, int exit_code);
void	exit_if_true(t_shell *shell, int if_true, int exit_code);
//	 .../free_cmd_tbl.c
void	free_str_array(char ***args, int n_args);
void	close_files(t_cmd_tbl *cmd_tbl);
void	free_cmd_tbl(t_cmd_tbl *cmd_tbl);
//	 .../clean_shell.c
void	set_exit_code(t_shell *shell, int exit_code);
void	free_input(t_shell *shell);
void	clean_shell(t_shell *shell);
//	 .../error.c
void	write_file_error_message(const char *pathname);
void	print_error_and_exit(t_shell *shell);
void	write_failed_message(const char *pathname);
//	 .../clean_data_structures.c
void	free_tkn_tbl(t_tkn_tbl **tkn_tbl);
void	free_cmd_tbls(t_cmd_tbl **cmd_tbls, int n);

//TO DELETE
void	print_tokens(t_shell *shell);
void	print_contents(t_shell *shell);
char	*translate_enum(int n);

extern int	g_status;

#endif