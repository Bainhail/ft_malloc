/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:00:33 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/01 18:37:02 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include <stdlib.h>

int             main()
{
        char  *addr;

        addr = (char*)malloc(1024);
        addr = (char*)realloc(addr, 2048);
		free(addr);
        return (0);
}

/*int		main()
{
//	char	a;
	char	*test;
	t_heap	*tmp;
	t_heap	*tab[5];

	test = NULL;
	tmp = NULL;
	for (int i = 0; i < 5; i++)
		tab[i] = h_new_node(CAT_TINY, 9000001);
	for (int i = 0; i < 5; i++)
	{
		tmp = tab[i];
		printf("Category = %u\nSize max = %lu\nSize_free = %lu\nNB Block = %lu\nAddr noeud = %p\nAddr 1st block = %p\n\n",
			   tmp->category, tmp->size_max, tmp->size_free, tmp->nb_block, tmp, tmp->block_start);
	}
	for (int i = 0; i < 5; i++)
	{
		tmp = heap_ancor;
		h_remove_node(tab[i]);
		}
	char *cmd="ls -lRa ../";

	system(cmd);
	return (0);
	}*/
