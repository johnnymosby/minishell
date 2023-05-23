/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:13:32 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/23 17:18:15 by rbasyrov         ###   ########.fr       */
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
}	t_cmd_tbl;

typedef struct s_shell
{
	int			argc;
	char		**argv;
	char		**envs;
	char		*prompt;
	char		*input;
	char		*trimmed_input;
	int			exit_code;
	int			if_history_exists;
	t_tkn_tbl	*tkn_tbl;
}	t_shell;

#endif