/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:47:34 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 04:08:01 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_token(t_token *token)
{
	t_token	*read;

	read = token;
	while (read)
	{
		printf("|%s|---> type = |%d|\n", read->data, read->type);
		read = read->next;
	}
}

t_token	*last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	 free_tokens(t_token **token)
{
	t_token	*tempo;

	while (*token)
	{
		tempo = *token;
		*token = (*token)->next;
		free(tempo->data);
		free(tempo);
	}
}

char	*get_env_value(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*join_quotes_data(char *s1, char *s2)
{
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2)+ 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, ft_strlen(s1));
	ft_memcpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free (s1);
	return (ret);
}
