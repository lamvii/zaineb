/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_suff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:31:19 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/17 22:31:42 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arg_in_token(t_token **token)
{
	t_token	*tem;

	tem = *token;
	while (*token && (*token)->type == SPACE)
		*token = (*token)->next;
	if (*token)
	{
		*token = (*token)->next;
		if (*token)
			(*token)->prev->next = NULL;
	}
	free_tokens(&tem);
}

int	tab_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i + 1);
}

// or use memcpy
int	add_new_arg(char ***arg, char **str)
{
	int		i;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (tab_size(*arg) + 1));
	if (!tab)
		return (0);
	i = 0;
	while ((*arg)[i])
	{
		tab[i] = (*arg)[i];
		i++;
	}
	tab[i] = *str;
	tab[i + 1] = NULL;
	free(*arg);
	*arg = tab;
	return (1);
}

int	get_argument(t_token *token, char ***arg)
{
	char	*str;

	if (!token)
		return (1);
	str = ft_strdup(token->data);
	if (!str)
		return (0);
	if (!(*arg))
	{
		*arg = (char **)malloc(sizeof(char *) * 1);
		if (!(*arg))
			return (0);
		(*arg)[0] = NULL;
	}
	if (!add_new_arg(arg, &str))
		return (0);
	return (1);
}

int	get_cmd_suff(t_token **token, t_cmd_suffix **cmd_suff)
{
	t_token	*read;
	t_token	*tem;

	while (*token)
	{
		read = *token;
		if (is_redirection(&read))
		{
			if (!get_redirection(*token, &((*cmd_suff)->redirection)))
				return (0);
			tem = *token;
			*token = read;
			if (read)
				read->prev->next = NULL;
			free_tokens(&tem);
		}
		else
		{
			if (!get_argument(read, &((*cmd_suff)->args)))
				return (0);
			if (*token)
				free_arg_in_token(token);
		}
	}
	return (1);
}
