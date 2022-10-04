/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/10/04 18:23:45 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	heredoc(t_ms *ms);

void	builtins(t_ms *ms)
{
	t_ms_list	*tmp;
	size_t	len;
	
	len = 0;
	tmp = ms->tokenlist;
	b_pwd(ms);
	b_export(ms);
	b_unset(ms);
	b_echo(ms);
	b_cd(ms);
	heredoc(ms);
	while(tmp)
	{
		len = ft_strlen(tmp->token);
		if (b_env(tmp->token, ms) && len < 3)
		{
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}
	return ;
}

void	heredoc(t_ms *ms)
{
	t_ms_list	*tmp;
	char		*delim;
	char		*hereline;
	char		*herecom;
	//char		*tmp_here;

	tmp = ms->tokenlist;
	if(!ft_strncmp(tmp->token, "<<\0", 3))
	{
		if(tmp->next)
			delim = tmp->next->token;
		else
		{
			ft_printf("cli: syntax error near unexpected token `newline'");
			ms->lex->error = 4;
			return ;
		}
		hereline = "";
		herecom = NULL;
		while (ft_strncmp(hereline, delim, sizeof(delim)))
		{
			hereline = readline("> ");
			if (hereline == NULL)
			{
				ft_printf("bash: warning: here-document at line 10 delimited by end-of-file (wanted `%s')\n", delim);
				break ;
			}
			if (!ft_strncmp(hereline, delim, sizeof(delim)))
			{
				free (hereline);
				break;
			}
			if (herecom)
			{
				// tmp_here = herecom;
				herecom = ft_strjoin(herecom, hereline);
				herecom = ft_strjoin(herecom, "\n");
			}
			else
				herecom = ft_strjoin(hereline, "\n");
			
			// free (hereline);
		}
		if (herecom)
			{
				ft_printf("%s", herecom);
				//free (tmp_here);
			}
	}
}


int	execution(t_ms	*ms)
{
	char	*cmd_path;
	char	**env_arr;
	pid_t	pid;
	
	if (ms->sections == 0)
	{
		builtins(ms);
		env_arr = make_array_env(ms);
		cmd_path = get_cmd_path(ms->tokenlist->token, env_arr);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			ft_printf("%i", execve(cmd_path, make_array_token(ms), env_arr));
		//	ft_printf("%s", cmd_path);
			exit (0);
		}
	waitpid(pid, NULL, WUNTRACED);
	}
	return (0);
}