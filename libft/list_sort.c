#include "libft.h"

void	list_sort(t_list *list, int (*f)(void *, void *))
{
	int		swap_performed;
	t_list	*head;

	if (!f)
		return ;
	swap_performed = 0;
	head = list;
	while (list)
	{
		if (list->next && f(list->data, list->next->data) > 0)
		{
			list_swap_data(list, list->next);
			swap_performed = 1;
		}
		list = list->next;
		if (!list && swap_performed)
		{
			list = head;
			swap_performed = 0;
		}
	}
	return ;
}
