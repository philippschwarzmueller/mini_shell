#include "shell.h"

void	reset_cmd(char **command, char **options, int *in, int *out)
{
	command[0] = NULL;
	options[0] = NULL;
	*in = 0;
	*out = 0;
}

t_command	*create_cmd(char *command, char *options, int in, int out)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->command = command;
	cmd->options = options;
	cmd->path = NULL;
	cmd->in = in;
	cmd->out = out;
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

void	free_cmd(void *pointer)
{
	t_command	*command;

	command = (t_command *)pointer;
	free(command->command);
	free(command->options);
	free(command);
}
