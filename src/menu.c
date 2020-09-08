/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 16:15:15 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	main_menu(t_game *game)
{
	SDL_Point	flags;
	SDL_Event	e;

	flags.x = 0;
	flags.y = 1;
	//init_editor(&ed);
	while (!flags.x)
	{
		if (SDL_PollEvent(&e) != 0)
			sld_events_menu(game, e, &flags);
		if (flags.y)
		{
			SDL_FillRect(game->surf, NULL, 0xFFFF00000);
            
			//draw_map_editor(game, &ed);
			//draw_col_frame(game, &ed, ed.cursor.pos, 0xFFFF0000);
			//draw_menu(game, &ed);
			//status_selector(game, &ed);
            SDL_BlitSurface(game->surf, NULL, game->menu, NULL);
			SDL_UpdateWindowSurface(game->win);
			flags.y = 0;
		}
		SDL_Delay(5);
	}
    if (flags.x == 1)
	    game->status = 0;
}