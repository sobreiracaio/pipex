/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:30:59 by admin             #+#    #+#             */
/*   Updated: 2023/06/19 18:34:46 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char *cmd, char **envp)
{
    int i;
    char **paths;
    char *path;
    char *part_path;
    i = 0;
    
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free (part_path);
        if(access(path, F_OK) == 0)
            return(path);
        free (path);
        i++;
    }
     i = 0;
     while (paths[i++])
        free(paths[i]);
    free(paths);
    return (0);   
}

void error(void)
{
    perror("Error");
    exit(EXIT_FAILURE);
}

void execute(char *argv, char **envp)
{
    char **cmd;
    int i;
    char *path;

    i = 0;
    cmd = ft_split(argv, ' ');
    path = find_path(cmd[0], envp);
    if (!path)
    {
        while (cmd[i++])
            free(cmd[i]);
        free (cmd);
        error();
    }
    if(execve(path, cmd, envp) == -1)
    {
        //  while (cmd[i++])
        //     free(cmd[i]);
        // free (cmd);
        error();
    }
}   


