#include "libft.h"

void	ft_list_clear(t_list *list, void (*del)(void *))
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		if (del)
			del(list->data);
		free(list);
		list = next;
	}
	return ;
}
