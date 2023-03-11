#ifndef EXPANDER_H
# define EXPANDER_H

char	*append_str(char *str, char *to_append, size_t i, size_t j);
char	*append_value(char *to_append, char *name, char **env);
char	*get_env_value(char *varname, char **env);
void	state_change(char c, t_state_lex *state);
char	*trim_front(char *s1, const char *set);
char	*trim_back(char *s1, const char *set);

#endif
