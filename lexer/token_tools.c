/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:54:22 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/27 23:49:51 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	what_token(char *line, int i)
{
	if (line[i] == ' ')
		return (SPACE);
	if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	if (line[i] == '>' && line[i + 1] == '>')
		return (APPEND);
	if (line[i] == '\'')
		return (S_QUOTE);
	if (line[i] == '"')
		return (D_QUOTE);
	if (line[i] == '|')
		return (PIPE);
	if (line[i] == '<')
		return (REDIREC_IN);
	if (line[i] == '>')
		return (REDIREC_OUT);
	if (line[i] == '$')
		return (DOLLAR);
	else
		return (WORD);
}

char	*add_size2_token(char *line, int *i)
{
	int	j;

	j = *i;
	*i += 2;
	return (ft_substr(line, j, 2));
}

char	*add_word(char *line, int *i)
{
	int		start;
	int		end;
	int		token_type;

	start = *i;
	end = *i;
	token_type = what_token(line, *i);
	while (token_type == what_token(line, *i) && line[end] != '\0')
	{
		end++;
		(*i)++;
	}
	return (ft_substr(line, start, end - start));
}

char	*dollar_v(char *str, t_env *env)
{
	char	*value;
	char	*num;
	char	*tmp;

	if (!ft_strncmp(str, "?", 1))
	{
		num = ft_itoa(g_global.errno);
		tmp = (ft_strjoin(num, str + 1));
		free(num);
		return (tmp);
	}
	value = get_env_value(str, env);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

void	delete_empty_quotes(t_token **head, t_token **run)
{
	t_token	*tem;

	//check if $"" elemine $
	if ((*run)->prev && (*run)->prev->type == DOLLAR)
		tem = (*run)->prev;
	else
		tem = (*run);
	*run = (*run)->next->next;
	if (*run)
		(*run)->prev->next = NULL;
	if (tem->prev)
		tem->prev->next = (*run);
	else
		(*head) = (*run);
	if (*run)
		(*run)->prev = tem->prev;
	free (tem);
}
