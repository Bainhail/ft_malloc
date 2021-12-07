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

#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
#include "ft_stdlib.h"

#define COUNT 1024

int			main()
{
  char *test;
  for (int i = 0; i < COUNT; i++)
    {
      test = malloc(1024);
      test[0] = 'a';
    }
  return (0);
}

/*int             main()
{
  char  *addr;

  printf("%lu\n", sizeof(t_block));

  malloc(1024);
  malloc(1024 * 32);
  malloc(1024 * 1024);
  malloc(1024 * 1024 * 16);
  malloc(1024 * 1024 * 128);
  //  show_alloc_mem();
  return (0);
}
*/
