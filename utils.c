/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:06:21 by cmakario          #+#    #+#             */
/*   Updated: 2024/03/03 18:28:44 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//free double pointer array
void	free_ar_split(char **ar_split)
{
	int	i;

	i = 0;
	while (ar_split[i])
	{
		free(ar_split[i]);
		i++;
	}
	free(ar_split);
}

void	ft_exit(char *error_message, char **array, int fd[2], int exit_status)
{
	if (error_message != NULL)
		write(2, error_message, ft_strlen(error_message));
	free_ar_split(array);
	close(fd[0]);
	close(fd[1]);
	exit(exit_status);
}
