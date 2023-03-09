#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int e_code, t_list *commands);
char	**join_cmd(char *command, char **cmd);
void	exit_builtin(t_list *commands);
void	dup_back(int orig_in, int orig_out, int *pip);

#endif
