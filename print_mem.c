/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:07:50 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/04 20:40:34 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static void			print_block(t_block *block, size_t *nb)
{
	ft_putstr("0x");
	ft_putnbr_base((size_t)block, B16);
	ft_putstr(" - 0x");
	ft_putnbr_base((size_t)block + block->size + sizeof(t_block), B16);
	ft_putstr(": ");
	ft_putnbr_base(block->size, B10);
	ft_putstr(" octect(s)\n");
	*nb += block->size;
}

static void			print_node(t_heap *node, size_t *nb)
{
	t_block		*tmp;

	tmp = node->block_first;
	if (node->category == CAT_TINY)
		ft_putstr("TINY: ");
	else if (node->category == CAT_SMALL)
		ft_putstr("SMALL: ");
	else if (node->category == CAT_LARGE)
		ft_putstr("LARGE: ");
	ft_putstr("0x");
	ft_putnbr_base((size_t)node, B16);
	ft_putstr(" ---> ");
	ft_putnbr_base(node->nb_block, B10);
	ft_putstr(" block(s)\n");
	if (tmp == NULL)
		ft_putstr("No block allocated\n");
	while (tmp != NULL)
	{
//		*nb += sizeof(t_block);
		print_block(tmp, nb);
		tmp = tmp->next;
	}
}

void				show_alloc_mem()
{
	size_t		cat;
	t_heap		*ptr;
	size_t		nb_oct;

	cat = CAT_TINY;
	ptr = heap_ancor;
	nb_oct = 0;
	while (ptr != NULL)
	{
//		nb_oct += sizeof(t_heap);
		if (ptr->category == CAT_LARGE)
			print_node(ptr, &nb_oct);
		ptr = ptr->next;
	}
	if (nb_oct > 0)
	{
		ft_putstr("Total : ");
		ft_putnbr_base(nb_oct, B10);
		ft_putstr(" octet(s)\n");
	}
}
