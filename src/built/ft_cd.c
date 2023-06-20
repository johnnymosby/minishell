/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <maruzibo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:16:01 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/20 15:36:59 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_cd.h"
#include "builts.h"

/*
This function changes the address of the dicrectory: 
old and current dicrectory addresses are updated
*/
int change_address(char **env, char *new)
{
    char    s[MAX_PATH];

    if (!getcwd(s, MAX_PATH))
        return(2);
    if(!is_in_envs("PWD", env))  
        ft_set_new_env(env, "PWD", s);
    s = ft_getenv(env, "PWD");
    ft_set_new_env(env, "PWD", new);
    if(!is_in_envs("OLDPWD", cmd->env))  
        ft_set_new_env(cmd, "OLDPWD", s);
    ft_set_new_env(env, "OLDPWD", s);  
    return(0);
}
int  go_to_oldpwd(t_shell *shell)
{
    char    *old;

    if (!is_in_envs("OLPPWD"))
        code = error_message("ch", "no OLDPWD");
    else
    {
        if (!chdir(old))
        {
            code = change_address(shell->envs, old);
        }
        else 
            code = error_message("chdir", "Chdir Error");
    }
}
int go_to_home(t_shell *shell)
{
    char *hom;
    int     code;
    
    if (!is_in_envs("HOME"))
        ft_set_new_env(shell->envs, "HOME", "/home");
    else
    {
        hom = ft_getenv(shell->envs, "HOME");
        if (!chdir(hom))
            code = change_address(shell->envs, "HOME");
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
int ft_cd_init(t_shell *shell)
{
    int     ex_code;
    char    **cd_args;
    
    cd_args = cmd->cmd_tbls->args;
    if (!cd_args) //no argument for cd it goes to home
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
	return (ex_code);
}
