/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:40:55 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 03:25:15 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*creat_token(char *line, int *i)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = what_token(line, *i);
	if (token->type <= REDIREC_OUT && token->type >= D_QUOTE)
	{
		token->data = ft_substr(line, *i, 1);
		(*i)++;
	}
	else if (token->type == APPEND || token->type == HEREDOC)
		token->data = add_size2_token(line, i);
	else
		token->data = add_word(line, i);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int	tokenizer(char *line, t_token **token)
{
	t_token	*last;
	t_token	*new;
	int		i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!(*token))
			*token = creat_token(line, &i);
		else
		{
			new = creat_token(line, &i);
			last = last_token(*token);
			last->next = new;
			if (new)
				new->prev = last;
		}
	}
	return (1);
}
