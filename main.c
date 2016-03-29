/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoinier <amoinier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 18:22:11 by amoinier          #+#    #+#             */
/*   Updated: 2016/03/29 19:53:39 by amoinier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(int ac, char **av)
{
	char	*line;
	int		a;
	int 	fd;
	ac = 2;

	fd = open(av[1], O_RDONLY);
	while ((a = get_next_line(fd, &line)) > 0)
	{
		//ft_putnbr(a);
		ft_putchar('\n');
		ft_putstr(line);
		ft_putchar('\n');
	}
	ft_putnbr(a);
	return (0);
}
