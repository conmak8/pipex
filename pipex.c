/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:06:21 by cmakario          #+#    #+#             */
/*   Updated: 2024/03/04 00:37:04 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_pth(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*re;
	char	*re1;

	i = -1;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while ((env[++i]) && (ft_strncmp(env[i], "PATH=", 5)))
	if (!env[i])
		return (NULL);
	paths = ft_split(&env[i][5], ':');
	i = -1;
	while (paths && paths[++i])
	{
		re = ft_strjoin(paths[i], "/");
		re1 = ft_strjoin(re, cmd);
		free(re);
		if (access(re1, F_OK | X_OK) == 0)
			return (free_ar_split(paths), re1);
		free(re1);
	}
	return (free_ar_split(paths), write(2, NULL, 14), NULL);
}

void	run1(char **cmd, int fd[2], char **env, char *input)
{
	int		inf;
	char	*command;

	inf = open(input, O_RDONLY);
	if (inf < 0)
		ft_exit("file cannot open\n", cmd, fd, 1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit("dup2 failed\n", cmd, fd, 3);
	if (dup2(inf, STDIN_FILENO) == -1)
		ft_exit("dup2 failed\n", cmd, fd, 3);
	close(inf);
	close(fd[0]);
	close(fd[1]);
	command = get_pth(cmd[0], env);
	if (!command)
		ft_exit("command not found\n", cmd, fd, 1);
	if (execve(command, cmd, env) == -1)
		ft_exit("execve failed\n", cmd, fd, 4);
}

void	run2(char **cmd, int fd[2], char **env, char *output)
{
	int		outf;
	char	*command;

	outf = open(output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outf < 0)
		ft_exit("file cannot open or create\n", cmd, fd, 1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit("dup2 failed\n", cmd, fd, 3);
	if (dup2(outf, STDOUT_FILENO) == -1)
		ft_exit("dup2 failed\n", cmd, fd, 3);
	close(outf);
	close(fd[1]);
	close(fd[0]);
	command = get_pth(cmd[0], env);
	if (!command)
		ft_exit("command not found\n", cmd, fd, 1);
	if (execve(command, cmd, env) == -1)
		ft_exit("execve failed\n", cmd, fd, 4);
}

static int	child_process(char **av, int fd[2], char **env, char scenario)
{
	char	**cmd;

	if (scenario == 'a')
	{
		cmd = ft_split(av[2], ' ');
		if (cmd == NULL)
			return (close(fd[0]), close(fd[1]), 1);
		run1(cmd, fd, env, av[1]);
	}
	else
	{
		cmd = ft_split(av[3], ' ');
		if (cmd == NULL)
			return (close(fd[0]), close(fd[1]), 1);
		run2(cmd, fd, env, av[4]);
	}
	free_ar_split(cmd);
	return (0);
}

int	main(int ai, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ai != 5)
		return (write(2, "arg num wrong\n", 14), 1);
	if (pipe(fd) < 0)
		return (write(2,"error\n", 6), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (close(fd[0]), close(fd[1]), 4);
	if (pid1 == 0)
		child_process(av, fd, env, 'a');
	pid2 = fork();
	if (pid2 == -1)
		return (close(fd[0]), close(fd[1]), wait(NULL), 4);
	if (pid2 == 0)
		child_process(av, fd, env, 'b');
	return (close(fd[0]), close(fd[1]), wait(NULL), wait(NULL), 0);
}
