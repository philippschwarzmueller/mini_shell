#include "shell.h"

static int	is_quoted(char *str, size_t i, char c);
static int	count_quotes(char *str, size_t i, char c);

char	*ft_decrustify_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	while (str[j])
	{
		if (str[j] != '\"' && str[j] != '\'' && str[j] != '\\')
			tmp[i++] = str[j++];
		else if (j > 0 && (str[j - 1] == '\\' || is_quoted(str, j, str[j])))
			tmp[i++] = str[j++];
		else
			j++;
	}
	res = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(res, tmp, i + 1);
	return (free(str), free(tmp), res);
}

static int	is_quoted(char *str, size_t i, char c)
{
	char	cmp;
	size_t	j;
	int		sv;

	j = i;
	sv = 0;
	cmp = '\'';
	if (c == '\\')
		return (0);
	if (c == '\'')
		cmp = '\"';
	while (str[j] && str[j] != cmp)
		if (str[++j] == cmp)
			sv = 1;
	j = i;
	while (j && str[j] != cmp)
		if (str[--j] == cmp && sv && count_quotes(str, i, cmp))
			return (1);
	return (0);
}

static int	count_quotes(char *str, size_t i, char c)
{
	size_t	j;
	int		sv_left;
	int		sv_right;

	j = i;
	sv_left = 0;
	sv_right = 0;
	while(str[j])
	{
		if (str[j] == c && str[j - 1] != '\\')
			sv_right++;
		j++;
	}
	j = i;
	while(j)
	{
		if (str[j] == c && j > 0 && str[j - 1] != '\\')
			sv_left++;
		j--;
	}
	return (sv_left % 2 == 0 && sv_right % 2 == 0);
}
