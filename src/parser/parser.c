#include "shell.h"

struct s_state	init_state(void);
t_command		*parse_token(char *str, struct s_state *state);

struct s_state
{
	int	pipe;
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
		if (ft_strncmp(temp_str, "|", 1) == 0)
		{
			state.pipe = 1;
			ft_printf("found pipe\n");
		}
		else
		{
			ft_lstadd_back(&command_table, ft_lstnew(parse_token(lexed_arg->content, &state)));
			ft_printf("added one\n");
		}
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

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		return (NULL);
	cmd->command = str;
	cmd->path = str;
	if (state->pipe == 1)
	{
		ft_printf("setting in to pipe\n");
		cmd->in = "pipe";
		state->pipe = 0;
	}
	else
		cmd->in = str;
	cmd->out = str;
	return (cmd);
}

struct s_state	init_state(void)
{
	struct s_state	state;

	state.pipe = 0;
	return (state);
}
