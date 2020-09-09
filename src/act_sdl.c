/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/09 12:05:05 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_start(t_game *game)
{
	if (game->comeback == 0)
	{
		load_map(&game->level, &game->player);
		game->delay = 10;
	}
}

void	sld_events(t_game *game, SDL_Event e, int *quit, int *repaint)
{
	if (e.type == SDL_QUIT)
	{
		*quit = 1;
		game->status = 0;
	}
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*quit = 1;
		else
			key_press(e.key.keysym.sym, game);
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_press(&(e.button), game);
		*repaint = 1;
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		mouse_move(&(e.motion), game);
		if (game->status)
			*repaint = 1;
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		mouse_weel(e.wheel.y, game);
		*repaint = 1;
	}
}

void	check_keyboard(t_game *game, float d_time, int *quit)
{
	const	Uint8 *state = SDL_GetKeyboardState(NULL);

	game->comeback = 1;
	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
		move_forward(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
		move_back(&(game->player.obj), &game->level.map, d_time);
	if (state[SDL_SCANCODE_LEFT])
		turn_left(&(game->player.obj), d_time);
	else if (state[SDL_SCANCODE_RIGHT])
		turn_right(&(game->player.obj), d_time);
	if (state[SDL_SCANCODE_A])
		move_left(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_D])
		move_right(&(game->player.obj), &game->level.map, d_time);
	else if (state[SDL_SCANCODE_RETURN])
		{
			game->comeback = 0;
			++game->level.num;
			if (game->level.num > game->max_level)
			{
				*quit = 1;
				game->status = 4;
			}
			else
				check_start(game);
		}
}

void	redraw(t_game *game, int *fps)
{
	unsigned int	cur_time;
	

	cur_time = SDL_GetTicks();
	
	if (cur_time > game->last_time + game->f_time)
	{
		for (int i = 0; i < S_W * S_H; i++)
			game->z_buffer[i] = 100;
		draw_game(game);
		SDL_UpdateWindowSurface(game->win);
		SDL_FlushEvent(SDL_KEYDOWN);
		game->last_time = cur_time;
		*fps += 1;
	}
}




void	sdl_cycle(t_game *game)
{
	int			quit;
	SDL_Event	e;
	int			repaint;
	int			first;
	int			fps;
	int			lastTime;
	int			curTime;
	float		d_time;
	
	quit = 0;
	first = 1;
	fps = 0;
	check_start(game);
	lastTime = SDL_GetTicks();
	while (!quit)
	{
		d_time = (float)(SDL_GetTicks() - curTime)/1000.0;
		curTime = SDL_GetTicks();
		if (curTime > lastTime + 1000) {
			lastTime = curTime;
			fps = 0;
		}
		repaint = 0;
		check_keyboard(game, d_time, &quit);
		redraw(game, &fps);
		if (SDL_PollEvent(&e) != 0 || repaint)
			sld_events(game, e, &quit, &repaint);
		SDL_Delay(game->delay);
	}
	if (game->status != 0 &&  game->status != 4)
		game->status = 3;
}
