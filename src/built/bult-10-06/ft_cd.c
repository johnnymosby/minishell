/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/14 19:35:14 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_cd.h"
#include "builts.h"

/*
This function changes the address of the dicrectory: 
old and current dicrectory addresses are updated
*/
int change_address(t_shell *cmd, char *new)
{
    char    s[MAX_PATH];
    //char    s1[MAX_PATH];

    if (!getcwd(s, MAX_PATH))
        return(2);
    if(!is_in_envs("PWD", cmd->env))  
        ft_set_new_env(cmd, "PWD", s);
    s = ft_getenv(cmd, "PWD");
    ft_set_new_env(cmd, "PWD", new);
    //if(!is_in_envs("OLDPWD", cmd->env))  
      //  ft_set_new_env(cmd, "OLDPWD", s);
    //else 
        ft_set_new_env(cmd, "OLDPWD", s);  
    return(0);
}
int  go_to_old_dir(t_shell *cmd)
{
    char    *old;

    old = ft_getenv(cmd, "OLDPWD");
    chdir(old);
    
}
int go_to_home(t_shell *cmd)
{
    char *hom;
    int     code;
    
    if (!is_in_envs("HOME"))
        ft_set_new_env(cmd, "HOME", "/home");
    else
    {
        hom = ft_getenv(cmd, "HOME");
        if (!chdir(hom))
            code = change_address(cmd, "HOME");
        else 
            code = error_message("chdir", "Chdir Error");
    }
    if(hom)
        free(hom);
    return (code);
} 


/*
Changes the current working directory
*/
int ft_cd_init(t_shell *cmd)
{chdir
    char    *s;
    int     ex_code;
    char    **cd_args;
    
    cd_args = cmd->cmd_tbls->args;
    if (!cd_args) //this is the case: cd (nothing here)
        ex_code = go_to_home(cmd); 
    else if (nb_of_rows(cd_args) > 1) // more than 1 arg for cd
        ex_code = error_message("cd", "too many arguments");
    else //here we change the working directory
    {
       
       if (!ft_strcmp(arg, "-"))
            ex_code = go_to_old_dir(pwd, env);
		else if (chdir(arg) == EXIT_SUCCESS)
		    ex_code = change_address(cmd, pwd);
		else
            ex_code = invalid_error("cd", errno, arg);
	}
	return (status);
}
