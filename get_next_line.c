/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/05 20:40:20 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char    *tmp;

	tmp = ft_strdup(s1);
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	return (s1);
}

char	*ft_stockfile(int const fd)
{
	int		ret;
	char	*buf;
	char	*str;

	str = ft_strnew(1);
	buf = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin_free(str, buf);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret < 0)
		str = NULL;
	free(buf);
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	int				i;
	char			*str;
	static	char	*tmp[BUFF_SIZE];

	if (!tmp[fd])
		tmp[fd] = ft_strnew(1);
	if (fd < 0 || !line || !(str = ft_strdup(ft_stockfile(fd))))
		return (-1);
	tmp[fd] = ft_strjoin_free(ft_strdup(tmp[fd]), str);
	free(str);
	i = 0;
	if (tmp[fd][i] == '\0')
	{
		*line = NULL;
		free(tmp[fd]);
		return (0);
	}
	while (tmp[fd][i] != '\n' && tmp[fd][i])
		i++;
	if (!(*line = (char *)malloc(sizeof(*line) * (i + 1))))
		return (-1);
	*line = ft_strsub(tmp[fd], 0, i);
	tmp[fd] = &tmp[fd][i + 1];
	//tmp[fd] = ft_strdup(ft_strchr(tmp[fd], '\n') + 1);
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
	i = 0;
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
