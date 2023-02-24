#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	word,
	operation,
}	t_type;

typedef struct s_state
{
	int	is_word;
	int	is_squoted;
	int	is_dquoted;
	int	is_escaped;
	int	is_operator;
}		t_state;

typedef struct s_token
{
	char	*token;
	t_type	type;
}			t_token;

#endif
