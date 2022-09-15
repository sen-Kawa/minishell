/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/09/15 16:25:21 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include "libft/libft.h"
# ifdef __APPLE__ // should work in linux and mac headers
# include </Users/ksura/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/ksura/goinfre/.brew/opt/readline/include/readline/history.h>
# else
# include <readline/readline.h>
# include <readline/history.h>
# endif

# include <unistd.h>

typedef struct lex_struct
{
	int		start;
	int		i;
	int		length;
	int		error;
}	t_lex_struct;

char			*get_cmd_path(char *cmd, char **envp);
t_lex_struct	tokenice(char *command, t_ms_list *tokens, char **envp);
int				pipe_check(char *command, t_lex_struct lex, t_ms_list *tokens);
void			printing_tokens(t_ms_list *tokens);
void			freeing_tokens(t_ms_list	*tokens);
t_lex_struct	afterquotes(char *command, t_lex_struct lex, t_ms_list *tokens);
t_lex_struct	beforequotes(char *command, t_lex_struct lex, t_ms_list *tokens);
void			redirecting(t_ms_list *tokens);
void			dollarizing(t_ms_list *tokens);
void			dollar_double(t_ms_list *tokens, char **envp);
char	**ft_split_sp(char const *s, char c);

#endif
