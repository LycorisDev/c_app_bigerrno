#include "libft.h"

void	list_swap_data(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
	return ;
}
