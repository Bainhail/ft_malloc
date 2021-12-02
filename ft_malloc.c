/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 03:49:15 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 16:59:43 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static size_t		select_category(size_t size)
{
	size = (size == 0) ? 1 : size;
	if (size >= 1 && size <= (TINY_BLOCK - sizeof(t_block)))
		return (CAT_TINY);
	else if (size > (TINY_BLOCK - sizeof(t_block))
			 && size <= (SMALL_BLOCK - sizeof(t_block)))
		return (CAT_SMALL);
	return (CAT_LARGE);
}

t_heap				*look_for_heap(size_t cat, size_t size)
{
	t_heap		*tmp;

	tmp = heap_ancor;
	if (cat == CAT_LARGE && size > (SMALL_BLOCK - sizeof(t_block)))
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->category == cat && tmp->size_free >= size)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void				*pMalloc(size_t size)
{
	void	*ptr;
	t_heap	*addr;
	size_t	cat;

	ptr = NULL;
	init_global();
	cat = select_category(size);
	if ((addr = look_for_heap(cat, size)) == NULL || cat == CAT_LARGE)
		addr = h_insert_node(h_new_node(cat, &size));
	if (addr != NULL)
	{
		ft_putstr("CALL INSERT BLOCK --> ");
		ft_putnbr(cat);
		ft_putchar('\n');
		ptr = insert_block(addr, size);
		ptr = ptr + sizeof(t_block);
	}
	return (ptr);
}

DYLD_INTERPOSE(pMalloc, malloc);
