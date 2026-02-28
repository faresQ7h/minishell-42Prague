/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:10:44 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 16:15:56 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_children(t_shell *s)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == s->last_pid)
		{
			if (WIFEXITED(status))
				s->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				s->exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 20);
				else if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
		}
		pid = wait(&status);
	}
}
