/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:30:59 by admin             #+#    #+#             */
/*   Updated: 2023/06/20 21:52:19 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error(void)
{
    perror("Error");
    exit(EXIT_FAILURE);
}

void free_split(char **str)
{
    int i;
    
    i = 0;
    while (str[i])
            free(str[i++]);
    free (str);
    
}

char *find_path(char *cmd, char **envp)
{
    int i;
    char **envp_paths;
    char *cmd_path;
    char *part_path;
    i = 0;
    
    while (!ft_strnstr(envp[i], "PATH=", 5))
        i++;
    envp_paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (envp_paths[i])
    {
        part_path = ft_strjoin(envp_paths[i], "/");
        cmd_path = ft_strjoin(part_path, cmd);
        free (part_path);
        if(access(cmd_path, F_OK) == 0)
        {
            free_split (envp_paths);
            return(cmd_path);
        }
            void free_split(char **str);
        free (cmd_path);
        i++;
    }
     i = 0;
    free_split(envp_paths);
    return (NULL);   
}


void execute(char *argv, char **envp)
{
    char **cmd;
    char *path;
  
    cmd = ft_split(argv, ' ');
    path = find_path(cmd[0], envp);
    if (!path)
    {
        free_split(cmd);
        free (path);
        exit(127);
    }
    if(execve(path, cmd, envp) == -1)
    {
        free_split(cmd);
        free(path);
        error();
    }
}   


