/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:51:06 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/14 13:11:32 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

int		command_connect_nbr(void *object, t_action_arg *arg)
{
	t_player 	*player;
	t_server	*serv;

	player = (t_player *)object;
	serv = g_server;
	printf("Player %d has sent command [connect_nbr]\n", player->fd);
	ft_bzero(serv->buff, 2048);
	ft_strcpy(serv->buff, ft_itoa(player->team->max_players - player->team->connected));
	ft_strcat(serv->buff, "\n");
	if (send(player->fd, serv->buff, ft_strlen(serv->buff), 0) == -1)
		return (EXIT_FAILURE);
	arg = (void *)arg;
	return (EXIT_SUCCESS);
}

//this one should be fine too
