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

	x = -1;
	if ((tab2 = (char*)malloc((1 * size) + 1)) == NULL)
		return (NULL);
	while (++x < size)
		tab2[x] = tab[x];
	tab2[x] = buf;
	return (tab2);
}

int		get_next_line(int const fd, char **line)
{
  	static	int	sta = 0;
	int		i;
	int		x;
	int		ret;
	int		test;
	char	buf[BUFF_SIZE + 1];

	i = 0;
	x = 0;
	test = 0;
	if (fd == -1)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) && ret != -1 && test != 1)
	{
		i = 0;
		while (buf[i] != '\n' && i < BUFF_SIZE && buf[i])
		{
			line[sta] = ft_allo_mem(line[sta], x, buf[i]);
			i++;
			x++;
			if (buf[i] == '\n')
				test = 1;
		}
	}
	sta++;
	ft_putnbr(sta);
	return (ret);
}

int	main(int ac, char **av)
{
	int		fd;
	char	**line;

	line = (char **)malloc(sizeof(line) * 10);
	if (!line)
		return (0);
	ac = ac * 1;
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, line);
	ft_putstr(line[0]);
	ft_putchar('\n');
	get_next_line(fd, line);
	ft_putstr(line[1]);
	return (0);
}
