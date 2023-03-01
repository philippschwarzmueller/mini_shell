#ifndef EXECUTOR_H
# define EXECUTOR_H

void	err(char *mess, int exit_code, char **cmd);
char	*format_cmd(char *cmd);
char	**join_cmd(char **str);

#endif
