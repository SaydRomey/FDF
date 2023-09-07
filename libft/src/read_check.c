/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:13:46 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/06 22:29:28 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
opens a file, attempts to read 1 byte from it
returns:
 0 if file is empty
 1 if file is not empty
-1 if there is a problem opening or reading from the file
*/
int	read_check(const char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(filename, READ);
	if (fd < 0)
		return (ERROR);
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read == 0)
		return (EMPTY);
	else if (bytes_read == -1)
		return (ERROR);
	return (VALID);
}
