/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:35:09 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/17 22:35:24 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection(t_token **search)
{
	bool	is_redirect;

	is_redirect = true;
	while (*search && (*search)->type == SPACE)
		*search = (*search)->next;
	if ((*search && ((*search)->type > HEREDOC
				|| (*search)->type < REDIREC_IN)) || !(*search))
		return (false);
	else
		*search = (*search)->next;
	while (*search && (*search)->type == SPACE)
		*search = (*search)->next;
	if ((*search && (*search)->type != WORD) || !(*search))
		return (false);
	*search = (*search)->next;
	return (is_redirect);
}

t_ioredirect	*creat_redirection(t_token *token)
{
	t_ioredirect	*new_redirect;

	new_redirect = (t_ioredirect *)malloc(sizeof(t_ioredirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->next = NULL;
	while (token->type == SPACE)
		token = token->next;
	new_redirect->type = token->type;
	token = token->next;
	while (token->type == SPACE)
		token = token->next;
	new_redirect->file_name = ft_strdup(token->data);
	if (!new_redirect->file_name)
		return (NULL);
	return (new_redirect);
}

t_ioredirect	*last_redirection(t_ioredirect *redirect)
{
	t_ioredirect	*last;

	last = redirect;
	if (!redirect)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	get_redirection(t_token *token, t_ioredirect **cmd_pref)
{
	t_ioredirect	*new;
	t_ioredirect	*last_re;

	new = creat_redirection(token);
	if (!new)
		return (0);
	if (!(*cmd_pref))
		*cmd_pref = new;
	else
	{
		last_re = last_redirection(*cmd_pref);
		last_re->next = new;
	}
	return (1);
}
