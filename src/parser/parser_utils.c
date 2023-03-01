#include "shell.h"

void	reset_cmd(char **command, char ***options, int *in, int *out)
{
	command[0] = NULL;
	if (options != NULL)
		options = NULL;
	*in = 0;
	*out = 0;
}

t_command	*create_cmd(char *command, char **options, int in, int out)
{
	t_command	*cmd;

	ft_printf("creating cmd\n");
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->command = command;
	cmd->options = options;
	cmd->path = NULL;
	cmd->in = in;
	cmd->out = out;
	ft_printf("created cmd\n");
	return (cmd);
}

struct s_state	init_state(void)
{
	struct s_state	state;

	state.pipe = false;
	state.option = false;
	state.command = false;
	state.redirect_in = false;
	state.redirect_out = false;
	state.last = false;
	return (state);
}

void	ft_freestra(char **str_arr)
{
	int	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_cmd(void *pointer)
{
	t_command	*command;

	command = (t_command *)pointer;
	free(command->command);
	ft_freestra(command->options);
	free(command);
}
