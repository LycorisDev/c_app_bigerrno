#include "bigerrno.h"

int	lst_size(t_env **lst)
{
	int		size;
	t_env	*loc;

	size = 0;
	loc = *lst;
	while (loc)
	{
		++size;
		loc = loc->next;
	}
	return (size);
}
