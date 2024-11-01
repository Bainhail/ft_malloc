#include "ft_stdlib.h"

t_heap *heap_ancor;

void init_global()
{
  static int flg = 0;

  if (flg == 0)
    heap_ancor = NULL;
  flg = 1;
}

int check_limit(size_t size)
{
  t_heap *tmp;
  struct rlimit lim;
  long long unsigned size_total;
  long long unsigned size_free;

  size_total = 0;
  size_free = 0;
  tmp = heap_ancor;
  while (tmp != NULL)
  {
    size_total += tmp->size_max;
    size_free += tmp->size_free;
    tmp = tmp->next;
  }
  if (getrlimit(RLIMIT_DATA, &lim) == 0)
  {
    if ((size_total + size) - size_free > lim.rlim_cur)
      return (RET_FALSE);
  }
  return (RET_TRUE);
}
