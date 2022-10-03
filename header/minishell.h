/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/10/03 09:17:20 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"

# ifdef __APPLE__ // should work in linux and mac headers
#  include </Users/ksura/goinfre/.brew/opt/readline/include/readline/readline.h>
#  include </Users/ksura/goinfre/.brew/opt/readline/include/readline/history.h>

# else
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

# include <unistd.h>



typedef struct s_lex
{
	int			start;
	int			i;
	int			length;
	int			error;
}	t_lex;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	t_env		*env_list;
	int			env_lst_size;
	t_lex		*lex;
	t_ms_list	*tokenlist;
}	t_ms;

char			*get_cmd_path(char *cmd, char **envp);
char			**ft_split_ssp(char const *s, char c);
t_lex			*tokenice(char *command, t_ms *ms, char **envp);
t_lex			*afterquotes(char *command, t_lex *lex, t_ms_list *tokens);
t_lex			*beforequotes(char *command, t_lex *lex,
					t_ms_list *tokens);
int				pipe_check(char *command, t_lex *lex, t_ms_list *tokens);
void			printing_tokens(t_ms_list *tokens);
void			freeing_tokens(t_ms *ms);
void			freeing_all(t_ms *ms);
void			redirecting(t_ms_list *tokens);
void			dollarizing(t_ms_list *tokens);
void			dollar_double(t_ms_list *tokens, char **envp);
char	*replacing_vars(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*replacing_vars_middle_dollar(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*all_dollar_splitting(int a, char **envp \
, char **dollar_split, char *new_dollar);
char	*dollar_core(char **envp, char **space_split, int i);
void	b_exit(char *command);
int		b_env(char *token, t_ms *ms);

void	make_array(t_ms *ms, int nlines);
void	bubblesorting(int nlines, char *env_array[]);
void	creating_env_list(char **envp, t_ms *ms);

// void	initms(t_ms *ms);

//buildins
void	execute(t_ms *ms);
void	print_env(t_ms	*ms);
void	b_export(t_ms	*ms);
void	b_unset(t_ms	*ms);
int		b_pwd(t_ms	*ms);
void	b_echo(t_ms	*ms);
void	b_cd(t_ms	*ms);

//llist stuff
t_env   *ft_envvnew(char *content);
t_env   *ft_envvlast(t_env *envv);
void    ft_envvadd_back(t_env **env, t_env *new);

//tokenising
void	sections(t_ms	*ms);
#endif