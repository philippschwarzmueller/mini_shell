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
	state.redir_in = false;
	state.redir_out = false;
	state.append = false;
	state.last = false;
	state.here_doc = false;
	state.in_set = false;
	state.out_set = false;
	return (state);
}

void	free_cmd(void *pointer)
{
	t_command	*command;

	command = (t_command *)pointer;
	free(command->command);
	ft_free_stra(command->options);
	if (command->in > 2)
		close(command->in);
	if (command->out > 2)
		close(command->out);
	free(command);
}

int	ft_here_doc(char *delimiter)
{
	char	*str;
	char	*delimit_signal;
	int		src[2];

	if (pipe(src))
		ft_printf("here doc failed, errorcodes not yet existent\n");
	str = get_next_line(0);
	delimit_signal = ft_strjoin(delimiter, "\n");
	while (str && ft_strncmp(delimit_signal, str, ft_strlen(str) - 1))
	{
		ft_putstr_fd(str, src[1]);
		free(str);
		str = get_next_line(0);
	}
	free(delimit_signal);
	if (str != NULL)
		free(str);
	close(src[1]);
	return (src[0]);
}
