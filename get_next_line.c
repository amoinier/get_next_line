/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/05 17:05:57 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stockfile(int const fd)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	if (!(str = (char *)malloc(sizeof(str) * (BUFF_SIZE + 1))))
		return (NULL);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret < 0)
	{
		str = NULL;
		return (str);
	}
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	int				i;
	char	*str;
	static	char	*tmp[BUFF_SIZE];

	if (!tmp[fd])
		tmp[fd] = "";
	if (fd < 0 || !line || (str = ft_strdup(ft_stockfile(fd))) == NULL)
		return (-1);
	tmp[fd] = ft_strjoin(tmp[fd], str);
	i = 0;
	if (tmp[fd][i] == '\0')
		return (0);
	while (tmp[fd][i] != '\n' && tmp[fd][i])
		i++;
	if (!(*line = (char *)malloc(sizeof(*line) * (i + 1))))
		return (-1);
	ft_strncpy(*line, tmp[fd], i);
	tmp[fd] = &tmp[fd][i + 1];
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
	while ((i = get_next_line(42, &line)) == 1)
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
