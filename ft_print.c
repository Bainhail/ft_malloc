/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:43:45 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 02:15:36 by nabihali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

void		ft_putnbr(int n)
{
	int		cp;
	int		mod;

	mod = 1;
	if (n >= 0)
		n = n * (-1);
	else
		ft_putchar('-');
	cp = n;
	while (cp < -9)
	{
		cp = cp / 10;
		mod = mod * 10;
	}
	while (mod > 0)
	{
		ft_putchar('0' + ((n / mod) * -1));
		n = n % mod;
		mod = mod / 10;
	}
}
