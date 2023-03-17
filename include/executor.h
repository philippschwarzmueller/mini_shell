#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int e_code, t_list *commands);
char	**join_cmd(char *command, char **cmd);
void	dup_back(int orig_in, int orig_out, int *pip, int size);
void	wait_for_processes(pid_t last_pid, t_list *commands);
t_bool	runs_in_parent(t_command *command);

#endif
