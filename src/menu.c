/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/11 17:23:08 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	print_wolf(SDL_Surface *sdest, const char *text,
	SDL_Rect *dest, int f_size)
{
	const char	*f = "prgres/wf.otf";
	SDL_Color	col;
	TTF_Font	*fnt;
	SDL_Surface	*stext;

	col = (SDL_Color){171, 32, 46, 255};
	fnt = NULL;
	fnt = TTF_OpenFont(f, f_size);
	if (!fnt)
	{
		write(1, "Not open font!\n", 15);
		exit(0);
	}
	stext = TTF_RenderText_Blended(fnt, text, col);
	SDL_BlitSurface(stext, NULL, sdest, dest);
	SDL_FreeSurface(stext);
	TTF_CloseFont(fnt);
	dest->y += f_size;
}

void	draw_s_rect(t_game *game)
{
	SDL_Point	pos;
	SDL_Point	ind;
	Uint32		col;

	pos.y = H_H - 20 + H_H * game->menu_item / 5 - 1;
	while (++pos.y < H_H - 20 + H_H * (game->menu_item + 1) / 5)
	{
		ind.y = pos.y * S_W;
		pos.x = H_W + H_W / 2 - 10;
		while (++pos.x < S_W - 10)
		{
			ind.x = ind.y + pos.x;
			col = game->data[ind.x];
			game->data[ind.x] = (((col & 0xFF0000) >> 1) & 0xFF0000) |
				(((col & 0xFF00) >> 1) & 0xFF00) |
				(((col & 0xFF) >> 1) & 0xFF);
		} 
	}	
}

void	draw_menu(t_game *game)
{
	SDL_Point	pos;
	int			index;
	SDL_Rect	r;
	int			f_size;

	pos.y = -1;
	while (++pos.y < S_H)
	{
		index = pos.y * S_W;
		pos.x = -1;
		while (++pos.x < S_W)
		{
			game->data[index + pos.x] = game->data_menu[index + pos.x];
		}
	}
	r = (SDL_Rect){H_W + H_W / 2, H_H - 20, 0, 0};
	f_size = H_H / 5;
	if (game->menu_flag)
		draw_s_rect(game);
	if (game->comeback)
		print_wolf(game->surf, "Continue", &r, f_size);
	else
		r.y += f_size;
	print_wolf(game->surf, "New game", &r, f_size);
	print_wolf(game->surf, "Settings", &r, f_size);
	print_wolf(game->surf, "Editor", &r, f_size);
	print_wolf(game->surf, "Exit", &r, f_size);
}

void	main_menu(t_game *game)
{
	SDL_Point	flags;
	SDL_Event	e;
	//SDL_Rect	r;

	flags.x = 0;
	flags.y = 1;
	//r.h = 100;
	//r.w = 100;
	//r.x = 0;
	//r.y = 0;
	while (!flags.x)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_menu(game, e, &flags);
		if (flags.y)
		{
			draw_menu(game);
			SDL_UpdateWindowSurface(game->win);
			flags.y = 0;
		}
		SDL_Delay(5);
	}
	if (flags.x == 1)
		game->status = 0;
}
