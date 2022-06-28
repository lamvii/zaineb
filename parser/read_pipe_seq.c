/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipe_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:21:20 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 04:22:55 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_cmd_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("arg : %s \n", arg[i]);
		i++;
	}
}

void	read_pipe_seq(t_pipe_seq *pipe_seq)
{
	t_ioredirect	*cmd_pref;
	t_ioredirect	*cmd_suff;

	while (pipe_seq)
	{
		cmd_pref = pipe_seq->cmd->cmd_pref;
		while (cmd_pref)
		{
			printf("redirection filename = %s\n", cmd_pref->file_name);
			cmd_pref = cmd_pref->next;
		}
		if (pipe_seq->cmd->cmd)
			printf("command_name = %s\n", pipe_seq->cmd->cmd);
		cmd_suff = pipe_seq->cmd->cmd_suff->redirection;
		while (cmd_suff)
		{
			printf("redirection filename = %s\n", cmd_suff->file_name);
			cmd_suff = cmd_suff->next;
		}
		if (pipe_seq->cmd->cmd_suff->args)
			read_cmd_args(pipe_seq->cmd->cmd_suff->args);
		pipe_seq = pipe_seq->next;
	}
}
