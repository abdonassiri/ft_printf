/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnassir <abnassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:35 by abnassir          #+#    #+#             */
/*   Updated: 2025/12/08 16:33:04 by abnassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_nbr_unsigned(unsigned int nb)
{
	if (nb / 10)
		return (put_nbr_unsigned(nb / 10) + put_nbr_unsigned(nb % 10));
	else
		return (ft_putchar(nb + '0'));
}

int	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		return (ft_putchar('-') + put_nbr_unsigned(nb));
	}
	else
		return (put_nbr_unsigned(nb));
}
