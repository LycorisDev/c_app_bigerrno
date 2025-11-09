#include "libft.h"

int	ft_list_any(t_list *list, int (*f)(void *))
{
	if (!f)
		return (0);
	while (list)
	{
		if (f(list->data))
			return (1);
		list = list->next;
	}
	return (0);
}
