#include "shell.h"

void	default_in_out(int *in, int *out, struct s_state *state)
{
	if (!state->in_set)
		*in = 0;
	if (!state->out_set)
		*out = 1;
}

void	reset_cmd(char **command, char ***options, int *in, int *out)
{
	command[0] = NULL;
	if (options != NULL)
		free(options);
	*in = 0;
	*out = 0;
}

t_command	*create_cmd(char *command, char **options, int in, int out)
{
	t_command	*cmd;

	if (!command)
		return (NULL);
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->command = command;
	cmd->options = options;
	cmd->in = in;
	cmd->out = out;
	return (cmd);
}

void	free_cmd(void *pointer)
{
	t_command	*command;

	command = (t_command *)pointer;
	if (!command)
		return ;
	if (command->command)
		free(command->command);
	if (command->options)
		ft_free_stra(command->options);
	if (command->in > 2)
		close(command->in);
	if (command->out > 2)
		close(command->out);
	free(command);
}

int	ft_here_doc(char *delim, char **env)
{
	char	*str;
	char	*delimiter;
	int		src[2];

	if (pipe(src))
		ft_printf("here doc failed, errorcodes not yet existent\n");
	str = read_input(STDIN_FILENO);
	delimiter = ft_decrustify_str(ft_strdup(delim));
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter) + 1))
	{
		if (ft_strchr(delim, 39) == NULL && ft_strchr(delim, 34) == NULL)
			str = expand_string(str, env);
		ft_putstr_fd(str, src[1]);
		ft_putstr_fd("\n", src[1]);
		free(str);
		str = read_input(STDIN_FILENO);
	}
	free(delimiter);
	free(str);
	close(src[1]);
	return (src[0]);
}
