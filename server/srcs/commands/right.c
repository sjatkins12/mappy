/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:49:16 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/13 23:50:19 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

int		command_right(t_player *player, t_server *serv)
{
	printf("Player %d has sent command [right]\n", player->fd);
	player->direction = (player->direction * 2 == 8) ? NORTH : player->direction * 2;
	if (send(player->fd, MSG_OK, strlen(MSG_OK), 0) == -1)
		return (error(0, "Send", false));
	return (EXIT_SUCCESS);
}

//should be fine
