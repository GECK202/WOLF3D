/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 15:28:57 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		main_selector(t_game *game)
{
	while (game->status > 0) {
		if (game->status == 1)
		{
			load_music(game);
			sdl_cycle(game);
		}
		else if (game->status == 2)
			map_editor(game);
		else if (game->status == 3)
			game->status = 0;
	}
}

int			main(int ac, char *av[])
{
	t_game		game;
	int			cheat;
	int			status;
	double		z_buffer[S_W * S_H];

	status = 1;
	if (S_W < 640 || S_H < 480)
		ft_exit("Bad resolution!!!");
	if (ac == 2) {
		cheat = ft_strcmp(av[1], "cheat");
		if (!ft_strcmp(av[1], "editor"))
			status = 2;
	}
	game.z_buffer = z_buffer;
	init_player(&game);
	load_map(&game.level, &game.player);
	if (!init_sdl(&game))
		return (free_init_sdl(&game));
	game.status = status;
	main_selector(&game);
	close_sdl(&game);
	return (0);
}


