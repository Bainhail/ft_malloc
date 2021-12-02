/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabihali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:43:45 by nabihali          #+#    #+#             */
/*   Updated: 2021/12/02 16:52:52 by nabihali         ###   ########.fr       */
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

static size_t	check_base(char *base)
{
	size_t    i;
	size_t    z;

	i = 0;
	z = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		z = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
			return (0);
		while (base[z])
		{
			if (base[i] == base[z])
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

void		ft_putnbr_base(size_t nb, char *base)
{
	size_t    nbr[100];
	size_t    size_base;
	int	    i;

	i = 0;
	size_base = 0;
	if (check_base(base))
	{
		while (base[size_base])
			size_base++;
		while (nb)
		{
			nbr[i] = nb % size_base;
			nb = nb / size_base;
			i++;
		}
		while (--i >= 0)
			ft_putchar(base[nbr[i]]);
	}
}
