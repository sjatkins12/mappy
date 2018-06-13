/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 16:11:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/13 16:19:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMM_H
# define FT_COMM_H

typedef struct			s_communication_methods
{
	int32_t				(*outgoing)(int32_t, char *);
	int32_t				(*incoming)(int32_t);
	int32_t				(*printraw)(int32_t);
}						t_communication_methods;

t_communication_methods			communication;

#endif
