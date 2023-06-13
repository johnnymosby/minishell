/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/11 15:19:18 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_cd.h"
#include "builts.h"

int ft_is_envar(char *s, char *env)
{
    
}
/*
This function changes the address of the dicrectory: 
old and current dicrectory addresses are updated
*/
int change_address(char *old, char **env)
{
    int MAX_PATH = 256;
    char    s[MAX_PATH];

    if (!getcwd(s, MAX_PATH))
        return(1);
    if(!ft_is_envar("PWD", *env)) //write ft_is_envar 
        create_envar("PWD", env); // write this function
    update_envar("PWD", s, *env); // write this function
    if(!ft_is_envar("OLDPWD", *env))
        create_envar("OLDPWD", env);
    update_envar("OLDPWD", old, *env);    
    return(0);
}

/*
this function performs change of directory
*/
int ft_cd_init(t_list *token, t_list **env, char *new)
{
    char    *s;
    int     ex_code;

    if (!token)
        ex_code = go_to_home(env, new); // write this function
    else if (token->next != 0)
        ex_code = cd_error_message("cd", "extra argument");
    else 
    {
        if (!ft_strcmp(token->content, "-"))
            ex_code = change_to_old(new, env);
        else if (chdir(arg) == 0)
            ex_code = change_address(new, env);
        else
            ex_code = 
    }
}