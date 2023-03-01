#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int exit_code, char **cmd);
char	*format_cmd(char *cmd);
char	**join_cmd(char *command, char **cmd);
size_t	ft_arr_len(char **arr);
void	ft_free_arr(char **ptr);
char	*ft_strjoin_alt(char *s1, char *s2);

#endif
