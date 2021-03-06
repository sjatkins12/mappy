/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:09:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/12 16:10:15 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "board.h"
#include "communication.h"
#include "transmit.h"

static int32_t	all(void *trans);
static int32_t	mapsize(void *trans);

__attribute__((constructor)) void construct_transmit_tiles(void)
{
	transmit.tiles.all = &all;
	transmit.tiles.mapsize = &mapsize;
}

static int32_t		mapsize(void *trans)
{
	char	*num;
	int32_t	ret;

	num = ft_itoa(board.data.x + 1);
	server.sendbuf = strcat(server.sendbuf, "msz ");
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, " ");
	num = ft_itoa(board.data.y + 1);
	server.sendbuf = strcat(server.sendbuf, num);
	server.sendbuf = strcat(server.sendbuf, "\n");
	if (transmit.flag == GRAPHIC)
		ret = communication.graphical();
	else
		ret = communication.vehicles(trans, server.sendbuf, 1);
	bzero(server.sendbuf, server.nsend);
	return (ret);
}

static int32_t all(void *trans)
{
	int32_t x;
	int32_t y;
	char *num;

	x = 0;
	while (x <= board.data.x)
	{
		y = 0;
		while (y <= board.data.y)
		{
			server.sendbuf = strcat(server.sendbuf, "bct ");
			num = ft_itoa(x);
			server.sendbuf = strcat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, " ");
			num = ft_itoa(y);
			server.sendbuf = strcat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, " ");
			num = ft_itoa((board.data.tiles[x]).column[y].state);
			server.sendbuf = strcat(server.sendbuf, num);
			server.sendbuf = strcat(server.sendbuf, "\n");
			if (transmit.flag == GRAPHIC)
			{
				if (communication.graphical() == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else
			{
				if (communication.vehicles(trans, server.sendbuf, 1) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			bzero(server.sendbuf, server.nsend);
			y++;
		}
		x++;
	}
	bzero(server.sendbuf, server.nsend);
	return (EXIT_SUCCESS);
}
