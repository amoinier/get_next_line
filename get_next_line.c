/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/08 17:34:43 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	tmp = NULL;
	return (s1);
}

static	int		ft_stockfile(int const fd, char *tmp[fd], char *buf)
{
	int		ret;

	while (!(ft_strchr(buf, '\n')) && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp[fd] = ft_strjoin_free(tmp[fd], buf);
	}
	free(buf);
	buf = NULL;
	return (ret);
}

int				get_next_line(int const fd, char **line)
{
	int				i;
	char			*buf;
	char			*tt;
	static	char	*tmp[BUFF_SIZE];

	if (fd < 0 || !line ||
	(!(buf = (char *)malloc(sizeof(buf) * (BUFF_SIZE + 1)))))
		return (-1);
	if (!tmp[fd] && (!(tmp[fd] = (char *)malloc(sizeof(tmp[fd]) * (1 + 1)))))
		return (-1);
	if (ft_stockfile(fd, &(*tmp), buf) < 0)
		return (-1);
	if (*tmp[fd] == '\0')
	{
		*line = NULL;
		return (0);
	}
	i = 0;
	while (tmp[fd][i] != '\n' && tmp[fd][i])
		i++;
	*line = ft_strsub(tmp[fd], 0, i);
	tt = (char *)malloc(sizeof(tt) * (ft_strlen(tmp[fd]) + 1));
	ft_strcpy(tt, &tmp[fd][i + 1]);
	tmp[fd] = tt;
	free(tt);
	return (1);
}
/*
int		main(int ac, char **av)
{
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	ac = ac * 1;
	fd = open(av[1], O_RDONLY);
	while ((i = get_next_line(fd, &line)) == 1)
	{
		ft_putnbr(i);
		ft_putchar('|');
		ft_putstr(line);
		ft_putchar('|');
		ft_putchar('\n');
	}
	return (0);
}
*/
