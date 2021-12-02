/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 04:07:47 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 17:44:38 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

void		pFree(void *ptr)
{
	t_heap	*tmp;
	t_block	*test;

	tmp = heap_ancor;
	if (ptr != NULL && tmp != NULL)
	{
		while (tmp != NULL && (void*)tmp < (void*)ptr && ptr > ((tmp->block_start + tmp->size_max)))
			tmp = tmp->next;
		if (tmp != NULL)
		{
			test = tmp->block_first;
			while (test != NULL && (void*)test != (ptr - sizeof(t_block)))
				test = test->next;
			if ((void*)test == (ptr - sizeof(t_block)))
				remove_block(tmp, (ptr - sizeof(t_block)));
		}
	}
}

DYLD_INTERPOSE(pFree, free);
