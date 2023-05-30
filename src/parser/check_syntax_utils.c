/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:53:05 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/05/30 18:55:07 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tkn_type_to_str(t_type tkn_type)
{
	if (tkn_type == FT_DGREAT || tkn_type == FT_GREAT)
		return (">");
	else if (tkn_type == FT_DLESS || tkn_type == FT_LESS)
		return ("<");
	else if (tkn_type == FT_PIPE)
		return ("|");
	else
		return ("");
}

int	if_redirection(t_type tkn_type)
{
	if (tkn_type == FT_LESS
		|| tkn_type == FT_DLESS
		|| tkn_type == FT_GREAT
		|| tkn_type == FT_DGREAT)
		return (TRUE);
	else
		return (FALSE);
}
