/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:58:28 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 17:00:27 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

static void		ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*cpy;

	i = 0;
	cpy = (unsigned char*)s;
	while (i < n)
	{
		cpy[i] = 0;
		i = i + 1;
	}
}

void				*pCalloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		mult;

	ptr = NULL;
	mult = count * size;
	ft_putstr("CALLOC\n");
	if ((ptr = pMalloc(mult)) != NULL)
		ft_bzero(ptr, mult);
	ft_putstr("CALLOC FIN\n");
	return (ptr);
}

DYLD_INTERPOSE(pCalloc, calloc);
