/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 11:32:54 by ksura            ###   ########.fr       */
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

char	*get_cmd_path(char *cmd, char **envp);
void	tokenice(char *command, t_ms_list *tokens);


void	printing_list_a(t_ms_list *tokens);
#endif
