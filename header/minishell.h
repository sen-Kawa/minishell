/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/10/07 14:03:16 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <sys/wait.h>
// # include <sys/stat.h>
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
	t_env		*env_list;
	int			env_lst_size;
	int			sections;
	t_lex		*lex;
	t_ms_list	*tokenlist;
	int			exit_status;
	t_pipes		*pipes_struct;
}	t_ms;


char			*get_cmd_path(char *cmd, char **envp);
char			**ft_split_ssp(char const *s, char c);
t_lex			*tokenice(char *command, t_ms *ms, char **envp);
t_lex			*afterquotes(char *command, t_lex *lex, t_ms_list *tokens);
t_lex			*beforequotes(char *command, t_lex *lex,
					t_ms_list *tokens);
t_lex			*double_quotes(char *command, t_ms *ms);
t_lex			*single_quotes(char *command, t_ms *ms);
int				pipe_check(char *command, t_lex *lex, t_ms_list *tokens);
void			printing_tokens(t_ms_list *tokens);
void			freeing_tokens(t_ms *ms);
void			freeing_all(t_ms *ms);
void			redirecting(t_ms *ms);
void			dollarizing(t_ms *ms);
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
int	builtins(t_ms *ms);
void	print_env(t_ms	*ms);
int	b_export(t_ms	*ms);
int	b_unset(t_ms	*ms);
int		b_pwd(t_ms	*ms);
int	b_echo(t_ms	*ms);
int	b_cd(t_ms	*ms);
int	exit_status(t_ms	*ms);

//llist stuff
t_env   *ft_envvnew(char *content);
t_env   *ft_envvlast(t_env *envv);
void    ft_envvadd_back(t_env **env, t_env *new);

//tokenising
void	sections(t_ms	*ms);

//execution
int		execution(t_ms	*ms);
char	**make_array_env(t_ms *ms);
char	**make_array_token(t_ms *ms);

//redirections
/**
*@brief opens/creates given files, checks for access rights
*
*@param *filename: char pointer to the file to open/create
*@param rw: int to declare if its input file (rw = 0) or 
*output file (rw = 1)
*@param **envp; environmentpointer of the mainfct for 
*execution of "touch" and "chmod"
*@return filedescritor fd of the opened file
*/
int	open_file(char *filename, int rw, char **envp);

#endif
