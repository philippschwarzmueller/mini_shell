#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	word,
	piping,
	infile,
	outfile,
	here_doc,
	append,
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
//void	remove_val(t_list **lst, void *content);
char	*ft_decrustify_str(char *str);
void	set_type(t_token *new);
void	del_first(t_list **lst);

#endif
