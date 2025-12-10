/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnassir <abnassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:24:31 by abnassir          #+#    #+#             */
/*   Updated: 2025/12/10 13:25:30 by abnassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_base(size_t nbr, char format)
{
	if (nbr >= 16)
		return (ft_hex_base(nbr / 16, format) + ft_hex_base(nbr % 16, format));
	else if (nbr < 10)
		return (ft_putchar(nbr + '0'));
	else
	{
		if (format == 'x')
			return (ft_putchar(nbr - 10 + 'a'));
		else
			return (ft_putchar(nbr - 10 + 'A'));
	}
}

int	ft_print_adress(void *adress)
{
	return (ft_putstr("0x") + ft_hex_base((unsigned long) adress, 'x'));
}
