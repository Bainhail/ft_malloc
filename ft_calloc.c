/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:58:28 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 01:31:12 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DYLD_INTERPOSE_CAL(_replacment,_replacee) \
__attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };

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

	ft_putstr("CALLOC\n");
	mult = count * size;
	ft_putstr("CALLOC Before MALLOC\n");
	ptr = pMalloc(mult);
	ft_putstr("CALLOC After MALLOC\n");
	ft_bzero(ptr, mult);
	ft_putstr("CALLOC After BZERO\n");
	return (ptr);
}

DYLD_INTERPOSE_CAL(pCalloc, calloc);
