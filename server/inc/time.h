/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:44:02 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 15:50:34 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef struct	timeval	t_timeval;

typedef struct			s_time_methods
{
	int32_t				(*compare)(t_timeval *, t_timeval *);
	void				(*setalarm)(t_timeval *, double);
	void				(*settimer)(t_timeval **);
}						t_time_methods;

t_time_methods		time;

#endif


