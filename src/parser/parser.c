#include "shell.h"

struct s_state	init_state(void);
void			parse_token(char *str, struct s_state *state,
					t_list *command_table);
t_command		*create_cmd(char *command, char *options, int in, int out);

struct s_state
{
	t_bool	pipe;
	t_bool	option;
	t_bool	command;
	t_bool	redirect;
	t_bool	last;
};

t_list	*parse(t_list *lexed_arg)
{
	t_list			*command_table;
	t_list			*del;
	struct s_state	state;

	state = init_state();
	command_table = ft_lstnew(NULL);
	while (lexed_arg != NULL)
	{
		if (lexed_arg->next == NULL)
			state.last = true;
		parse_token((char *)lexed_arg->content, &state, command_table);
		lexed_arg = lexed_arg->next;
	}
	del = command_table;
	command_table = command_table->next;
	ft_lstdelone(del, free);
	return (command_table);
}

void	update_state(char *str, struct s_state *state)
{
	if (ft_strncmp(str, "|", 1) == 0)
		state->pipe = true;
	else if (str[0] == '-' || state->command == true)
		state->option = true;
	else
		state->command = true;
}

void	parse_token(char *str, struct s_state *state,
				t_list *command_table)
{
	static char	*command;
	static char	*options;
	static int	in;
	static int	out;

	update_state(str, state);
	if (state->option == true && state->pipe == false)
	{
		if (options == NULL)
			options = ft_strdup(str);
		else
		{
			options = ft_strjoin(options, " ");
			options = ft_strjoin(options, str);
		}
	}
	if (state->command == true && state->option == false
		&& state->pipe == false)
		command = ft_strdup(str);
	if (state->pipe == true || state->last == true)
	{
		if (state->pipe == true)
			out = -2;
		else
			out = STDOUT_FILENO;
		if (state->redirect == true)
			in = -2;
		ft_lstadd_back(&command_table,
			ft_lstnew(create_cmd(command, options, in, out)));
		command = NULL;
		options = NULL;
		in = 0;
		out = 0;
		*state = init_state();
		state->redirect = true;
	}
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
	state.redirect = false;
	state.last = false;
	return (state);
}
