#include "libft.h"

void	list_del_if(t_list *list, int (*f)(void *), void (*del)(void *))
{
	t_list	*next;

	if (!f)
		return ;
	while (list)
	{
		next = list->next;
		if (f(list->data))
			list_del_one(list, del);
		list = next;
	}
	return ;
}
