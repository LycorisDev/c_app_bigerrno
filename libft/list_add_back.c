#include "libft.h"

void	list_add_back(t_list *list, t_list *new)
{
	if (!list || !new)
		return ;
	list = list_last(list);
	list->next = new;
	new->prev = list;
	return ;
}
