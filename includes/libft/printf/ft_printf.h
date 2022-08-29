/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:34:49 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 16:25:05 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../include/libft.h"

int		ft_printf(const char *format, ...);
int		ft_putchar_len(int c);
int		ft_putstr_len(char *s);
int		ft_putnbr_len(int n, char specifier);
int		ft_hexlen(unsigned long n);
int		ft_puthex_len(unsigned long n, int specifier);
char	ft_htoc(unsigned long n, char specifier);
char	*ft_itoh(char *hex, int len, unsigned long n, char specifier);

#endif
