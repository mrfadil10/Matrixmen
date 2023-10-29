/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:29 by mfadil            #+#    #+#             */
/*   Updated: 2023/10/29 14:38:26 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//static int	ft_count_words(const char *str, char c)
//{
//	int	i;
//	int	flag;

//	i = 0;
//	flag = 0;
//	while (*str)
//	{
//		if (*str != c && flag == 0)
//		{
//			flag = 1;
//			i++;
//		}
//		else if (*str == c)
//			flag = 0;
//		str++;
//	}
//	return (i);
//}

//static char	*ft_put_words(const char *str, int start, int end)
//{
//	char	*word;
//	int		i;

//	i = 0;
//	word = ft_calloc(sizeof(char), (end - start + 1));
//	while (start < end)
//		word[i++] = str[start++];
//	return (word);
//}

//char	**ft_split(char const *s, char *c)
//{
//	size_t	i;
//	size_t	j;
//	int		index;
//	char	**result;

//	i = 0;
//	j = 0;
//	index = -1;
//	if (!s)
//		return (NULL);
//	result = ft_calloc(sizeof(char *), (ft_count_words(s, c) + 1));
//	if (!s || !result)
//		return (0);
//	while (*s && i <= ft_strlen(s))
//	{
//		if (s[i] != c && index < 0)
//			index = i;
//		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
//		{
//			result[j++] = ft_put_words(s, index, i);
//			index = -1;
//		}
//		i++;
//	}
//	return (result);
//}

#include "libft.h"

static int	ft_is_delimiter(char c, char const *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	return (0);
}

static int	ft_countwords(char const *s, char const *charset)
{
	int	i;
	int	new;
	int	words;

	if (!s)
		return (0);
	words = 0;
	new = 1;
	i = -1;
	while (s[++i])
	{
		if (!ft_is_delimiter(s[i], charset))
		{
			if (new)
				words++;
			new = 0;
		}
		else
			new = 1;
	}
	return (words);
}

static char	*ft_strdupi(const char *s, char const *set, unsigned int *index)
{
	char	*minitab;
	int		i;
	int		len;

	len = 0;
	i = (*index) - 1;
	while (s[++i] && !ft_is_delimiter(s[i], set))
		len++;
	minitab = (char *) ft_calloc(len + 1, sizeof(char));
	if (!minitab)
		return (NULL);
	i = 0;
	while (s[(*index)] && !ft_is_delimiter(s[(*index)], set))
		minitab[i++] = s[(*index)++];
	return (minitab);
}

static void	ft_freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_split(char const *s, char const *charset)
{
	char			**tab;
	int				words;
	int				current;
	unsigned int	i;

	words = ft_countwords(s, charset);
	tab = (char **) ft_calloc(words + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	current = 0;
	i = 0;
	while (s && current < words)
	{
		while (s[i] && ft_is_delimiter(s[i], charset))
			if (!s[i++])
				break ;
		tab[current] = ft_strdupi(s, charset, &i);
		if (!tab[current++])
		{
			ft_freetab(tab);
			return (NULL);
		}
	}
	return (tab);
}