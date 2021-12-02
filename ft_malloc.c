/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 03:49:15 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 02:35:48 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#define DYLD_INTERPOSE_MAL(_replacment,_replacee) \
__attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };

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
	cat = select_category(size);
	if (heap_ancor == NULL)
	{
		addr = h_insert_node(h_new_node(cat, size));
		ptr = insert_block(addr, size);
		ptr = ptr + sizeof(t_block);
	}
	else
	{
		if ((addr = look_for_heap(cat, size)) == NULL)
			addr = h_insert_node(h_new_node(cat, size));
		ptr = insert_block(addr, size);
		ptr = ptr + sizeof(t_block);
	}
	return (ptr);
}

DYLD_INTERPOSE_MAL(pMalloc, malloc);
