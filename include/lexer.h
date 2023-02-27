#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	word,
	piping,
	redirect,
	syntax
}	t_type;

typedef struct s_state_lex
{
	int	is_word;
	int	is_squoted;
	int	is_dquoted;
	int	is_escaped;
	int	is_operator;
}		t_state_lex;

typedef struct s_token
{
	char	*token;
	t_type	type;
}			t_token;

void	del_token(void *content);
void	remove_val(t_list **lst, void *content);
t_token	*tokenize(char *str, size_t i, size_t *len);
void	print_lexed_lst(t_list *lst);
void	syntax_error(t_list **lst);

#endif
