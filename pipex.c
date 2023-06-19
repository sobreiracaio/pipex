/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:47:46 by crocha-s          #+#    #+#             */
/*   Updated: 2023/06/19 16:45:59 by crocha-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process (char **argv, char **envp, int *fd)
{
	int fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close (fd[1]);
	execute(argv[3],envp);
}



int main (int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;

	if (argc == 5)
	{
		if(pipe(fd) == -1)
			error();
		pid = fork();
		if(pid == -1)
			error();
		if(pid == 0)
		{
			child_process(argv, envp, fd);
			waitpid(pid, NULL, 0);
			parent_process(argv, envp, fd);
		}
		
	}
	else
	{
		ft_putstr_fd("Error: Bad arguments.", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>",1);
	}
	return (0);
}





// #include "pipex.h"

// void pipex (int fd1, int fd2, char *cmd1, char *cmd2)
// {
// 	int files[2];
// 	pid_t parent;
	
// 	pipe(files);
// 	parent = fork();
// 	if (parent == -1)
// 		return (perror("Fork: "));
// 	if (parent == 0) 
// 		child_process(fd1, cmd1);
// 	else
// 		parent_process(fd2, cmd2);
// }

// int main (int argc, char **argv)
// {
	
// }

// 

// #include <unistd.h>
// #include <stdio.h>
 
// int main()
// {
// 	char *args[3];
 
// 	args[0] = "ls";
// 	args[1] = "-l";
// 	args[2] = NULL;
// 	execve("/bin/ls", args, NULL);
// 	printf("This line will not be executed.\n");
 
// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>

// int main()
// {
// 	pid_t pid;
 
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
 
// 	if (pid == 0)
// 		printf("This is the child process. (pid: %d)\n", getpid());
// 	else
// 		printf("This is the parent process. (pid: %d)\n", getpid());
 
// 	return (0);
// }