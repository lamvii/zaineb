/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 06:32:43 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 01:05:39 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	elimine_dollar(t_token **token)
{
	t_token	*tem;

	tem = *token;
	tem->next->prev = tem->prev;
	if (tem->prev)
		tem->prev->next = tem->next;
	*token = tem->next;
	tem->next = NULL;
	tem->prev = NULL;
	free_tokens(&tem);
}

int	replace_dollar_with_value_elem(t_token **token, t_env *env)
{
	t_token	*new;
	t_token	*tem;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = WORD;
	new->data = dollar_v((*token)->next->data, env);
	tem = *token;
	new->next = tem->next->next;
	new->prev = tem->prev;
	if (tem->prev)
		tem->prev->next = new;
	tem->prev = NULL;
	if (tem->next->next)
		tem->next->next->prev = new;
	tem->next->next = NULL;
	free_tokens(&tem);
	*token = new;
	return (1);
}

void	chanche_quote_type(t_token **token)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		if (run->type == D_QUOTE || run->type == S_QUOTE)
			run->type = WORD;
		run = run->next;
	}
}

int	change_dollars(t_token **token, t_env *env)
{
	t_token	*run;

	run = *token;
	while (run)
	{
		while (run && run->type != DOLLAR)
			run = run->next;
		if (run && run->next && (run->next->type == D_QUOTE
				|| run->next->type == S_QUOTE))
			elimine_dollar(&run);
		else if (run && run->next && run->next->type == WORD)
		{
			if (!replace_dollar_with_value_elem(&run, env))
				return (0);
		}
		else if (run)
		{
			run->type = WORD;
			run = run->next;
		}
	}
	chanche_quote_type(token);
	return (1);
}
//done well tested
