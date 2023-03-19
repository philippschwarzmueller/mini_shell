#include "shell.h"

static t_bool	is_num(char *s);
static long		set_e_code(t_command *cmd);
static int		checkoffset(const char *str);

int	ft_exit(t_command *cmd, t_list *cmds, char ***env)
{
	long	e_code;

	if (ft_lstsize(cmds) > 1)
		return (EXIT_SUCCESS);
	if (cmd->options)
		e_code = set_e_code(cmd);
	else if (ft_stra_len(cmd->options) == 0)
		e_code = 0;
	else
		e_code = 1;
	ft_lstclear(&cmds, free_cmd);
	ft_free_stra(*env);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	exit(e_code);
	return (0);
}

static long	set_e_code(t_command *cmd)
{
	if ((cmd->options[0] && !is_num(cmd->options[0]))
		|| !ft_strlen(cmd->options[0]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		return (255);
	}
	else if (ft_stra_len(cmd->options) > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (ft_strtol(cmd->options[0]));
}

static t_bool	is_num(char *s)
{
	int	res;
	int	i;

	res = true;
	i = checkoffset(s);
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			res = false;
		i++;
	}
	return (res);
}

static int	checkoffset(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}
