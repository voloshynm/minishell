#ifndef PARSER_H
# define PARSER_H

typedef struct s_tree_node
{
	char			*str;
	t_token		token;
	int				i;
	struct s_tree_node	*next;
	struct s_tree_node	*prev;
}					t_lexer;

t_lexer		*init_lexer(char *input);

#endif