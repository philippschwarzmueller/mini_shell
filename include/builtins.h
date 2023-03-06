#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_echo(char **stra);
int	ft_cd(char **options);
int	ft_pwd(char **options, char **env);
int	ft_env(char **env);
int	ft_unset(char ***env, char **options);

#endif
