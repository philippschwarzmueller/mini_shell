#ifndef PARSER_H
# define PARSER_H

typedef enum s_bool
{
	false,
	true,
}	t_bool;

struct s_state
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
};

typedef struct s_command
{
	char	*command;
	char	**options;
	int		in;
	int		out;
}	t_command;

void			free_cmd(void *pointer);
void			ft_freestra(char **str_arr);
t_command		*create_cmd(char *command, char **options, int in, int out);
void			reset_cmd(char **command, char ***options, int *in, int *out);
struct s_state	init_state(void);
int				ft_here_doc(char *delimiter);
void			default_in_out(int *in, int *out, struct s_state *state);
void			update_state(t_token *token, struct s_state *state, char *cmd);
void			update_in_out_state(struct s_state *state, t_type type);

#endif
