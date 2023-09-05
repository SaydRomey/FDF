/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:51:35 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:18:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Allocates with malloc, returns new null-terminated string
result of the concatenation of s1 and s2.
If the allocation fails the function returns NULL
**must be freed*
*/
char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*joined;
	char		*start;
	const char	*end1;
	const char	*end2;

	if (!s2)
		return (NULL);
	end1 = s1;
	end2 = s2;
	while (end1 && *end1)
		end1++;
	while (*end2)
		end2++;
	joined = (char *)malloc((end1 - s1) + (end2 - s2) + 1);
	if (!joined)
		return (NULL);
	start = joined;
	while (s1 && *s1)
		*start++ = *s1++;
	while (*s2)
		*start++ = *s2++;
	*start = '\0';
	return (joined);
}

/* using libft's functions

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	char	*start;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	if (s1)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	len_s2 = ft_strlen(s2);
	joined = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!joined)
		return (NULL);
	start = joined;
	if (s1)
		ft_strlcpy(start, s1, len_s1 + 1);
	start += len_s1;
	ft_strlcpy(start, s2, len_s2 + 1);
	return (joined);
}
*/
