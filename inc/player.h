/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 15:30:42 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/04 15:34:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H


typedef struct		s_playerpool
{
	t_queue			*data;
	int32_t			(*new)(void);
	t_dblist		*(*pop)(void);
	void			(*add)(t_player *add);
}					t_playerpool;

typedef struct		s_playerplace
{
	void			(*onboard)(t_player *);
	void			(*advance)(t_player *);
}					t_playerplace;

typedef struct		s_player_methods
{
	t_playerpool	pool;
	t_playerplace	place;
	int32_t			(*new)(int32_t);
	int32_t			(*command)(t_player *);
}					t_player_methods;

t_player_methods	player;

#endif
