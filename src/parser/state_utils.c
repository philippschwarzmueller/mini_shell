#include "shell.h"

t_state_parse	init_state(char **env)
{
	t_state_parse	state;

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

void	update_in_out_state(t_state_parse *state, t_type type)
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

void	update_state(t_token *token, t_state_parse *state, char *cmd)
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

int	check_parsed_syntax(t_list *command_table)
{
	t_command	*temp_c;

	while (command_table != NULL)
	{
		temp_c = (t_command *) command_table->content;
		if (!temp_c)
		{
			ft_putstr_fd("Syntax error, missing a command\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		command_table = command_table->next;
	}
	return (EXIT_SUCCESS);
}
