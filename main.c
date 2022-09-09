#include "minishell.h"

char *command;

int	main(void)
{
	while (1)
	{
		command = readline("cli prompt >> ");
		if (ft_strlen(command) > 0)
			add_history(command);
	}
	//	write(1, "1", 1);
	return 0;
}
