#include "includes/minishell.h"

t_envp	*find_by_key(t_envp **v, char *key)
{

}

t_envp	*find_prev_by_key(t_envp **v, char *key)
{

}

void	put_var_in_envp_list(t_envp **v, t_envp *new_var)
{
	t_envp	*temp;

	temp = find_prev_by_key(v, new_var->key);
	if (temp->next)
	{
		temp->next->prev = new_var;
		new_var->next = temp->next;
	}
	temp->next = new_var;
	new_var->prev = temp;
}

void	replace_var_in_envp_list(t_envp *temp, t_envp *new_var)
{
	new_var->next = temp->next;
	new_var->prev = temp->prev;
	temp->prev->next = new_var;
	temp->next->prev = new_var;
	free(temp);
}

void	add_to_envp_list(t_envp **v, const char *key_value)
{
	t_envp	*new_var;
	t_envp	*temp;

	if (!*key_value)
		return ;
	new_var = malloc(sizeof(t_envp));
	if (new_var == NULL)
		return(p_error(ALLOC_FAILURE, NULL));
	new_var->key_value = key_value;
	new_var->key = get_key();
	new_var->value = get_value();
	new_var->next = NULL;
	new_var->prev = NULL;
	if (*v == NULL)
	{
		*v = new_var;
		return ;
	}
	temp = find_by_key(v, new_var->key);
	if (temp != NULL)
		replace_var_in_envp_list(temp, new_var);
	else
		put_var_in_envp_list(v, new_var);
}

int	init_envp(t_shell *m, char **envp)
{
	t_envp	*v;
	int		cnt_el;
	int		i;

	v = NULL;
	m->envp = v;
	while(envp[++cnt_el] != NULL)
		add_to_envp_list(&v, envp[cnt_el]);

}