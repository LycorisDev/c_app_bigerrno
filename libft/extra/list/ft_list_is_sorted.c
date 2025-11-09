#include "libft.h"

int	ft_list_is_sorted(t_list *list, int (*f)(void *, void *))
{
	if (!list || !f)
		return (0);
	while (list->next)
	{
		if (f(list->data, list->next->data) > 0)
			return (0);
		list = list->next;
	}
	return (1);
}
