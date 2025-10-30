#include "bigerrno.h"

t_env	*add_node(t_env **lst, char *key, char *value)
{
	t_env	*new;

	new = lst_new(key, value);
	if (!new || !new->key)
	{
		free(new);
		lst_clear(lst);
		return (0);
	}
	lstadd_back(lst, new);
	return (new);
}
