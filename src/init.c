/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 16:02:55 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		reformat(int *data_img, SDL_Surface *image, SDL_PixelFormat *fmt)
{
	int	i;
	int	j;
	int	index;
	SDL_Color	col;
	
	j = -1;
	while (++j < image->h)
	{
		i = -1;
		while (++i < image->w)
		{
			index = j * image->w + i;
			col.r = (data_img[index] & 0xFF0000)>>16;
			col.g = (data_img[index] & 0xFF00)>>8;
			col.b = (data_img[index] & 0xFF);
			data_img[index] = (col.b << fmt->Bshift) | (col.g << fmt->Gshift) | (col.r << fmt->Rshift);
		}
	}
}

int		init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) //|SDL_INIT_AUDIO
		return (ERROR);
	
	if (TTF_Init() == -1)
		return (ERROR);
	game->win = 0;
	game->win = SDL_CreateWindow("WOLF", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
	if (!game->win)
		return (ERROR);
	game->surf = SDL_GetWindowSurface(game->win);
	if (!game->surf)
		return (ERROR);
	game->data = (int *)game->surf->pixels;
	game->draw_map = 0;
	game->fps = 50;
	game->f_time = 1000 / game->fps;
	game->last_time = SDL_GetTicks();
	game->athlas = IMG_Load("res/athlas2.png");
	game->menu = IMG_Load("res/main_screen.png");
	//printf("alias");
	if (!game->athlas || !game->menu)
		return (ERROR);
	game->data_img = (int *)game->athlas->pixels;
	game->data_menu = (int *)game->menu->pixels;
	reformat(game->data_img, game->athlas, game->athlas->format);
	reformat(game->data_menu, game->menu, game->menu->format);
	

//printf("Pixel Color -> R: %d,  G: %d,  B: %d,  A: %d\n", fmt->Rshift, fmt->Gshift, fmt->Bshift, fmt->Ashift);


	
	return (OK);
}
