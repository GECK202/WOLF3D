/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/05 20:15:11 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_player(t_game *game)
{
	t_vec2 pos;

	pos.x = 4.5f;
	pos.y = 3.5f;
	init_object(&(game->player.obj),  pos, 0, 10, 2);
	game->player.sec.fov = 90 * M_PI / 180;
	game->player.sec.ang_step = game->player.sec.fov / S_W;
	game->player.ray_depth = 91;
}
