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
	t_bool	redirect_out;
	t_bool	redirect_in;
	t_bool	append;
	t_bool	last;
	t_bool	here_doc;
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
void			ft_here_doc(char *delimiter);

#endif
