#ifndef EXPANDER_H
# define EXPANDER_H

char	*append_str(char *str, char *to_append, size_t i, size_t j);
char	*append_value(char *to_append, char *name, char **env);
char	*get_env_value(char *varname, char **env);
void	state_change(char c, t_state_lex *state);
int		find_var_end(char c);

#endif
