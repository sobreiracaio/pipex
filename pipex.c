/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:47:46 by crocha-s          #+#    #+#             */
/*   Updated: 2023/06/13 18:14:05 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex (int fd1, int fd2, char *cmd1, char *cmd2)
{
	int files[2];
	pid_t parent;
	
	pipe(files);
	parent = fork();
	if (parent == -1)
		return (perror("Fork: "));
	if (parent == 0) 
		child_process(fd1, cmd1);
	else
		parent_process(fd2, cmd2);
}

int main (int argc, char **argv)
{
	
}