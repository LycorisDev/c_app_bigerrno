#include "libft.h"

t_list	*ft_list_last(t_list *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}
