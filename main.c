#include "minishell.h"

char *command;

// void	handler(int num)
// {
// 	(void)num;
// 	// write(0, "\n", 1);
// 	// ft_putstr_fd("\b\b\n", 1);
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// 	// rl_redisplay();
// 	// exit(1);
// }

void	handler_quit(int sig)
{
	// write(0, "\n", 1);
	if (sig ==  SIGINT)
	{
		// exit (1);
		ft_putstr_fd("\b\b\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig ==  SIGQUIT)
	{
		exit(1);
		write(1, "1", 1);
		// signal(SIGQUIT, SIG_DFL);
	}
	
	// exit(1);
}

int	main(void)
{
	struct	sigaction	sa;
	pid_t	pid;

	pid = getpid();
	ft_printf("pid is %d\n", pid);
	while (1)
	{
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		// write(1, "1", 1);
		command = readline("cli prompt >> ");
		if (command && *command)
			add_history(command);
	}
	return 0;
}
