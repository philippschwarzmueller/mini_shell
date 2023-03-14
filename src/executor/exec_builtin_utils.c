#include "shell.h"

t_bool	runs_in_parent(t_command *command)
{
	char	*str;

	str = command->command;
	if (str == NULL)
		return (0);
	if (!ft_strncmp(str, "cd", 3))
		return (true);
	if (!ft_strncmp(str, "export", 7))
		return (true);
	if (!ft_strncmp(str, "unset", 6))
		return (true);
	if (!ft_strncmp(str, "exit", 5))
		return (true);
	return (false);
}
