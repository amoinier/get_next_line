/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/03/29 20:11:54 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		ft_stockfile(int const fd, t_lect *lect)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmmp;

	//ft_putchar('A');
	//ft_putstr(lect->tmp);
	//ft_putchar('B');
	while (!(ft_strchr(lect->tmp, '\n')) && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmmp = lect->tmp;
		if (!(lect->tmp = ft_strjoin(tmmp, buf)))
			return (-1);
		free(tmmp);
	}
	return (ret);
}

static	t_lect	**ft_realloc(t_lect **p, int nline)
{
	t_lect	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (t_lect **)malloc(sizeof(tmp) * (nline + 1))))
		return (NULL);
	while (i != nline)
	{
		tmp[i] = p[i];
		i++;
	}
	free(p);
	p = NULL;
	p = tmp;
	return (p);
}

static	t_lect	*init_elem(int const fd)
{
	t_lect	*lect;

	if (!(lect = (t_lect *)malloc(sizeof(lect))))
		return (NULL);
	lect->fd = fd;
	lect->nb = 0;
	if (!(lect->tmp = ft_strnew(2)))
		return (NULL);
	return (lect);
}

int				get_next_line(int const fd, char **line)
{
	static	t_lect	**lect;
	int				spc;
	char			*tt;
	int				x;

	if ((!lect && (!(lect = (t_lect **)malloc(sizeof(lect))))) ||
	(!lect[0] && (!(lect[0] = init_elem(fd)))))
		return (-1);
	//ft_putchar('C');
	x = 0;
	while (x < lect[0]->nb && lect[x]->fd != fd)
		x++;
	//ft_putchar('D');
	if (!lect[x])
	{
		lect[0]->nb = x + 1;
		ft_realloc(lect, x + 1);
		lect[x + 1] = init_elem(fd);
		lect[x + 2] = NULL;
	}
	if (fd < 0 || !line || BUFF_SIZE < 0 || ft_stockfile(fd, lect[x]) < 0)
		return (-1);
	if (lect[x]->tmp[0] == '\0' && (*line = NULL) == NULL)
		return (0);
	spc = ft_whereisc(lect[x]->tmp, '\n');
	*line = ft_strsub(lect[x]->tmp, 0, spc);
	if (!(tt = (char *)malloc(sizeof(tt) * (ft_strlen(lect[x]->tmp) + 1))))
		return (-1);
	ft_strcpy(tt, &lect[x]->tmp[spc + 1]);
	ft_strclr(lect[x]->tmp);
	lect[x]->tmp = ft_strcpy(lect[x]->tmp, tt);
	free(tt);
	return (1);
}
