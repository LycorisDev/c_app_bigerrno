#include "libft.h"

int	ft_list_add_sorted(t_list *list, t_list *new, int (*f)(void *, void *))
{
	if (!list || !new || !f)
		return (0);
	while (list)
	{
		if (f(list->data, new->data) > 0)
		{
			new->next = list;
			new->prev = list->prev;
			list->prev = new;
			return (1);
		}
		else if (!list->next)
			break ;
		list = list->next;
	}
	list->next = new;
	new->prev = list;
	return (1);
}
