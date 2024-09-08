/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemyden <ydemyden@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:49:54 by ydemyden          #+#    #+#             */
/*   Updated: 2024/09/08 12:29:08 by ydemyden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// string scanning operation || locate the FIRST occurrence of c
// (converted to a char) in the string pointed to by s.  The
// terminating NUL character is considered to be part of the string.
char	*ft_strchr(const char *s, int c)
{
	int				z;
	unsigned char	uc;

	uc = (unsigned char)c;
	z = 0;
	while (s[z] != '\0')
	{
		if (s[z] == uc)
			return ((char *)&s[z]);
		z++;
	}
	if (uc == '\0')
		return ((char *)&s[z]);
	return (NULL);
}

// calculates the length of a string, not including '\0'
size_t	ft_strlen(const char *s)
{
	size_t	z;

	z = 0;
	while (s[z] != '\0')
	{
		z++;
	}
	return (z);
}

// copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap (for overlaps is memmove)

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		z;
	char		*pdest;
	const char	*psrc;

	if (!dest || !src)
		return (NULL);
	pdest = (char *)dest;
	psrc = (const char *)src;
	z = 0;
	while (n > z)
	{
		pdest[z] = psrc[z];
		z++;
	}
	return (dest);
}

// returns a pointer to a new string which is
// a duplicate of the string s.
char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*dplct;

	if (!s)
		return (NULL);
	l = ft_strlen(s) + 1;
	dplct = malloc(l);
	if (!dplct)
		return (NULL);
	ft_memcpy(dplct, s, l);
	return (dplct);
}

// Allocates and returns a new string,
// which is the result of the concatenation of ’s1’ and ’s2’
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	if (s1)
		ft_memcpy(joined, s1, len1);
	if (s2)
		ft_memcpy(joined + len1, s2, len2 + 1);
	return (joined);
}
