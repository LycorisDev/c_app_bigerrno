#include "bigerrno.h"

static t_env	*lst_last(t_env *last);

t_env	*lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return (0);
	tmp = *lst;
	if (!*lst)
	{
		*lst = new;
		return (*lst);
	}
	tmp = lst_last(*lst);
	tmp->next = new;
	new->prev = tmp;
	return (*lst);
}

static t_env	*lst_last(t_env *last)
{
	if (!last)
		return (0);
	while (last->next)
		last = last->next;
	return (last);
}
