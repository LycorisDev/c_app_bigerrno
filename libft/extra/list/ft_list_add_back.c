#include "libft.h"

void	ft_list_add_back(t_list *list, t_list *new)
{
	if (!list || !new)
		return ;
	list = ft_list_last(list);
	list->next = new;
	new->prev = list;
	return ;
}
