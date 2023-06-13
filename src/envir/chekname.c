/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:08:07 by maruzibo          #+#    #+#             */
/*   Updated: 2023/05/29 19:02:04 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
int is_delimit(char c)
{
    if (ft_isspace(c) || c == '"' 
        || c == '\'' || c == '/')
        return (1);
    else 
        return (0);
}
ft_exit(int code)
{
    //free somethings
    exit(code);
}
int ft_valid_name(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (i == 0 && s[i] >= '0' && s[i] <= '9')
            return (0);
        else if (s[i] != '_' && !ft_isalnum(s[i]))
            return (0);
        i++;
    }
    return (1);
}
/*
This function checks if  given string name contains an
environment variable.
*/
int ft_exist_name(char *name, t_list *env)
{
    int i;
    char    *s;

    if (!env )
        return (0);
    while(env)
    {
        i = 0;
        s = (char *)env->content;
        while(s[i] && name[i])
        {
            if(s[i] != name[i])
                break;
            i++;
        }
        if(!name[i] || ft_isspace(name[i])
            && (s[i] = '=' || !s[i]))
            return (1);
        env = env->next;
    }
    return(0);
}

/*
This function cuts words into pieces a possible variable names and words bounded with token 
delimiters. If the string starts with $ it gives a variable name.
*/
char *ft_scissor(char *s)
{
    int i;
    char *res;

    i = 0;
    if(s[i] == '$')
        i++;
    while(s[i] && s[i] != '$')
    {
        if(is_delimit(s[i]) || s[i] == '=')
            break ;
        i++;
    }
    res = ft_substr(s, 0, i);
    if (!res)
        ft_exit(1);
    return (res);
}