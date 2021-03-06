/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:16:44 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 22:50:38 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "socket.h"
#include "board.h"
#include "events.h"
#include "vehicle.h"

void	__attribute__((constructor))construct_getopts(void)
{
	bzero(&server, sizeof(t_server));
	construct_server();
	construct_servergetopts();
	struct s_opts	opt0 = {"p", 1, server.opts.port};
	struct s_opts	opt1 = {"x", 1, server.opts.boardx};
	struct s_opts	opt2 = {"y", 1, server.opts.boardy};
	struct s_opts	opt3 = {"c", 1, server.opts.maxclients};
	struct s_opts	opt4 = {"f", 1, server.opts.boardload};
	struct s_opts	opt5 = {"d", 1, server.opts.destinations_nb};
	struct s_opts	opt6 = {"s", 1, server.opts.starts_nb};
	struct s_opts	opt7 = {NULL, 0, NULL};

	arr_opts[0] = opt0;
	arr_opts[1] = opt1;
	arr_opts[2] = opt2;
	arr_opts[3] = opt3;
	arr_opts[4] = opt4;
	arr_opts[5] = opt5;
	arr_opts[6] = opt6;
	arr_opts[7] = opt7;
}

int32_t		main(int argc, char **argv)
{
	int32_t	arg;

	arg = 0;
	if (argc < 7)
	{
		server.usagewarning(NULL);
		return (EXIT_FAILURE);
	}
	if ((arg = ft_getopts(arr_opts, argv)) != EXIT_SUCCESS)
		server.usagewarning(argv[arg]);
	server.new();
	if (errno != 60)
		perror(strerror(errno));
	return (EXIT_SUCCESS);
}
