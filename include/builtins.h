#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_echo(char **stra);
int		ft_cd(char **options, char **env);
int		ft_pwd(char **options);
int		ft_env(char **env);
int		ft_unset(char ***env, char **options);
int		ft_export(char ***env, char **options);
char	**add_to_environment(char **env, char *varname, char *value);
int		update_env(char ***env, char *varname, char *value);
int		ft_exit(t_command *command, t_list *commands, char ***env);


#endif
