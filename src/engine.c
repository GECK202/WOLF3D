/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/04 20:09:39 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
void	set_col_num(t_vec2 *isc_pos, t_isec *isec, t_game *game, SDL_Point index)
{
	t_vec2		delta;
	int		number;
	int		number2;
	
	if (isc_pos->y < floor(isc_pos->y) + 0.5)
	{
		delta.y = isc_pos->y - floor(isc_pos->y);
		number = 0;
	}
	else
	{
		delta.y = floor(isc_pos->y) + 1.0 - isc_pos->y;
		number = 2;
	}
	if (isc_pos->x < floor(isc_pos->x) + 0.5)
	{
		delta.x = isc_pos->x - floor(isc_pos->x);
		number2 = 3;
	}
	else
	{
		delta.x = floor(isc_pos->x) + 1.0 - isc_pos->x;
		number2 = 1;
	}
	if (delta.x > delta.y)
	{
		isec->colum = (int)((isc_pos->x - (int)(isc_pos->x)) * 64);
		isec->number = game->level.map.elem[index.y][index.x].side[number];
		if (number == 0)
			isec->colum = 63 - isec->colum;
	}
	else
	{
		isec->colum = (int)((isc_pos->y - (int)(isc_pos->y)) * 64);
		isec->number = game->level.map.elem[index.y][index.x].side[number2];
		if (number2 == 1)
			isec->colum = 63 - isec->colum;
	}
}

void	engine(t_game *game, t_isec *isec, int x)
{
	float	ang;
	t_vec2	target;
	float	step;
	t_vec2	check_pos;
	SDL_Point index;

	ang = (game->player.obj.rot + game->player.sec.ang_step * x) * M_PI / 180;
	target.x = sin(ang);
	target.y = cos(ang);
	ang = (game->player.sec.ang_step * x) * M_PI / 180;
	step = 0;
	isec->height = 1;
	isec->number = 0;
	isec->dist = 100;
	while (step < 91)
	{
		step += 0.01;
		check_pos.x = (game->player.obj.pos.x + target.x * step);
		check_pos.y = (game->player.obj.pos.y + target.y * step);
		index.y = (int)check_pos.y;
		index.x = (int)check_pos.x;
		if (index.x >= 0 && index.x < 64 && index.y >= 0 && index.y < 64)
		{		
			if (game->level.map.elem[index.y][index.x].lock) {
				isec->dist = step;
				isec->height = H_W / (isec->dist * cos(ang));
				set_col_num(&check_pos, isec, game, index);
				return ;
			}
		}
	}
}
//*/
void	def_wallparams(t_player *player, t_drawer *drawer)
{
	drawer->ray_alpha = (player->sec.fov * (S_W / 2 - drawer->cursor_x)) / (double)S_W;
	drawer->wall_len = (S_W / (drawer->raylen[0] * cos(drawer->ray_alpha)));
}



void	engine(t_game *game, t_isec *isec, int x)
{
	t_drawer	*drawer;
	t_player	*player;
	t_map		*map;

	drawer = &(game->drawer);
	player = &(game->player);
	map = &(game->level.map);
	drawer->cursor_x = x + H_W;
	def_raylen(map, player, drawer);
	def_walltile(map, drawer);
	def_walltile_u(drawer);
	def_wallparams(player, drawer);

	
	
	isec->dist = drawer->raylen[0];
	isec->height = drawer->wall_len / 2;
	isec->number = drawer->wall_tile;
	isec->colum = drawer->tex_u;	
}
