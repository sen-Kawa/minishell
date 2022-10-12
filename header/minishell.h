/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/10/12 14:10:25 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

# ifdef __APPLE__ // should work in linux and mac headers
#  include </Users/ksura/goinfre/.brew/opt/readline/include/readline/readline.h>
#  include </Users/ksura/goinfre/.brew/opt/readline/include/readline/history.h>

# else
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

# include <unistd.h>

typedef struct s_pipes
{
	int		fd_file[4];
	int		pipe_ends[2];
	int		pipe2_ends[2];
	int		child_pid[2];
}	t_pipes;

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
	int			env_lst_size;
	int			sections;
	int			current_section;
	int			exit_status;
	t_env		*env_list;
	t_lex		*lex;
	t_pipes		*pipes_struct;
	t_ms_list	*tokenlist;
}	t_ms;

//cmd_paths.c
char	*get_cmd_path(char *cmd, char **envp);

//directing_vars.c
char	*replacing_vars(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*replacing_vars_middle_dollar(char **envp, int ds \
, char **dollar_split, char *new_dollar);
void	redirecting(t_ms *ms);

//dollars.c
void	dollarizing(t_ms *ms);
void	dollar_double(t_ms_list *tokens, t_ms	*ms);
char	*all_dollar_splitting(int a, char **envp \
, char **dollar_split, char *new_dollar);
char	*dollar_core(char **space_split, int i, t_ms	*ms);

//execution.c
int		builtins(t_ms *ms);
void	heredoc(t_ms *ms, char	*delim);

//quote_handling.c
t_lex	*double_quotes(char *command, t_ms *ms);
t_lex	*single_quotes(char *command, t_ms *ms);
t_lex	*beforequotes(char *command, t_lex *lex, t_ms_list *tokens);
t_lex	*afterquotes(char *command, t_lex *lex, t_ms_list *tokens);

//splitter2.c
char	**ft_split_ssp(char const *s, char c);

//tokeniser.c
void	freeing_tokens(t_ms *ms);
void	freeing_all(t_ms *ms);
int		pipe_check(char *command, t_lex *lex, t_ms_list *tokens);
t_lex	*tokenice(char *command, t_ms *ms, char **envp);

//main.c
void	creating_env_list(char **envp, t_ms *ms);

//printing.c
void	printing_tokens(t_ms_list *tokens);
void	print_to_out(t_ms *ms, char *to_print);

//sorting_env.c
void	bubblesorting(int nlines, char *env_array[]);
void	make_array(t_ms *ms, int nlines);
char	**make_array_env(t_ms *ms);
char	**make_array_token(t_ms *ms);

//buildins
int		b_exit(t_ms	*ms);
int		b_env(char *token, t_ms *ms);
int		b_export(t_ms	*ms);
int		b_unset(t_ms	*ms);
int		b_echo(t_ms	*ms);

//buildins2.c
int		b_pwd(t_ms	*ms);
int		b_cd(t_ms	*ms);

//llist_env.c
t_env	*ft_envvnew(char *content);
t_env	*ft_envvlast(t_env *envv);
void	ft_envvadd_back(t_env **env, t_env *new);
void	print_env(t_ms	*ms);

//sections.c
void	sections(t_ms	*ms);

//execution
int		execution(t_ms	*ms);

#endif
