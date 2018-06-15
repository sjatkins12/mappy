/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_pdeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 20:12:56 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/14 13:14:50 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zappy.h"

t_pdeath	*pop_pdeath(t_pdeath **head)
{
	t_pdeath *tmp;

	if (!(*head))
		return (NULL);

	tmp = *head;
	*head = (*head)->next;
	return (tmp);
}
