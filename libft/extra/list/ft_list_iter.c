#include "libft.h"

void	ft_list_iter(t_list *list, void (*f)(void *))
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
