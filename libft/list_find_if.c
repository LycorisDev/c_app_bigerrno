#include "libft.h"

t_list	*list_find_if(t_list *list, int (*f)(void *))
{
	if (!f)
		return (0);
	while (list)
	{
		if (f(list->data))
			return (list);
		list = list->next;
	}
	return (0);
}
