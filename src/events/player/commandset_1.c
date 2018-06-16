/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandset_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:14:04 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/16 12:27:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "events.h"
#include "communication.h"
#include "inventory.h"
#include "egg.h"

static int32_t		advance(void *entity);
static int32_t		ft_fork(void *entity);
static int32_t		connect_nbr(void *entity);
static int32_t		send_inventory(void *entity);

__attribute__((constructor))void	construct_playercommands_set1(void)
{
	struct s_eventhold ev0 = {"advance\n", &advance, 7};
	struct s_eventhold ev1 = {"fork\n", &ft_fork, 42};
	struct s_eventhold ev2 = {"connect_nbr\n", &connect_nbr, 0};
	struct s_eventhold ev3 = {"inventory\n", &send_inventory, 1};

	
	eventlookup[0] = ev0;
	eventlookup[1] = ev1;
	eventlookup[2] = ev2;
	eventlookup[3] = ev3;
}

static int32_t	advance(__attribute__((unused))void *entity)
{
	t_player	*pl;

	pl = (t_player *)entity;
	printf("[COMMAND]\n  player advanced\n");
	communication.outgoing(pl->c_fd, "ok\n");
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	event.is_waiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t	ft_fork(void *entity)
{
	t_player	*pl;

	pl = (t_player *)entity;
	if (egg.incubate(pl) == -1)
		communication.outgoing(pl->c_fd, "ko\n");
	else
		communication.outgoing(pl->c_fd, "ok\n");
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	event.is_waiting(pl);
	return (EXIT_SUCCESS);
}

static int32_t	connect_nbr(void *entity)
{
	t_player	*pl;
	char		*num;
	char		*str;
	int32_t		nlen;

	pl = (t_player *)entity;
	nlen = ft_numlen(pl->team->nplayers);
	if (!(num = ft_itoa(pl->team->nplayers))
		|| !(str = calloc(1, nlen + 2))
		|| !(str = ft_strfreecat(str, num))
		|| !(str = strcat(str, "\n"))
		|| (communication.outgoing(pl->c_fd, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	free(str);
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	return (EXIT_SUCCESS);
}

static int32_t	send_inventory(void *entity)
{
	t_player	*pl;
	char		*num;
	char		*str;
	int32_t		reslens;

	pl = (t_player *)entity;
	reslens = (sizeof("food") + sizeof("linemate") + sizeof("sibur")
				+ sizeof("deraumere") + sizeof("mendiane")
				+ sizeof("phiras") + sizeof("thystame") - 7);
	if (!(str = (char *)calloc(1, ((sizeof(char) * (7 * 3)) + reslens + 18)))
		|| !(str = strcat(str, "food "))
		|| !(num = ft_itoa(FOOD(pl->inventory.items)))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(LINEMATE(pl->inventory.items)))
		|| !(str = strcat(str, " linemate "))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(SIBUR(pl->inventory.items)))
		|| !(str = strcat(str, " sibur "))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(DERAUMERE(pl->inventory.items)))
		|| !(str = strcat(str, " deraumere "))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(MENDIANE(pl->inventory.items)))
		|| !(str = strcat(str, " mendiane "))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(PHIRAS(pl->inventory.items)))
		|| !(str = strcat(str, " phiras "))
		|| !(str = ft_strfreecat(str, num)))
		return (EXIT_FAILURE);
	if (!(num = ft_itoa(THYSTAME(pl->inventory.items)))
		|| !(str = strcat(str, " thystame "))
		|| !(str = ft_strfreecat(str, num))
		|| !(str = strcat(str, " \n"))
		|| (communication.outgoing(pl->c_fd, str) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	free(str);
	SRV_ALLP.status[pl->c_fd] = ACCEPTED;
	event.is_waiting(pl);
	return (EXIT_SUCCESS);
}
