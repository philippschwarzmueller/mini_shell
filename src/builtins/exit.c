#include "shell.h"

static t_bool	is_num(char *s);

int	ft_exit(t_command *cmd, t_list *commands, char ***env)
{
	long	exit_code;

	if (ft_lstsize(commands) > 1)
		return (EXIT_SUCCESS);
	if (cmd->options)
	{
		if ((cmd->options[0] && !is_num(cmd->options[0])) || !ft_strlen(cmd->options[0]))
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit_code = 255;
		}
		else if (ft_stra_len(cmd->options) > 1)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			exit_code = ft_strtol(cmd->options[0]);
		}
		else
			exit_code = ft_strtol(cmd->options[0]);
	}
	else if (ft_stra_len(cmd->options) == 0)
		exit_code = 0;
	else
		exit_code = 1;
	ft_lstclear(&commands, free_cmd);
	ft_free_stra(*env);
	exit(exit_code);
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
