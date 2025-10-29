#include "libft.h"

t_list	*list_find_at(t_list *list, size_t index)
{
	size_t	i;

	i = 0;
	while (list && i < index)
	{
		++i;
		list = list->next;
	}
	return (list);
}
