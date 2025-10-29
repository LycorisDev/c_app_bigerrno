#include "libft.h"

void	list_iter(t_list *list, void (*f)(void *))
{
	if (!f)
		return ;
	while (list)
	{
		f(list->data);
		list = list->next;
	}
	return ;
}
