#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	word,
	specifier,
	operation
}	t_type;

typedef struct s_state
{
	int	is_word;
	int	is_quoted;
	int	is_operator;
	int	is_specifier;
}		t_state;

typedef struct s_token
{
	char	*token;
	t_type	type;
}			t_token;

#endif
