#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int exit_code, t_list *commands);
char	**join_cmd(char *command, char **cmd);
void	dup_back(int orig_in, int orig_out);
void	exit_buildin(t_list *commands);

#endif