#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "../lib/libft/libft.h"

static void	signalhandler(int sig);

int	main(void)
{
	char				*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signalhandler);
	while (1)
	{
		input = readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
		if (input == NULL)
		{
			rl_replace_line("TEST", 0);
			rl_redisplay();
			exit(EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

static void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
