/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:14:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 16:36:39 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

# include "types.h" 

# define RAND_RESOURCE ((((((SRV_BORD.tiles)[x]).column)[y]).resources).items)

typedef struct			s_tile
{
	t_inventory			resources;
	t_player			*players[FD_SETSIZE];
	struct s_tile		*column;
}						t_tile;

typedef	struct			s_board
{
	int32_t				x;
	int32_t				y;
	t_tile				*tiles;
}						t_board;

typedef struct			s_board_methods
{
	t_board				data;
	int32_t				(*new)(void);
	int32_t				(*send_dimensions)(int32_t);
	void				(*resource_gen)(void);
	void				(*setplayer)(t_player *);
}						t_board_methods;

t_board_methods			board;

#endif
