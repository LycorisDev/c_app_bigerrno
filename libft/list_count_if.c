#include "libft.h"

size_t	list_count_if(t_list *list, int (*f)(void *))
{
	size_t	count;

	count = 0;
	if (!f)
		return (count);
	while (list)
	{
		if (f(list->data))
			++count;
		list = list->next;
	}
	return (count);
}
