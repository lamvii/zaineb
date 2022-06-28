/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:16:07 by ael-idri          #+#    #+#             */
/*   Updated: 2022/06/28 03:43:58 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define WORD 0
# define SPACE 1
# define D_QUOTE 2
# define S_QUOTE 3
# define PIPE 4
# define DOLLAR 5
# define REDIREC_IN 6
# define REDIREC_OUT 7
# define APPEND 8
# define HEREDOC 9
# define EOL 10

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "builtin/env.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_global
{
	int	errno;
}				t_global;

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_ioredirect
{
	int					type;
	int					fd;
	char				*file_name;
	struct s_ioredirect	*next;
}						t_ioredirect;

typedef struct s_cmd_suffix
{
	char			**args;
	t_ioredirect	*redirection;
}				t_cmd_suffix;

typedef struct s_command
{
	t_ioredirect	*cmd_pref;
	t_cmd_suffix	*cmd_suff;
	char			*cmd;
}						t_command;

typedef struct s_pipe_seq
{
	t_command			*cmd;
	struct s_pipe_seq	*next;
}						t_pipe_seq;

//		global
t_global	g_global;

//		./lexer/token.c
int		tokenizer(char *line, t_token **token);

//		./lexer/syntax_error.c
int		syntax_error(t_token **token, t_env *env);

//		./lexer/change_dollars.c
int		change_dollars(t_token **token, t_env *env);

//		./lexer/join_quote.c
int		join_quotes(t_token **token, t_env *env);

//		./lexer/heredoc_delimiter.c
int		prev_is_hdoc(t_token *token);
int		join_heredoc_delimiter(t_token **token);

//		./lexer/tokens_utils.c
void	read_token(t_token *token);
t_token	*last_token(t_token *token);
void	free_tokens(t_token **token);
char	*get_env_value(char *str, t_env *env);
char	*join_quotes_data(char *s1, char *s2);

// 		./lexer/token_tools.c
char	*add_word(char *line, int *i);
char	*add_size2_token(char *line, int *i);
int		what_token(char *line, int i);
char	*dollar_v(char *str, t_env *env);
void	delete_empty_quotes(t_token **head, t_token **run);

//		./lexer/manage_error.c
int		manage_syntax_error(int type);
int		malloc_error(void);

//		./parser/parser.c
int		parser(t_token **token, t_pipe_seq **pipe_seq);

//		./parser/free_pipe_seq.c
void	free_pipe_seq(t_pipe_seq **pipe_seq);

//		./parse/get_pipe_seq.c
int		get_pipe_seq(t_pipe_seq **pipe_seq, t_token **token);

//		./parser/get_command.c
int		get_command(t_token **token, t_command **cmd);

//		./parser/get_cmd_suff.c
int		get_cmd_suff(t_token **token, t_cmd_suffix **cmd_suff);

//		./parser/get_redirection.c
bool	is_redirection(t_token **search);
int		get_redirection(t_token *token, t_ioredirect **cmd_pref);

//		./parser/read_pipe_seq.c
void	read_pipe_seq(t_pipe_seq *pipe_seq);

//		./execution/utils.c
char	**creat_tab(char *cmd, char **args);
int		two_d_lenth(char **str);
int		str_ichr(char *str, char c);
char	*str_ndup(char *str, unsigned int n);
void	error(void);

//		./execution/exec_cmd.c
void	exec(t_command *cmd_line, t_env **env);
int		is_builtin(t_command *seq, t_env **str);
void	free_tab(char **tab);

//		./execution/pipe_exec.c
pid_t	execute_pipe(t_pipe_seq *seq, t_env **env, int infile, int outfile);
int		size_seq(t_pipe_seq *seq);
int		multiple_pipe(t_pipe_seq *seq, t_env **env);

//		./execution/redirection
int		open_infile(t_ioredirect *dir);
int		open_outfile(t_ioredirect *dir);
void	safe_close(int fd);
void	replace_fd(int *fd, int *new);
void	close_all(t_ioredirect	*red, int fd1, int fd2);

//		./execution/heredoc.c
int		creat_heredoc(char *delemeter);

//		main.c
void	print_tab(char **env);
char	**lst_to_env(t_env	*env);

#endif
