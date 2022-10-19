/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/10/19 12:27:17 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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

//delete_section.c
void	delete_section(t_ms *ms);

//cmd_paths.c
char	*get_cmd_path(char *cmd, char **envp);

//redirecting_vars.c
char	*replacing_vars(char **envp, int ds \
, char **dollar_split, char *new_dollar);
char	*replacing_vars_middle_dollar(char **envp, int ds \
, char **dollar_split, char *new_dollar);
void	delete_token(t_ms *ms);

//redirecting.c
void	redirecting(t_ms *ms);
void	redir2(t_ms_list *tmp, t_ms	*ms, int outfd);
void	redir2_1(t_ms_list *tmp, t_ms *ms, int outfd);
int		redir2_1_1(t_ms_list *tmp, t_ms *ms, int outfd);

//redirecting2.c
int		redir1_0(t_ms_list *tmp, t_ms *ms, int infd, int outfd);
int		redir1_1(t_ms_list *tmp, t_ms *ms, int infd);
int		redir1_2(t_ms_list *tmp, t_ms *ms, int infd);
int		redir1_3(t_ms_list *tmp, t_ms *ms, int outfd);
int		redir1_4(t_ms_list *tmp, t_ms *ms, int outfd);

//dollars.c
void	dollarizing(t_ms *ms);
void	dollar_double(t_ms_list *tokens, t_ms	*ms);
char	*all_dollar_splitting(int a, char **envp \
, char **dollar_split, char *new_dollar);
char	*dollar_core(char **space_split, int i, t_ms	*ms);

//execution.c
int		builtins(t_ms *ms);

//heredoc.c
void	tmp_heredoc(t_ms *ms, char *herecom);
void	here_command(char *hereline, char **herecom);
void	heredoc(t_ms *ms, char	*delim);

//quote_handling.c
t_lex	*double_quotes(char *command, t_ms *ms);
t_lex	*single_quotes(char *command, t_ms *ms);
t_lex	*beforequotes(char *command, t_lex *lex, t_ms_list *tokens);
t_lex	*afterquotes(char *command, t_lex *lex, t_ms_list *tokens);

//splitter2.c
char	**ft_split_ssp(char const *s, char c);

//free.c
void	freeing_tokens(t_ms *ms);
void	freeing_all(t_ms *ms, char *command);

//tokeniser.c
int		pipe_check(char *command, t_lex *lex, t_ms_list *tokens);
void	tokenice(char *command, t_ms *ms);

//main.c

//printing.c
void	printing_tokens(t_ms_list *tokens);
void	print_to_out(t_ms *ms, char *to_print);

//sorting_env.c
void	bubblesorting(int nlines, char *env_array[]);
void	make_array(t_ms *ms, int nlines);
char	**make_array_env(t_ms *ms);
char	**make_array_token(t_ms *ms);

//builtins
int		b_exit(t_ms	*ms);
void	b_exit_arg(char *token);
int		b_env(t_ms *ms);
int		b_unset(t_ms	*ms);
void	modify_env_list(t_env *prev_envlst, t_env *envlst, t_ms *ms);

//echo.c
int		b_echo(t_ms	*ms);
void	b_echo_print(t_ms_list *tmp, t_ms *ms, int flag);

//export.c
int		b_export(t_ms	*ms);
void	b_export_var(char *token, t_ms *ms);

//buildins2.c
int		b_pwd(t_ms	*ms);
int		b_cd(t_ms	*ms);
void	b_cd_tilde(char **token);
void	unsuccess_chdir(t_ms *ms);
void	update_pwd(t_ms *ms);

//llist_env.c
t_env	*ft_envvnew(char *content);
t_env	*ft_envvlast(t_env *envv);
void	ft_envvadd_back(t_env **env, t_env *new);
void	print_env(t_ms	*ms);
void	creating_env_list(char **envp, t_ms *ms);

//sections.c
void	sections(t_ms	*ms);

//execution
int		execution(t_ms	*ms);

//execution2
int		builtins(t_ms *ms);
void	child_signal(int sig);
void	child_infilefd(t_ms *ms, int in_pipe_fd);
void	child_outfilefd(t_ms *ms, int out_pipe_fd);

//init.c
void	init(t_ms *ms, char *command);

//parent_signals.c
void	handler_quit(int sig);
void	parent_signals(void);

#endif
