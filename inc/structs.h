/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:13:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/22 20:09:52 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	FT_QUOTE,
	FT_DQUOTE,
	FT_GREAT,
	FT_DGREAT,
	FT_LESS,
	FT_DLESS,
	FT_PIPE,
	FT_SPACE,
	FT_WORD
}	t_type;

typedef enum e_cmd
{
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
	FT_UNSET,
	FT_DLESS,
	FT_ENV,
	FT_EXIT,
	FT_OTHER
}	t_cmd;

typedef struct s_tkn
{
	t_type	type;
	char	*cntnt;
}	t_tkn;

typedef struct s_tkn_tbl
{
	t_tkn	*tkns;
	int		max_n_tkns;
	int		n_tkns;
}	t_tkn_tbl;

typedef struct s_cmd_tbl
{
	char	*cmd;
	char	**args;
	int		in;
	char	*in_file;
	int		out;
	char	*out_file;
	int		n_args;
	int		max_n_args;
}	t_cmd_tbl;

typedef struct s_shell
{
	int			argc;
	char		**argv;
	char		**envs;
	char		*prompt;
	char		*input;
	char		*trimmed_input;
	int			std_in_out[2];
	int			exit_code;
	int			if_history_exists;
	t_tkn_tbl	*tkn_tbl;
	int			n_cmd_tbls;
	t_cmd_tbl	*cmd_tbls;
}	t_shell;

#endif