#include "bigerrno.h"

void	lst_clear(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*lst = 0;
	return ;
}
