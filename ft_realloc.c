#include "ft_stdlib.h"

static t_heap *heap_recovery(void *ptr)
{
	t_heap *tmp;

	tmp = heap_ancor;
	while (tmp != NULL && (void *)tmp < ptr && ((void *)tmp + tmp->size_max) < ptr)
		tmp = tmp->next;
	return (tmp);
}

static t_block *block_recovery(void *ptr, t_heap *node)
{
	t_block *tmp;

	tmp = node->block_first;
	while (tmp != NULL && (void *)tmp != ptr)
		tmp = tmp->next;
	return (tmp);
}

static void *ft_memccpy(void *dst, void *src, size_t n)
{
	size_t i;
	unsigned char *c_dst;
	unsigned char *c_src;

	i = 0;

	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	while (i < n)
	{
		c_dst[i] = c_src[i];
		i = i + 1;
	}
	return (NULL);
}

void *realloc(void *ptr, size_t size)
{
	t_heap	*tmp = NULL;
	t_block	*addr = NULL;
	void	*tmp_ptr = ptr;

	init_global();
	tmp = heap_recovery(ptr);
	size = (size == 0) ? 1 : size;
	if (tmp == NULL || ptr == NULL)
		ptr = malloc(size);
	else if (tmp != NULL && ptr != NULL)
	{
		if ((addr = block_recovery(ptr - sizeof(t_block), tmp)) != NULL)
		{
			if (addr->size >= size)
			{
				ptr = addr;
				tmp->size_free += (addr->size - size);
				addr->size = size;
			}
			else
			{
				ptr = malloc(size);
				ft_memccpy(ptr, ((void *)addr + sizeof(t_block)), addr->size - sizeof(t_block));
				free(tmp_ptr);
			}
		}
		else
			ptr = NULL;
	}
	return (ptr);
}
