#include "libft.h"

void	ft_list_del_one(t_list *node, void (*del)(void *))
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (del)
		del(node->data);
	free(node);
	return ;
}
