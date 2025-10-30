#include "bigerrno.h"

void	clear_node(t_env *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
	return ;
}
