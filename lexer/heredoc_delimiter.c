/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 01:04:44 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 05:54:02 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prev_is_hdoc(t_token *token)
{
	token = token->prev;
	while (token && token->type == SPACE)
		token = token->prev;
	if (token && token->type == HEREDOC)
		return (1);
	return (0);
}

t_token	*new_delimiter(t_token **token)
{
	t_token	*delim;

	delim = (t_token *)malloc(sizeof(t_token));
	if (!delim)
		return (NULL);
	delim->type = WORD;
	delim->data = NULL;
	delim->next = NULL;
	delim->prev = (*token)->prev;
	(*token)->prev->next = delim;
	return (delim);
}

int	create_delimiter(t_token **token)
{
	t_token	*tem;
	t_token	*delim;

	delim = new_delimiter(token);
	if (!delim)
		return (0);
	tem = *token;
	if ((*token)->next && ((*token)->next->type == S_QUOTE || (*token)->next->type == D_QUOTE))
		(*token) = (*token)->next;
	while (*token && ((*token)->type != SPACE && (*token)->type != PIPE
			&& (*token)->type < REDIREC_IN))
	{
		if ((*token)->type == D_QUOTE)
		{
			(*token) = (*token)->next;
			if ((*token)->type == D_QUOTE)
			{
				*token = (*token)->next;
				continue ;
			}
			while (*token && (*token)->type != D_QUOTE)
			{
				delim->data = join_quotes_data(delim->data, (*token)->data);
				*token = (*token)->next;
			}
		}
		else if ((*token)->type == S_QUOTE)
		{
			(*token) = (*token)->next;
			if ((*token)->type == S_QUOTE)
			{
				*token = (*token)->next;
				continue ;
			}
			while (*token && (*token)->type != S_QUOTE)
			{
				delim->data = join_quotes_data(delim->data, (*token)->data);
				*token = (*token)->next;
			}
		}
		else
			delim->data = join_quotes_data(delim->data, (*token)->data);
		*token = (*token)->next;
	}
	delim->next = *token;
	if (*token)
	{
		(*token)->prev->next = NULL;
		(*token)->prev = delim;
	}
	free_tokens(&tem);
	return (1);
}

int	join_heredoc_delimiter(t_token **token)
{
	t_token	*run;

	run = (*token);
	while (run)
	{
		while (run && run->type != HEREDOC)
			run = run->next;
		if (!run)
			return (1);
		run = run->next;
		while (run && run->type == SPACE)
			run = run->next;
		if (!create_delimiter(&run))
			return (0);
	}
	// check_all_heredoc_have_delimiter(*token);
	// in case $"" delimiter is null implique segfault :)
	return (1);
}
