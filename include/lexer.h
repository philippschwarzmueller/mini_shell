#ifndef LEXER_H
# define LEXER_H

typedef enum s_bool
{
	false,
	true,
}	t_bool;

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
	t_bool	is_word;
	t_bool	is_squoted;
	t_bool	is_dquoted;
	t_bool	is_escaped;
	t_bool	is_operator;
}		t_state_lex;

typedef struct s_token
{
	char	*token;
	t_type	type;
}			t_token;

void	del_token(void *content);
//void	remove_val(t_list **lst, void *content);
void	set_type(t_token *new);
void	del_first(t_list **lst);

#endif
