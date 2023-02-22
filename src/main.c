#include "shell.h"

static void	signalhandler(int sig);
static void	print_lst(t_list *lst);
static void	disable_echo(void);

int	main(void)
{
	char	*input;
	t_list	*lst;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signalhandler);
	lst = NULL;
	while (1)
	{
		disable_echo();
		input = readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
		if (input == NULL)
		{
			rl_replace_line("TEST", 0);
			rl_redisplay();
			exit(EXIT_SUCCESS);
		}
		lst = lexing(input);
		print_lst(lst);
		ft_lstclear(&lst, free);
	}
	return (EXIT_SUCCESS);
}

static void	disable_echo(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
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

static void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", (char *)(lst->content));
		lst = lst->next;
	}
}
