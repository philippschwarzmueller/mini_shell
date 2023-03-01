#include "shell.h"

struct s_state	init_state(void);
void			parse_token(t_token *token, struct s_state *state,
					t_list *command_table);
t_command		*create_cmd(char *command, char **options, int in, int out);

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
		parse_token((t_token *)lexed_arg->content, &state, command_table);
		lexed_arg = lexed_arg->next;
	}
	del = command_table;
	command_table = command_table->next;
	ft_lstdelone(del, free);
	return (command_table);
}

void	update_state(t_token *token, struct s_state *state)
{
	if (token->type == piping)
		state->pipe = true;
	else if (token->type == infile)
	{
		state->redirect_in = true;
		state->option = false;
	}
	else if (token->type == outfile)
	{
		state->redirect_out = true;
		state->option = false;
	}
	else if (token->type == here_doc)
		ft_printf("heredoc found\n");
	else if (token->type == append)
		ft_printf("heredoc found\n");
	if (state->command == true)
		state->option = true;
	else
		state->command = true;
}

char	**append_options(char **options, char *str)
{
	int		old_len;
	int		i;
	char	**old_options;
	char	**new_options;

	old_len = 0;
	i = 0;
	old_options = options;
	while (old_options && old_options[old_len] != NULL)
		old_len++;
	new_options = malloc(sizeof(char *) * (old_len + 2));
	if (!new_options)
		return (NULL);
	if (old_options != NULL && old_options[0])
	{
		while (i < old_len)
		{
			new_options[i] = ft_strdup(old_options[i]);
			free(old_options[i]);
			i++;
		}
	}
	new_options[i] = ft_strdup(str);
	new_options[++i] = NULL;
	return (free(old_options), new_options);
}

void	update_in_out(int *in, int *out, struct s_state *state, char *path)
{
	int	fd;

	if (state->redirect_in == true)
	{
		fd = open(path, O_RDONLY);
		*in = fd;
	}
	else if (state->redirect_out == true)
	{
		fd = open(path, O_RDWR);
		*out = fd;
	}
	else
	{
		*out = STDOUT_FILENO;
		*in = STDIN_FILENO;
	}
}

void	parse_token(t_token *token, struct s_state *state,
				t_list *command_table)
{
	static char	*command;
	static char	***options;
	static int	in;
	static int	out;

	update_state(token, state);
	if (state->command == true && state->pipe == false
		&& state->option == false && !state->pipe)
		command = ft_strdup(token->token);
	else if (state->option == true && !state->redirect_in
		&& !state->redirect_out && !state->pipe)
		*options = append_options(*options, token->token);
	if (options == NULL)
		options = malloc(sizeof(char *));
	update_in_out(&in, &out, state, token->token);
	if (state->pipe == true || state->last == true)
	{
		ft_lstadd_back(&command_table,
			ft_lstnew(create_cmd(command, *options, in, out)));
		reset_cmd(&command, options, &in, &out);
		options = NULL;
		*state = init_state();
	}
}
