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
	char	*cmd_path;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
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
			add_history(command);
		cmd_path = get_cmd_path(command, envp);
	}
	return 0;
}
