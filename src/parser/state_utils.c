#include "shell.h"

struct s_state	init_state(char **env)
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
	state.env = env;
	return (state);
}

void	update_in_out_state(struct s_state *state, t_type type)
{
	if (type == here_doc)
	{
		state->here_doc = false;
		state->in_set = true;
	}
	else if (type == infile)
	{
		state->redir_in = false;
		state->in_set = true;
	}
	else if (type == outfile)
	{
		state->redir_out = false;
		state->out_set = true;
	}
	else if (type == append)
	{
		state->append = false;
		state->out_set = true;
	}
}

void	update_state(t_token *token, struct s_state *state, char *cmd)
{
	if (token->type == word)
	{
		if (!state->redir_out && !state->redir_in && !state->append
			&& !state->here_doc)
		{
			if (cmd != NULL)
				state->option = true;
			else
				state->command = true;
		}
	}
	else if (token->type != syntax)
	{
		if (token->type == piping)
			state->pipe = true;
		else if (token->type == here_doc)
			state->here_doc = true;
		else if (token->type == infile)
			state->redir_in = true;
		else if (token->type == outfile)
			state->redir_out = true;
		else if (token->type == append)
			state->append = true;
		state->command = false;
	}
}

void	print_parsed_lst(t_list *command_table)
{
	t_command	*temp;
	int			i;

	i = 0;
	while (command_table != NULL)
	{
		temp = (t_command *)command_table->content;
		ft_printf("------------------\n");
		if (!temp->command)
			return ;
		ft_printf("Command: %s\n", temp->command);
		ft_printf("Options: ");
		while (temp && temp->options != NULL && temp->options[i] != NULL)
		{
			ft_printf("%d: ", i);
			ft_printf("%s ", temp->options[i]);
			i++;
		}
		ft_printf("\n");
		ft_printf("In: %d\n", temp->in);
		ft_printf("Out: %d\n", temp->out);
		ft_printf("------------------\n");
		command_table = command_table->next;
		i = 0;
	}
}
