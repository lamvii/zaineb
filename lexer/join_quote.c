/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:06:53 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 04:41:00 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*creat_s_quote_token(t_token *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = S_QUOTE;
	new->next = NULL;
	new->prev = NULL;
	new->data = NULL;
	token = token->next;
	while (token && token->type != S_QUOTE)
	{
		new->data = join_quotes_data(new->data, token->data);
		token = token->next;
	}
	return (new);
}

int	join_s_quote(t_token **head, t_token **token)
{
	t_token	*new;
	t_token	*start;
	t_token	*end;

	start = *token;
	end = (*token)->next;
	while (end->type != S_QUOTE)
		end = end->next;
	new = creat_s_quote_token(*token);
	if (!new)
		return (0);
	new->prev = start->prev;
	new->next = end->next;
	if (end->next)
		end->next->prev = new;
	if (start->prev)
		start->prev->next = new;
	if (!(*token)->prev)
		*head = new;
	*token = new;
	end->next = NULL;
	start->prev = NULL;
	free_tokens(&start);
	return (1);
}

t_token	*creat_d_quote_token(t_token *token, t_env *env)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = D_QUOTE;
	new->next = NULL;
	new->prev = NULL;
	new->data = NULL;
	token = token->next;
	while (token && token->type != D_QUOTE)
	{
		if (token->type == DOLLAR && token->next && token->next->type == WORD)
		{
			new->data = join_quotes_data(new->data,
					dollar_v(token->next->data, env));
			token = token->next->next;
		}
		else
		{
			new->data = join_quotes_data(new->data, token->data);
			token = token->next;
		}
	}
	return (new);
}

int	join_d_quote(t_token **head, t_token **token, t_env *env)
{
	t_token	*new;
	t_token	*start;
	t_token	*end;

	start = *token;
	end = (*token)->next;
	while (end && end->type != D_QUOTE)
		end = end->next;
	new = creat_d_quote_token(*token, env);
	if (!new)
		return (0);
	new->prev = start->prev;
	new->next = end->next;
	if (end->next)
		end->next->prev = new;
	if (start->prev)
		start->prev->next = new;
	if (!(*token)->prev)
		*head = new;
	*token = new;
	end->next = NULL;
	start->prev = NULL;
	free_tokens(&start);
	return (1);
}

int	join_quotes(t_token **token, t_env *env)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		while (run && (run->type != S_QUOTE && run->type != D_QUOTE))
			run = run->next;
		if (run && run->type == S_QUOTE)
		{
			if (run && run->next->type == S_QUOTE)
				delete_empty_quotes(token, &run);
			else if (!join_s_quote(token, &run))
				return (0);
		}
		else if (run && run->type == D_QUOTE)
		{
			if (run && run->next->type == D_QUOTE)
				delete_empty_quotes(token, &run);
			else if (!join_d_quote(token, &run, env))
				return (0);
		}
		if (run)
			run = run->next;
	}
	return (1);
}
