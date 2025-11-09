#include "libft.h"

t_list	*ft_list_map(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_head;
	t_list	*map;

	if (!list || !f)
		return (0);
	map_head = ft_list_new(f(list->data));
	if (!map_head)
		return (0);
	map = map_head;
	list = list->next;
	while (list)
	{
		map->next = ft_list_new(f(list->data));
		map->next->prev = map;
		map = map->next;
		if (!map)
		{
			ft_list_clear(map_head, del);
			return (0);
		}
		list = list->next;
	}
	return (map_head);
}
