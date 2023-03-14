#ifndef EXPANDER_H
# define EXPANDER_H

char	*get_env_value(char *varname, char **env);
char	*trim_front(char *s1, const char *set);
char	*trim_back(char *s1, const char *set);
char	*remove_whitespaces(char *str);
void	state_change(char c, t_state_lex *state);
char	*ft_decrustify_str(char *str);

#endif
