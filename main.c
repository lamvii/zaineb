/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:45:52 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 04:23:15 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

char	**lst_to_env(t_env	*env)
{
	char	**str;
	int		i;
	int		size;

	i = 0;
	size = lst_size(env);
	str = (char **)malloc(sizeof(char *) * (lst_size(env) + 1));
	while (i < size && env->value)
	{
		str[i] = malloc(sizeof(char *)
				* (ft_strlen(env->key) + ft_strlen(env->value) + 2));
		ft_memset(str[i], 0, ft_strlen(env->key) + ft_strlen(env->value) + 2);
		ft_strlcpy(str[i], env->key, ft_strlen(env->key) + 1);
		ft_strlcat(str[i], "=", ft_strlen(env->key) + 2);
		ft_strlcat(str[i], env->value,
			ft_strlen(env->key) + 2 + ft_strlen(env->value));
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	minishell_loop(t_env *p)
{
	char		*line;
	t_token		*token;
	t_pipe_seq	*pipe_seq;

	token = NULL;
	pipe_seq = NULL;
	while (1)
	{
		free_pipe_seq(&pipe_seq);
		line = readline("<minishell$> ");
		add_history(line);
		if (!tokenizer(line, &token))
		{
			write(1, "\n", 1);
			continue ;
		}
		free(line);
		line = NULL;
		if (!syntax_error(&token, p) || !token || !parser(&token, &pipe_seq))
		{
			free_tokens(&token);
			g_global.errno = 1;
			continue ;
		}
		if (size_seq(pipe_seq) == 1
			&& pipe_seq->cmd->cmd_pref == NULL && is_builtin(pipe_seq->cmd, &p))
			continue ;
		g_global.errno = multiple_pipe(pipe_seq, &p);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*p;

	(void)ac;
	(void)av;
	g_global.errno = 0;
	p = parsing_env(env);
	signal(SIGINT, sig_handler);
	minishell_loop(p);
	freeing_env(p);
	return (g_global.errno);
}		
