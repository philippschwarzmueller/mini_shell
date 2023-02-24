#include "shell.h"

struct s_state	init_state(void);
t_command		*parse_token(char *str, struct s_state *state);

struct s_state
{
	int	pipe;
	int	option;
};

t_list	*parse(t_list *lexed_arg)
{
	t_list			*command_table;
	t_list			*del;
	struct s_state	state;
	char			*temp_str;

	state = init_state();
	command_table = ft_lstnew(NULL);
	while (lexed_arg != NULL)
	{
		temp_str = lexed_arg->content;
		if (temp_str[0] == '-')
			state.option = 1;
		if (ft_strncmp(temp_str, "|", 1) == 0)
			state.pipe = 1;
		else
			ft_lstadd_back(&command_table, ft_lstnew(parse_token(lexed_arg->content, &state)));
		lexed_arg = lexed_arg->next;
	}
	del = command_table;
	command_table = command_table->next;
	ft_lstdelone(del, free);
	return (command_table);
}

t_command	*parse_token(char *str, struct s_state *state)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->command = str;
	cmd->path = str;
	cmd->out = str;
	if (state->pipe == 1)
	{
		cmd->in = "pipe";
		state->pipe = 0;
	}
	else
		cmd->in = str;
	return (cmd);
}

struct s_state	init_state(void)
{
	struct s_state	state;

	state.pipe = 0;
	state.option = 0;
	return (state);
}
