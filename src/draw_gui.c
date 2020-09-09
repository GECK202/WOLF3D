/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 15:31:53 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_gui(t_game *game)
{
	static int	counter = 0;
	static char	shift = 0;
		
	draw_gun(game, 0, 33);
	draw_back(game, 0, 1);
	draw_face(game, 3 + shift, 42);
	if (counter == 40)
	{
		shift ^= 1;
		counter = 0;
		return ;
	}
	counter += 1;
}

void	draw_back(t_game *game, int tile_u, int tile_v)
{
	game->drawer.cursor[0] = -1;
	while (++game->drawer.cursor[0] < S_W)
	{
		game->drawer.cursor[1] = -1;
		while (++game->drawer.cursor[1] < 65)
		{
			game->data[game->drawer.cursor[0] +
				S_W * (game->drawer.cursor[1] + S_H - 64)] =
				game->data_img[game->drawer.cursor[0] % 64 + 65 * tile_u +
				1039 * (game->drawer.cursor[1] + 64 * tile_v)];
		}
	}
}

void	draw_face(t_game *game, int tile_u, int tile_v)
{
	game->drawer.cursor[0] = -1;
	while (++game->drawer.cursor[0] < 64)
	{
		game->drawer.cursor[1] = -1;
		while (++game->drawer.cursor[1] < 64)
			if (game->data_img[game->drawer.cursor[0] + 65 * tile_u +
				1039 * (game->drawer.cursor[1] + 65 * tile_v)] != 0x980088)
				game->data[game->drawer.cursor[0] + (S_W - 64) / 2 +
				S_W * (game->drawer.cursor[1] + S_H - 64)] =
					game->data_img[game->drawer.cursor[0] +
					65 * (tile_u) +
					1039 * (game->drawer.cursor[1] + 65 * tile_v)];
	}
}

void	draw_gun(t_game *game, int tile_u, int tile_v)
{
	game->drawer.cursor[0] = -1;
	while (++game->drawer.cursor[0] < (S_H - GUN_SCALE))
	{
		game->drawer.cursor[1] = -1;
		while (++game->drawer.cursor[1] < (S_H - GUN_SCALE))
		{
			game->drawer.tex_d[0] = (game->drawer.cursor[0] /
				(double)(S_H - GUN_SCALE)) * 64;
			game->drawer.tex_d[1] = (game->drawer.cursor[1] /
				(double)(S_H - GUN_SCALE)) * 64;
			game->drawer.pix_img =
				game->drawer.tex_d[0] + 1039 * game->drawer.tex_d[1] +
				(64 * tile_u) + (67535 * tile_v);
			if (game->data_img[game->drawer.pix_img] != 0x980088)
				game->data[game->drawer.cursor[0] +
				(S_W - S_H + GUN_SCALE) / 2 +
				S_W * (game->drawer.cursor[1] + GUN_SCALE - 64)] =
				game->data_img[game->drawer.pix_img];
		}
	}
}
