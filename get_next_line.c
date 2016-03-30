/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 17:02:06 by amoinier          #+#    #+#             */
/*   Updated: 2016/03/30 19:35:02 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		ft_stockfile(int const fd, t_lect *lect)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmmp;

	while (!(ft_strchr(lect->tmp, '\n')) && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmmp = lect->tmp;
		if (!(lect->tmp = ft_strjoin(tmmp, buf)))
			return (-1);
		//free(tmmp);
	}
	return (ret);
}

// t_lect	**ft_realloc(t_lect **p, int nline)
// {
// 	t_lect	**tmp;
// 	int		i;
//
// 	i = 0;
// 	if (!(tmp = (t_lect **)malloc(sizeof(tmp) * (nline + 1))))
// 		return (NULL);
// 	while (i != nline)
// 	{
// 		tmp[i] = p[i];
// 		i++;
// 	}
// 	free(p);
// 	p = NULL;
// 	p = tmp;
// 	return (p);
// }

static	t_lect	*init_elem(int const fd)
{
	t_lect	*lect;

	if (!(lect = (t_lect *)malloc(sizeof(*lect) * 2)))
		return (NULL);
	if (!(lect->tmp = ft_strnew(2)))
		return (NULL);
	lect->fd = fd;
	lect->nb = 0;
	return (lect);
}

int				get_next_line(int const fd, char **line)
{
	static	t_lect	*lect;
	int				spc;
	char			*tt;

	if ((!lect && (!(lect = init_elem(fd)))))
		return (-1);
	if (fd < 0 || !line || BUFF_SIZE < 0 || ft_stockfile(fd, lect) < 0)
		return (-1);
	if (lect->tmp[0] == '\0' && (*line = NULL) == NULL)
		return (0);
	spc = ft_whereisc(lect->tmp, '\n');
	*line = ft_strsub(lect->tmp, 0, spc);
	if (!(tt = (char *)malloc(sizeof(tt) * (ft_strlen(lect->tmp) + 1))))
		return (-1);
	ft_strcpy(tt, &lect->tmp[spc + 1]);
	ft_strclr(lect->tmp);
	lect->tmp = ft_strcpy(lect->tmp, tt);
	free(tt);
	return (1);
}
