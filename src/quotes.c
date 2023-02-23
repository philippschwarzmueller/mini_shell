#include "shell.h"

static int	is_unquoted(char *str, size_t i, char token);

int	quote_count(char *str)
{
	size_t	i;
	size_t	quote_cnt;
	size_t	dquote_cnt;

	i = 0;
	quote_cnt = 0;
	dquote_cnt = 0;
	while (str[i])
		if (is_unquoted(str, i++, '\"'))
			dquote_cnt++;
	i = 0;
	while (str[i])
		if (is_unquoted(str, i++, '\''))
			quote_cnt++;
	return ((quote_cnt % 2 == 1) || (dquote_cnt % 2 == 1));
}

static int	is_unquoted(char *str, size_t i, char token)
{
	char	cmp;
	size_t	j;
	int		sv;

	j = i;
	sv = 0;
	if (token == '\"')
		cmp = '\'';
	else
		cmp = '\"';
	if (str[i] != '\'' && str[i] != '\"')
		return (0);
	while (str[j] && str[j] != cmp)
		if (str[++j] == token)
			sv = 1;
	j = i;
	while (j && str[j] != cmp)
		if (str[--j] == token && sv)
			return (1);
	return (0);
}
