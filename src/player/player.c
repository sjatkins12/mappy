/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:20:08 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/09 16:44:44 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"
#include "communication.h"
#include "commands.h"
#include "player.h"
#include "team.h"

#define PBUF ((SRV_ALLP.lookup)[cl])->buf

/* method function prototypes */
static int32_t	add_toteam(int32_t cl);
static int32_t	new(int32_t cl);

/* method object */
t_player_methods	player = {
	&new,
	&add_toteam,
	&parse_command
};

static int32_t	add_toteam(int32_t cl)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;

	p = (SRV_ALLP.lookup)[cl];
	ret = 0;
	i = 0;
	// add client removal on too many attempts
	if ((ret = communicate.fromclient.incoming(p)) == -1)
		return (EXIT_SUCCESS);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((i = team.name_exists(cl)) == -1)
	{
		ret = communicate.toclient.outgoing(cl, "INVALID TEAMNAME\n");
		p->conn_attempts++;
		if (p->conn_attempts == 10)
			client.del(cl);
	}
	else
	{
		ret = team.add_player(cl, i);
		SRV_ALLP.client_stat[cl] = ACCEPTED;
	}
	return (ret);
}

static int32_t	new(int32_t cl)
{
	t_player	*p;
	int32_t		ret;
	int32_t		i;
	
	printf("Creating new player <%d>\n", cl);
	ret  = 0;
	i = 0;
	if (!(p = (t_player *)ft_memalloc(sizeof(t_player))))
		return (EXIT_FAILURE);
	p->c_fd = cl;
	(SRV_ALLP.lookup)[cl] = p;
	return (EXIT_SUCCESS);
}

static int32_t	parse_command(int32_t cl)
{
	char	*firstword_delim;
	char	hold;

	if (communicate.fromclient.incoming((SRV_ALLP.lookup)[cl]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((firstword_delim = strchr(PBUF, ' ')))
	{
		hold = *firstword_delim;
		*firstword_delim = '\0';
	}
	commands.lookup(cl);
	return (EXIT_SUCCESS);
	// if command not recognized, print raw

}

static void		placeonboard(int32_t cl)
{
	t_player	*pl;

	pl = (SRV_ALLP.lookup)[cl];
	pl.location.x = arc4random_uniform((uint32_t)SRV_BORD.x);
	pl.location.y = arc4random_uniform((uint32_t)SRV_BORD.y);
	pl.location.orientation = arc4random_uniform((uint32_t)4);
	board.setplayer(cl);
}

/*
static int32_t		delete(void)
{
}

static int32_t		elevate(void)
{
}

static int32_t		see(void)
{
}

static int32_t		advance(void)
{
}

static int32_t		turn_right(void)
{
}

static int32_t		turn_left(void)
{
}

static int32_t		inventory(void)
{
}

static int32_t		take(object)
{
}

static int32_t		put(object)
{
}

static int32_t		broadcast(char *str)
{
}

static int32_t		incantation()
{
}

static int32_t		death()
{
}
*/
