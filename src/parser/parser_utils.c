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

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->command = command;
	cmd->options = options;
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
	state.append = false;
	state.last = false;
	return (state);
}

void	free_cmd(void *pointer)
{
	t_command	*command;

	command = (t_command *)pointer;
	free(command->command);
	ft_free_stra(command->options);
	free(command);
}

void	ft_here_doc(char *delimiter)
{
	char	*str;
	int		src[2];

	if (pipe(src))
		ft_printf("here doc failed, errorcodes not yet existent\n");
	str = get_next_line(0);
	while (str && ft_strncmp(delimiter, str, ft_strlen(str) - 1))
	{
		ft_putstr_fd(str, 1);
		free(str);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
	dup2(src[0], 0);
	close(src[0]);
	close(src[1]);
}
