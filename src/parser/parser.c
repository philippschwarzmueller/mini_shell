#include "shell.h"

static void		parse_token(t_token *token, struct s_state *s,
					t_list *cmd_table);
static char		**append_options(char **options, char *str);
static void		update_in_out(int *in, int *out, struct s_state *state,
					char *path);

t_list	*parse(t_list *lexed_arg, char **env)
{
	t_list			*command_table;
	t_list			*del;
	struct s_state	state;

	state = init_state(env);
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

void	init_empty_opts(char ****opts)
{
	char	***helper;

	helper = malloc(sizeof(char ***));
	*helper = NULL;
	*opts = helper;
}

static void	parse_token(t_token *token, struct s_state *s, t_list *cmd_table)
{
	static char	*cmd;
	static char	***opt = NULL;
	static int	in;
	static int	out;

	update_state(token, s, cmd);
	if (s->pipe || s->redir_in || s->redir_out || s->append || s->here_doc)
		update_in_out(&in, &out, s, token->token);
	else if (s->command && !s->pipe && !s->option)
		cmd = ft_strdup(token->token);
	else if (s->option && !s->pipe)
		*opt = append_options(*opt, token->token);
	if (!opt)
		init_empty_opts(&opt);
	if (s->pipe == true || s->last == true)
	{
		default_in_out(&in, &out, s);
		ft_lstadd_back(&cmd_table, ft_lstnew(create_cmd(cmd, *opt, in, out)));
		reset_cmd(&cmd, opt, &in, &out);
		opt = NULL;
		*s = init_state(s->env);
	}
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
	while (old_options && old_options[old_len])
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
	if (ft_strncmp(path, "<<", 2) == 0 || ft_strncmp(path, ">>", 2) == 0
		|| ft_strncmp(path, "<", 1) == 0 || ft_strncmp(path, ">", 1) == 0)
		return ;
	if (state->here_doc)
	{
		*in = ft_here_doc(path, state->env);
		update_in_out_state(state, here_doc);
	}
	else if (state->redir_in == true)
	{
		*in = open_files(path, 0);
		update_in_out_state(state, infile);
	}
	else if (state->redir_out == true)
	{
		*out = open_files(path, O_TRUNC);
		update_in_out_state(state, outfile);
	}
	else if (state->append == true)
	{
		*out = open_files(path, O_APPEND);
		update_in_out_state(state, append);
	}
}
