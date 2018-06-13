/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:40:27 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 14:35:18 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int32_t	new(void);
static void		disconnect(int32_t cl);

__attribute__((constructor))void	construct_client(void)
{
	client.new = &new;
	client.disconnect = &disconnect
}

static inline __attribute__((always_inline))void	add_fd_select(int32_t sock)
{
	printf("fd to add : <%d>\ncurrent nfds : <%d>\n", sock, SRV_SOCK.nfds);
	FD_SET(sock, SRV_SOCK.copy);
	if (SRV_SOCK.nfds <= sock)
		SRV_SOCK.nfds = (sock + 1);
}

static int32_t		new(void)
{
	int32_t	newfd;
	int32_t	ret;

	ret = EXIT_SUCCESS;
	printf("<--- NEW CLIENT --->\n");
	newfd = accept(SRV_SOCK.sockfd,
				(struct sockaddr *)&(SRV_SOCK.temp), &(SRV_SOCK.socklen));
	(SRV_ALLP.status)[newfd] = NOT_ACCEPTED;
	add_fd_select(newfd);
	if (!SRV_GENV.maxinitial_clients && !SRV_GENV.maxingame_players)
	{
		client.disconnect(newfd);
		printf("Client %d rejected, not allowed\n", newfd);
	}
	else
	{
		ret = communication.outgoing(newfd, "WELCOME\n");
		printf("New client %d connected\n", newfd);
	}
	return (ret);
}

static void			disconnect(int32_t cl)
{
	printf("Remove client <%d> from fdset and lookup\n", cl);
	if (SRV_ALLP.lookup[cl])
	{
		// call player removal to add player back to pool
		if ((((SRV_ALLP.lookup)[cl])->team))
		{
			printf("Deleting reference to player in team\n");
			((((SRV_ALLP.lookup)[cl])->team)->players)[cl] = NULL;
		}
	}
	if ((SRV_ALLP.status)[cl] != DEAD)
		SRV_GENV.maxclients++;
	(SRV_ALLP.status)[cl] = 0;
	close(cl);
	FD_CLR(cl, SRV_SOCK.copy);
}
