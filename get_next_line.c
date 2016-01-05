/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/05 16:14:56 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stockfile(int const fd)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	str = "";
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
		if (ft_strchr(str, '\n'))
			break ;
	}
	//if (ret == 0)
	//return (NULL);
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	int				i;
	static	char	*tmp;

	if (!tmp)
		tmp = "";
	if (fd < 0 || !line)
		return (-1);
	tmp = ft_strjoin(tmp, ft_stockfile(fd));
	i = 0;
	if (tmp[i] == '\0')
		return (0);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	*line = (char *)malloc(sizeof(*line) * (i + 1));
	ft_strncpy(*line, tmp, i);
	tmp = &tmp[i + 1];
	return (1);
}
/*
int	main(int ac, char **av)
{
	int		fd;
	int	i;
	char	*line;

	line = NULL;
	ac = ac * 1;
	i = 0;
	fd = open(av[1], O_RDONLY);
	while ((i = get_next_line(fd, &line)) == 1)
	{
		ft_putnbr(i);
		ft_putchar('|');
		ft_putstr(line);
		ft_putchar('|');
		ft_putchar('\n');
		i++;
	}
	return (0);
}
*/
