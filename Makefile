# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 17:33:28 by ael-idri          #+#    #+#              #
#    Updated: 2022/06/28 01:45:24 by ael-idri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra
RM			=	rm -rf
SRCS	 	=	./lexer/token.c ./lexer/token_tools.c ./lexer/syntax_error.c \
				./lexer/tokens_utils.c ./lexer/join_quote.c					 \
				./lexer/change_dollars.c ./lexer/manage_error.c				 \
				./lexer/heredoc_delimiter.c									 \
				./parser/free_pipe_seq.c   ./parser/get_cmd_suff.c    		 \
				./parser/get_command.c     ./parser/get_pipe_seq.c   		 \
				./parser/get_redirection.c ./parser/parser.c				 \
				./parser/read_pipe_seq.c									 \
				./execution/utils.c ./execution/cmd_exec.c					 \
				./builtin/cd.c ./builtin/environement.c ./builtin/exit.c 	 \
				./builtin/pwd.c ./builtin/unset.c ./builtin/utils.c 		 \
				./builtin/export.c ./builtin/echo.c 						 \
				./execution/pipe_exec.c ./execution/redirection.c    		 \
				./execution/heredoc.c    									 \
				main.c 													 
OBJS		=	$(SRCS:.c=.o)
LIBFT		=	./libft/libft.a
PATH_LIBFT	=	./libft/
HEADER		=	minishell.h

all			:	$(NAME)

${LIBFT}	:
				@make -C ${PATH_LIBFT}

$(NAME)		:	$(OBJS) ${LIBFT}
				${CC} ${FLAGS} -lreadline -L /Users/${USER}/.brew/opt/readline/lib \
				 ${OBJS} -o $(NAME) $(LIBFT)

%.o			:	%.c $(HEADER)
				$(CC) ${FLAGS} -c -I /Users/${USER}/.brew/opt/readline/include $< -o $@
    
clean		:
				$(RM) $(OBJS)
				make clean -C ${PATH_LIBFT}

fclean		:	clean
				$(RM) $(NAME)
				make fclean -C ${PATH_LIBFT}

re			:	fclean all

.PHONY		:	all clean fclean re