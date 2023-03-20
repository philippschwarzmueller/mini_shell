#ifndef PARSER_H
# define PARSER_H

typedef struct s_state_parse
{
	t_bool	pipe;
	t_bool	option;
	t_bool	command;
	t_bool	redir_out;
	t_bool	redir_in;
	t_bool	append;
	t_bool	last;
	t_bool	here_doc;
	t_bool	in_set;
	t_bool	out_set;
	char	**env;
}	t_state_parse;

typedef struct s_command
{
	char	*command;
	char	**options;
	int		in;
	int		out;
}	t_command;

void			free_cmd(void *pointer);
t_command		*create_cmd(char *command, char **options, int in, int out);
void			reset_cmd(char **command, char ***options, int *in, int *out);
t_state_parse	init_state(char **env);
int				ft_here_doc(char *delimiter, char **env);
void			default_in_out(int *in, int *out, t_state_parse *state);
void			update_state(t_token *token, t_state_parse *state, char *cmd);
void			update_in_out_state(t_state_parse *state, t_type type);
int				open_files(char *path, int flag);
int				check_parsed_syntax(t_list *command_table);

#endif
