#include "bigerrno.h"

t_env	*find_key(t_env **lst, char *key)
{
	t_env	*tmp;

	if (!key || !lst || !*lst)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
