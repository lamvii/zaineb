/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:30:37 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 03:46:03 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(t_token **token, t_pipe_seq **pipe_seq)
{
	t_token		*search;
	t_token		*sub_token;

	while (*token)
	{
		search = *token;
		sub_token = *token;
		while ((search && search->type != PIPE))
			search = search->next;
		if (search != NULL)
		{
			search->prev->next = NULL;
			*token = search->next;
			search->next->prev = NULL;
			search->next = NULL;
			free_tokens(&search);
		}
		else
			*token = NULL;
		if (!get_pipe_seq(pipe_seq, &sub_token))
			return (malloc_error());
		// read_token(sub_token);
		// printf("----\n");
	}
	return (1);
}
