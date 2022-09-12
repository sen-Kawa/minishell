#include "minishell.h"

char *command;

void	handler_quit(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\b\b\n", 1);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	struct	sigaction sa;
	pid_t	pid;
	t_ms_list	*tokens;
	t_lex_struct	lex;
	// char	*cmd_path;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
	tokens = (t_ms_list *)malloc(sizeof(t_ms_list));
		if (!tokens)
			exit(EXIT_FAILURE);
	tokens->next = NULL;
	tokens->token = "something";
	while (1)
	{
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		command = readline("cli prompt >> ");
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			add_history(command);
			lex = tokenice(command, tokens);

		}
		(void)envp;
		
		// cmd_path = get_cmd_path(command, envp);
	}

	if (lex.error == 1)
		freeing_tokens(tokens);
	else
		printing_tokens(tokens);
	
	return 0;
}
