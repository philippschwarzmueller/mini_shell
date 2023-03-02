#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int exit_code, t_list *commands);
char	**join_cmd(char *command, char **cmd);
size_t	ft_arr_len(char **arr);
void	dup_back(int orig_in, int orig_out);

#endif
