#include "bigerrno.h"

t_env	*lst_new(const char *key, const char *value)
{
	t_env	*node;

	if (!key)
		return (0);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = 0;
	node->withvalue = value != 0;
	node->next = 0;
	node->prev = 0;
	return (node);
}
