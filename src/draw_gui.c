/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 11:10:24 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	draw_gui(t_game *game)
{
	draw_back(game, 0, 1);
	draw_face(game, 3, 42);
	draw_gun(game, 0, 33);
}

void	draw_back(t_game *game, int tile_u, int tile_v)
{
	int		cursor[2];

	cursor[0] = -1;
	while (++cursor[0] < S_W)
	{
		cursor[1] = -1;
		while (++cursor[1] < 65)
		{
			game->data[cursor[0] + S_W * (cursor[1] + S_H - 64)] =
				game->data_img[cursor[0] % 64 + 65 * tile_u +
				1039 * (cursor[1] + 64 * tile_v)];
		}
	}
}



void	draw_face(t_game *game, int tile_u, int tile_v)
{
	int			cursor[2];
	static int	counter = 0;
	static char	shift = 0;

	cursor[0] = -1;
	while (++cursor[0] < 65)
	{
		cursor[1] = -1;
		while (++cursor[1] < 65)
			if (game->data_img[cursor[0] + 65 * tile_u +
				1039 * (cursor[1] + 65 * tile_v)] !=
				0x980088 && cursor[0] != 64 && cursor[1] != 64)
				game->data[cursor[0] + (S_W - 64) / 2 +
				S_W * (cursor[1] + S_H - 64)] =
					game->data_img[cursor[0] + 65 * (tile_u + shift) +
					1039 * (cursor[1] + 65 * tile_v)];
	}
	if (counter == 100)
	{
		shift ^= 1;
		counter = 0;
		return ;
	}
	counter += 1;
}

void	draw_gun(t_game *game, int tile_u, int tile_v)
{
	int		cursor[2];
	int		texel[2];

	cursor[0] = -1;
	while (++cursor[0] < (S_H - 100))
	{
		cursor[1] = -1;
		while (++cursor[1] < (S_H - 100))
		{
			texel[0] = (cursor[0] / (double)(S_H - 100)) * 65;
			texel[1] = (cursor[1] / (double)(S_H - 100)) * 65;
			if (texel[0] != 64 && texel[1] != 64 &&
				game->data_img[texel[0] + 1039 * texel[1] +
				(65 * tile_u) + (67535 * tile_v)] != 0x980088)
				game->data[cursor[0] + (S_W - S_H + 100) / 2 +
				S_W * (cursor[1] + 41)] =
				game->data_img[texel[0] + 1039 * texel[1] +
				(65 * tile_u) + (67535 * tile_v)];
		}
	}
}
