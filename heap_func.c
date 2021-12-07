/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:53:21 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/07 15:01:12 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

/*
** Verification a 2 facteurs:
** - taille
** - categorie
*/
static size_t		get_heap_size(unsigned int *category, size_t *size)
{
	if (*category & CAT_TINY && *size <= (TINY_BLOCK - sizeof(t_block)))
		return (TINY_HEAP_SIZE);
	else if (*category & CAT_SMALL  && *size <= (SMALL_BLOCK - sizeof(t_block)))
		return (SMALL_HEAP_SIZE);
	*category = CAT_LARGE;
	if ((*size + sizeof(t_block)) % 16 != 0)
		*size += (16 - ((*size + sizeof(t_block)) % 16));
	return (*size + sizeof(t_block));
}

/*
** Creation d'une heap aillant une categorie specifique,
** En fonction de la taille et de la categorie donnees.
*/
t_heap				*h_new_node(unsigned int category, size_t *size)
{
	t_heap		*tmp;
	size_t		heap_size;

	tmp = NULL;
	heap_size = get_heap_size(&category, size) + sizeof(t_heap);
	if (*size == 0)
		*size = 1;
	if (*size > 0 && (category == CAT_TINY
					|| category == CAT_SMALL
					|| category == CAT_LARGE))
	{
		if ((tmp = (t_heap*)mmap(NULL, heap_size, PROT_READ | PROT_WRITE,\
								MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
			return (NULL);
		tmp->category = category;
		tmp->size_max = heap_size;
		tmp->size_free = heap_size - sizeof(t_heap);
		tmp->nb_block = 0;
		tmp->block_start = (void*)tmp + sizeof(t_heap);
		tmp->block_first = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return (tmp);
}

/*
** Insert le noeud avant ou apres le maillon de chaine
** Depend du flag envoyer en parametre.
x*/
void				h_insert_in_chain(t_heap **node, t_heap **chain, int flg)
{
	if (flg == 0)
	{
		(*node)->next = *chain;
		(*node)->prev = (*chain)->prev;
		(*chain)->prev = *node;
	}
	else
	{
		(*node)->next = (*chain)->next;
		(*chain)->next = *node;
		(*node)->prev = *chain;
	}
}

/*
** Insert une nouvelle heap dans la liste,
** En fonction de l'adresse du pointeur.
*/
t_heap				*h_insert_node(t_heap *new_node)
{
	t_heap		*tmp;
	int			flg;

	flg = -1;
	tmp = heap_ancor;
	if (tmp == NULL && new_node != NULL)
		heap_ancor = new_node;
	else if (tmp != NULL && new_node != NULL)
	{
		if ((new_node->category < tmp->category)
			|| ((new_node->category == tmp->category) && (new_node < tmp)))
			flg = 0;
		while (tmp->next != NULL && flg == -1)
		{
			if ((tmp->next != NULL && (new_node->category < tmp->next->category))
				|| ((new_node->category == tmp->next->category) && (new_node < tmp->next)))
				flg = 1;
			else
				tmp = tmp->next;
		}
		h_insert_in_chain(&new_node, &tmp, flg);
	}
	while (heap_ancor != NULL && heap_ancor->prev != NULL)
		heap_ancor = heap_ancor->prev;
	return (new_node);
}

/*
** A partir de noeud supprimer
** recreer les liens au sein de la chaine
*/
void				h_relink(t_heap **to_erase, t_heap **linker)
{
	if ((*linker)->prev != NULL)
	{
		*linker = (*linker)->prev;
		(*linker)->next = (*to_erase)->next;
		if ((*to_erase)->next != NULL)
			(*to_erase)->next->prev = *linker;
	}
	else if ((*linker)->next != NULL)
	{
		*linker = (*linker)->next;
		(*linker)->prev = (*to_erase)->prev;
		if ((*to_erase)->prev != NULL)
			(*to_erase)->prev->next = *linker;
	}
	else
		heap_ancor = NULL;
	if (heap_ancor != NULL)
	{
		while ((*linker)->prev != NULL)
			*linker = (*linker)->prev;
		heap_ancor = *linker;
	}
}

/*
** Retire une heap vide de la liste.
** Desalloue la memoire donnees par mmap.
*/
void				h_remove_node(t_heap *to_erase)
{
	t_heap		*tmp;

	tmp = heap_ancor;
	if (tmp != NULL && to_erase != NULL && to_erase->nb_block == 0)
	{
		while (tmp != NULL && tmp != to_erase
				&& (void*)tmp + tmp->size_max < (void*)to_erase)
			tmp = tmp->next;
		if (tmp == to_erase)
			h_relink(&to_erase, &tmp);
		munmap(to_erase, to_erase->size_max);
	}
}
