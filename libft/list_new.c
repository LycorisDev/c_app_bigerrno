#include "libft.h"

t_list	*list_new(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->data = data;
	new->prev = 0;
	new->next = 0;
	return (new);
}
