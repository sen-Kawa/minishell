#include "minishell.h"

char *command;

void	handler(int num)
{
	(void)num;
	write(0, "\n", 1);
	ft_putstr_fd("\b\b\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	struct	sigaction	sa;
	pid_t	pid;

	pid = getpid();
	ft_printf("pid is %d\n", pid);
	while (1)
	{
		sa.sa_handler = &handler;
		sigaction(SIGINT, &sa, NULL);
		write(1, "1", 1);
		command = readline("cli prompt >> ");
		if (ft_strlen(command) > 0)
			add_history(command);
	}
	return 0;
}
