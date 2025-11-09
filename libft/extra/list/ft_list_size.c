#include "libft.h"

size_t	ft_list_size(t_list *list)
{
	size_t	size;

	size = 0;
	while (list)
	{
		++size;
		list = list->next;
	}
	return (size);
}
