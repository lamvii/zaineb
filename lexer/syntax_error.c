/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:31:08 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 04:40:40 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pass_quote_word(t_token	**token)
{
	int	token_type;

	token_type = (*token)->type;
	*token = (*token)->next;
	while (*token && (*token)->type != token_type)
		*token = (*token)->next;
	if (!(*token))
		return (0);
	return (1);
}

int	check_redirec_word(t_token **token)
{
	*token = (*token)->next;
	while (*token && (*token)->type == SPACE)
		*token = (*token)->next;
	if (*token && ((*token)->type == WORD || (*token)->type == DOLLAR))
		return (1);
	if (*token && ((*token)->type == D_QUOTE || (*token)->type == S_QUOTE))
	{
		if (!pass_quote_word(token))
			return (manage_syntax_error(D_QUOTE));
		return (1);
	}
	return (0);
}

int	check_pipe(t_token *token)
{
	t_token	*go_left;

	go_left = token;
	if (go_left->prev)
		go_left = go_left->prev;
	else
		return (0);
	while (go_left && go_left->type == SPACE)
		go_left = go_left->prev;
	if (token->next)
		token = token->next;
	else
		return (0);
	while (token && token->type == SPACE)
		token = token->next;
	if (!go_left || !token)
		return (0);
	return (1);
}

int	syntax_error(t_token **tok, t_env *env)
{
	t_token	*token;

	token = *tok;
	while (token)
	{
		if (token && (token->type == D_QUOTE || token->type == S_QUOTE))
			if (!pass_quote_word(&token))
				return (manage_syntax_error(D_QUOTE));
		if (token && token->type >= REDIREC_IN && token->type <= HEREDOC)
			if (!check_redirec_word(&token))
				return (manage_syntax_error(REDIREC_IN));
		if (token && token->type == PIPE)
			if (!check_pipe(token))
				return (manage_syntax_error(PIPE));
		token = token->next;
	}
	if (!join_heredoc_delimiter(tok) || !join_quotes(tok, env)
		|| !change_dollars(tok, env))
		return (malloc_error());
	// read_token(*tok);
	return (1);
}
//all done and tested
