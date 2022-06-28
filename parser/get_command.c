/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:27:56 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 03:11:38 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_pref(t_token **token, t_ioredirect **cmd_pref)
{
	t_token			*search;
	t_token			*temp;
	bool			is_redirect;

	is_redirect = true;
	search = *token;
	while (*token && is_redirect)
	{
		is_redirect = is_redirection(&search);
		if (is_redirect)
		{
			if (!get_redirection(*token, cmd_pref))
				return (0);
			temp = *token;
			*token = search;
			if (search)
				search->prev->next = NULL;
			free_tokens(&temp);
		}
	}
	return (1);
}

int	creat_cmd_suff(t_token **token, t_cmd_suffix **cmd_suff)
{
	t_cmd_suffix	*new;

	new = (t_cmd_suffix *)malloc(sizeof(t_cmd_suffix));
	if (!new)
		return (0);
	new->args = NULL;
	new->redirection = NULL;
	*cmd_suff = new;
	if (!get_cmd_suff(token, cmd_suff))
		return (0);
	return (1);
}

int	get_cmd_name(t_token **token, char **cmd_name)
{
	char	*str;
	t_token	*tem;
	t_token	*search;

	tem = *token;
	search = *token;
	while (search && search->type == SPACE)
		search = search->next;
	if (!search)
		return (1);
	str = ft_strdup(search->data);
	if (!str)
		return (0);
	*cmd_name = str;
	*token = search->next;
	search->next = NULL;
	free_tokens(&tem);
	return (1);
}

int	get_command(t_token **token, t_command **cmd)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (0);
	new_cmd->cmd_pref = NULL;
	new_cmd->cmd = NULL;
	new_cmd->cmd_suff = NULL;
	if (!get_cmd_pref(token, &new_cmd->cmd_pref))
		return (0);
	if (!get_cmd_name(token, &new_cmd->cmd))
		return (0);
	if (!creat_cmd_suff(token, &new_cmd->cmd_suff))
		return (0);
	*cmd = new_cmd;
	return (1);
}
