/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:33:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:14:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
writes a char to a file descriptor
returns the number of bytes written
**should it return a ssize_t for ERROR (-1) ?*
*/
size_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
