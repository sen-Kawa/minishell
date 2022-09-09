/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 08:59:06 by ksura             #+#    #+#             */
/*   Updated: 2022/09/09 15:14:41 by ksura            ###   ########.fr       */
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

#endif
