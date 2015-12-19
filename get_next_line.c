/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2015/12/19 19:05:25 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <libft.h>

char    *ft_allo_mem(char *tab, int size, char buf)
{
	char    *tab2;
	int     x;

	x = 0;
	tab2 = (char*)malloc((1 * size) + 1);
	while (x < size)
	{
		tab2[x] = tab[x];
		x++;
	}
	tab2[x] = buf;
	return (tab2);
}

int		get_next_line(int const fd, char **line)
{
	int		i;
	int		x;
	char	*tab;
	char	buf[BUFF_SIZE + 1];

	i = 0;
	x = 0;
	line = NULL;
	tab = (char *)malloc(sizeof(tab) * (1 + 1));
	if (!tab)
		return (0);
	if (fd == -1)
		return (-1);
	while (read(fd, buf, BUFF_SIZE))
	{
		i = 0;
		while (buf[i] != '\n')
		{
			tab = ft_allo_mem(tab, x, buf[i]);
			i++;
			x++;
		}
	}
	ft_putstr(tab);
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	char	**line;

	line = NULL;
	ac = ac * 1;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	get_next_line(fd, line);
	return (0);
}
