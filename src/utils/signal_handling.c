#include "shell.h"

static void	handle_sigint(int sig);
static void	disable_echo(void);

void	init_signalhandlers(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
	disable_echo();
}

static void	disable_echo(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	init_child_sig_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	control_exit(size_t prompt_size, char **env)
{
	char	*offset;
	char	*exit_line;

	clear_history();
	ft_free_stra(env);
	if (!isatty(STDIN_FILENO))
		exit(g_exit_code);
	offset = ft_strjoin_f(ft_itoa(prompt_size), "C");
	exit_line = ft_strjoin("\033[", offset);
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd(exit_line, STDOUT_FILENO);
	ft_putendl_fd("exit", STDOUT_FILENO);
	free(offset);
	free(exit_line);
	exit(g_exit_code);
}
