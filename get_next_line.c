/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/01/03 17:42:09 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

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
	}
	if (ret < 0)
		return (NULL);
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	int		i;
	static	char	**tmp;

	if (fd < 0 || !line)
		return (-1);
	if (!tmp)
	{
		if (!(tmp = (char **)malloc(sizeof(tmp) * 1000)))
			return (-1);
		if (!tmp[fd])
		{
			if ((tmp[fd] = ft_stockfile(fd)) == NULL)
				return (-1);
		}
	}
	i = 0;
	if (tmp[fd][i] == '\0')
		return (0);
	while (tmp[fd][i] != '\n' && tmp[fd][i])
		i++;
	*line = (char *)malloc(sizeof(*line) * (i + 1));
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
	while (get_next_line(fd, &line) == 1)
	{
		ft_putstr(line);
		ft_putchar('\n');
		i++;
	}
	return (0);
	}*/
