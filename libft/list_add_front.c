#include "libft.h"

void	list_add_front(t_list *list, t_list *new)
{
	if (!list || !new)
		return ;
	new->next = list;
	list->prev = new;
	return ;
}
