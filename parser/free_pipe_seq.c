/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:22:06 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 04:13:24 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_elem_ioredirect(t_ioredirect **redirect)
{
	free((*redirect)->file_name);
	free(*redirect);
}

void	free_cmd_args(char ***arg)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		free((*arg)[i]);
		i++;
	}
	free(*arg);
}

void	free_pipe_elem(t_pipe_seq **pipe_seq)
{
	t_ioredirect	*tem;

	while ((*pipe_seq)->cmd->cmd_pref)
	{
		tem = (*pipe_seq)->cmd->cmd_pref;
		(*pipe_seq)->cmd->cmd_pref = (*pipe_seq)->cmd->cmd_pref->next;
		free_elem_ioredirect(&tem);
	}
	if ((*pipe_seq)->cmd->cmd)
		free((*pipe_seq)->cmd->cmd);
	while ((*pipe_seq)->cmd->cmd_suff->redirection)
	{
		tem = (*pipe_seq)->cmd->cmd_suff->redirection;
		(*pipe_seq)->cmd->cmd_suff->redirection = tem->next;
		free_elem_ioredirect(&tem);
	}
	if ((*pipe_seq)->cmd->cmd_suff->args)
		free_cmd_args(&((*pipe_seq)->cmd->cmd_suff->args));
	free((*pipe_seq)->cmd->cmd_suff);
	free((*pipe_seq)->cmd);
	free(*pipe_seq);
}

void	free_pipe_seq(t_pipe_seq **pipe_seq)
{
	t_pipe_seq	*tem;

	while (*pipe_seq)
	{
		tem = *pipe_seq;
		*pipe_seq = (*pipe_seq)->next;
		free_pipe_elem(&tem);
	}
}
