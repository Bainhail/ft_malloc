#ifndef __FT_STDLIB_H__
#define __FT_STDLIB_H__

#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>

#define RET_TRUE 1
#define RET_FALSE 0

#define RET_BEFORE -1
#define RET_SAME 0
#define RET_AFTER 1

#define CAT_TINY 2
#define CAT_SMALL 4
#define CAT_LARGE 8
#define CAT_FREE 0

#define B2 "01"
#define B8 "01234567"
#define B10 "0123456789"
#define B16 "0123456789ABCDEF"

#define TINY_HEAP_SIZE (4 * getpagesize())
#define SMALL_HEAP_SIZE (32 * getpagesize())
#define TINY_BLOCK (TINY_HEAP_SIZE / 128)
#define SMALL_BLOCK (SMALL_HEAP_SIZE / 128)

typedef struct s_heap t_heap;
typedef struct s_block t_block;
typedef struct s_cache t_cache;

struct s_heap
{
	unsigned int	category;
	size_t			size_max;
	size_t			size_free;
	size_t			nb_block;
	void			*block_start;
	t_block			*block_first;
	t_heap			*next;
	t_heap			*prev;
};

struct s_block
{
	size_t			size;
	void			*heap_start;
	t_block			*next;
};

// GLOBAL Variable
extern t_heap *heap_ancor;

void init_global();
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

int check_limit(size_t size);
t_heap *look_for_heap(size_t cat, size_t size);

t_heap *h_new_node(unsigned int category, size_t *size);
t_heap *h_insert_node(t_heap *new_node);
void h_remove_node(t_heap *to_erase);

void *check_for_spot(t_heap **node, size_t size, t_block **insert);

t_block *insert_block(t_heap *node, size_t size);
void remove_block(t_heap *node, t_block *to_erase);

void ft_putchar(char c);
void ft_putstr(char *s);
void ft_putnbr(int n);
void ft_putnbr_base(size_t nb, char *base);

void show_alloc_mem();

#endif
