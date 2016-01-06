/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/06 15:38:56 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_cleanstr(char *str, int size)
{
	int	i;

	i = -1;
	while (++i < size + 1 && str[i])
		str[i] = '\0';
}

static	char	*ft_strjoin_free(char *s1, char *s2)
{
	char    *tmp;

	tmp = ft_strdup(s1);
	ft_cleanstr(s1, ft_strlen(s1));
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	ft_cleanstr(tmp, ft_strlen(tmp));
	free(tmp);
	return (s1);
}

static	char	*ft_stockfile(int const fd)
{
	int		ret;
	int		i;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	str = ft_strnew(1);
	i = 1;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin_free(str, buf);
		i++;
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret < 0)
		return (NULL);
	return (str);
}

int				get_next_line(int const fd, char **line)
{
	int				i;
	char			*str;
	static	char	*tmp[1];

	if (!tmp[fd])
	if (!(tmp[fd] = (char *)malloc(sizeof(tmp[fd]) * (1))))
		return (-1);
	if (fd < 0 || !line || !(str = ft_stockfile(fd)))
		return (-1);
	tmp[fd] = ft_strjoin(tmp[fd], str);
	ft_cleanstr(str, ft_strlen(str));
	ft_strdel(&str);
	i = 0;
	if (tmp[fd][i] == '\0')
	{
		*line = NULL;
		ft_cleanstr(tmp[fd], ft_strlen(tmp[fd]));
		ft_strdel(tmp);
		return (0);
	}
	while (tmp[fd][i] != '\n' && tmp[fd][i])
		i++;
	*line = ft_strsub(tmp[fd], 0, i);
	ft_cleanstr(tmp[fd], i);
	tmp[fd] = &tmp[fd][i + 1];
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
