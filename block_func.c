/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:16:26 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/03 16:01:13 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static void			new_block(t_heap **addr, t_block **insert, t_block **block, size_t size)
{
	if (block != NULL && *block != NULL)
	{
		if (insert != NULL && *insert == NULL && block != NULL
			&& addr != NULL && *addr != NULL)
			(*addr)->block_first = *block;
		else
		{
			if (*block < *insert)
				(*block)->next = *insert;
			else
			{
				(*block)->next = (*insert)->next;
				(*insert)->next = *block;
			}
		}
		(*block)->size = size;
		(*block)->heap_start = *addr;
		(*addr)->nb_block += 1;
		(*addr)->size_free -= (size + sizeof(t_block));
	}
}

/*
** insertion de block et creation de heap si necessaire
*/
t_block				*insert_block(t_heap *node, size_t size)
{
	t_block		*tmp;
	t_block		*insert;

	tmp = NULL;
	insert = NULL;
	size = (size == 0) ? 1 : size;
	if (node != NULL)
	{
		if ((tmp = check_for_spot(&node, size, &insert)) == NULL)
		{
			insert = NULL;
			node = h_insert_node(h_new_node(CAT_TINY, &size));
			tmp = check_for_spot(&node, size, &insert);
		}
		new_block(&node, &insert, &tmp, size);
	}
	return (tmp);
}

/*
** Retire les liens des block desallouer
** si la heap est vide a la desallocation
** elle est egalement supprimer
*/
void				remove_block(t_heap *node, t_block *to_erase)
{
	t_block		*tmp;

	if (node != NULL && to_erase != NULL)
	{
		tmp = node->block_first;
		node->nb_block -= 1;
		node->size_free += (to_erase->size + sizeof(t_block));
		if (tmp == to_erase)
			node->block_first = tmp->next;
		else
		{
			while (tmp->next != NULL && tmp->next != to_erase)
				tmp = tmp->next;
			if (tmp->next == to_erase)
				tmp->next = to_erase->next;
		}
		if (node->nb_block == 0)
			h_remove_node(node);
	}
}
