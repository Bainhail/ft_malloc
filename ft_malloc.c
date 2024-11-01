#include "ft_stdlib.h"

static size_t select_category(size_t size)
{
  size = (size == 0) ? 1 : size;
  if (size >= 1 && size <= ((size_t)TINY_BLOCK))
    return (CAT_TINY);
  else if (size > ((size_t)TINY_BLOCK) && size <= ((size_t)SMALL_BLOCK))
    return (CAT_SMALL);
  return (CAT_LARGE);
}

t_heap *look_for_heap(size_t cat, size_t size)
{
  t_heap *tmp;

  tmp = heap_ancor;
  if (cat == CAT_LARGE && size > ((size_t)SMALL_BLOCK))
    return (NULL);
  while (tmp != NULL)
  {
    if ((tmp->category == cat || tmp->category == CAT_FREE) && tmp->size_free >= size)
    {
      if (tmp->category == CAT_FREE)
        tmp->category = cat;
      return (tmp);
    }
    tmp = tmp->next;
  }
  return (tmp);
}

void *malloc(size_t size)
{
  void *ptr;
  t_heap *addr;
  size_t cat;

  ptr = NULL;
  init_global();
  if (check_limit(size) == RET_FALSE)
    return (ptr);
  cat = select_category(size);
  if ((addr = look_for_heap(cat, size)) == NULL || cat == CAT_LARGE)
    addr = h_insert_node(h_new_node(cat, &size));
  if (addr != NULL)
  {
    ptr = insert_block(addr, size);
    ptr = ptr + sizeof(t_block);
  }
  return (ptr);
}
