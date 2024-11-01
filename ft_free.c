#include "ft_stdlib.h"

void free(void *ptr)
{
  t_heap *tmp;
  t_block *test;

  test = NULL;
  init_global();
  tmp = heap_ancor;
  if (ptr != NULL && tmp != NULL)
  {
    while (tmp != NULL && (void *)tmp < ptr && ptr > (((void*)tmp + tmp->size_max)))
      tmp = tmp->next;
    if (tmp != NULL)
    {
      test = tmp->block_first;
      while (test != NULL && (void *)test != (ptr - sizeof(t_block)))
        test = test->next;
      if ((void *)test == (ptr - sizeof(t_block)))
        remove_block(tmp, (ptr - sizeof(t_block)));
    }
  }
}
