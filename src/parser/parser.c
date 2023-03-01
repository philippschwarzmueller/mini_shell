#include "shell.h"

static void		parse_token(t_token *token, struct s_state *state,
					t_list *command_table);
static void		update_state(t_token *token, struct s_state *state);
static char		**append_options(char **options, char *str);
static void		update_in_out(int *in, int *out, struct s_state *state,
					char *path);

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

static void	parse_token(t_token *token, struct s_state *state,
		t_list *command_table)
{
	static char	*command;
	static char	***options;
	static int	in;
	static int	out;

	update_state(token, state);
	if (state->command && !state->pipe && !state->option && !state->pipe)
		command = ft_strdup(token->token);
	else if (state->option && !state->redirect_in && !state->redirect_out
		&& !state->pipe && !state->append)
		*options = append_options(*options, token->token);
	if (options == NULL)
		options = malloc(sizeof(char *));
	// somehow creates file even for > or >>
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

static void	update_state(t_token *token, struct s_state *state)
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
	{
		state->append = true;
		state->option = false;
	}
	if (state->command == true)
		state->option = true;
	else
		state->command = true;
}

static char	**append_options(char **options, char *str)
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

static void	update_in_out(int *in, int *out, struct s_state *state, char *path)
{
	int	fd;

	if (ft_strncmp(path, "<<", 2) == 0 || ft_strncmp(path, ">>", 2) == 0
		|| ft_strncmp(path, "<", 1) == 0 || ft_strncmp(path, ">", 1) == 0)
		return ;
	if (state->redirect_in == true)
	{
		fd = open(path, O_RDONLY);
		*in = fd;
	}
	else if (state->redirect_out == true)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*out = fd;
	}
	else if (state->append == true)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		*out = fd;
	}
	else
	{
		*out = STDOUT_FILENO;
		*in = STDIN_FILENO;
	}
}
