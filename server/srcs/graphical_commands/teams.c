/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teams.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:55:24 by asyed             #+#    #+#             */
/*   Updated: 2018/06/13 17:13:56 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

void	send_teams(t_server *server)
{
	int					i;
	int					len;
	t_graphic_list		*node;

	i = 0;
	while (server->teams && server->teams[i])
	{
		strcpy(server->buff, "tna ");
		strcat(server->buff, server->teams[i]->name);
		strcat(server->buff, "\n");
		len = strlen(server->buff) + 1;
		if (!(node = server->graph_list))
			return ;
		while (node)
		{
			send(node->fd, server->buff, len, 0);
			node = node->next;
		}
		i++;
	}
}
