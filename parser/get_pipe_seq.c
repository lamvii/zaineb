/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:25:25 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 03:09:45 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe_seq	*create_pipe_seq(t_token **token)
{
	t_pipe_seq	*pipe_seq;

	pipe_seq = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
	if (!pipe_seq)
		return (NULL);
	pipe_seq->cmd = NULL;
	if (!get_command(token, &pipe_seq->cmd))
		return (NULL);
	pipe_seq->next = NULL;
	return (pipe_seq);
}

t_pipe_seq	*last_pipe_seq(t_pipe_seq *pipe_seq)
{
	while (pipe_seq->next != NULL)
		pipe_seq = pipe_seq->next;
	return (pipe_seq);
}

int	get_pipe_seq(t_pipe_seq **pipe_seq, t_token **token)
{
	t_pipe_seq	*last;
	t_pipe_seq	*new;

	new = create_pipe_seq(token);
	if (!new)
		return (0);
	if (!(*pipe_seq))
		*pipe_seq = new;
	else
	{
		last = last_pipe_seq(*pipe_seq);
		last->next = new;
	}
	return (1);
}
