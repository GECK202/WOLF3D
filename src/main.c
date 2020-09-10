/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 13:46:36 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		main_selector(t_game *game)
{
	double		*z_buffer;//[S_W * S_H];
	
	game->z_buffer = 0;
	if (!(z_buffer = (double*)ft_memalloc(sizeof(double) * S_W * S_H)))
		return ;
	game->z_buffer = z_buffer;
	while (game->status > 0) {
		if (game->status == 1)
		{
			//load_music(game);
			sdl_cycle(game);
		}
		else if (game->status == 2)
			map_editor(game);
		else if (game->status == 3)
			main_menu(game);
		else if (game->status == 4)
		{
			printf("U WIN!!!\n");
			break ;
		}
	}
	
	if (z_buffer)
		free(z_buffer);
	
	game->z_buffer = 0;
	
}

int			main(int ac, char *av[])
{
	t_game		*game;
	int			cheat;
	int			status;
	//double		z_buffer[S_W * S_H];
	
	status = 3;
	if (S_W < 640 || S_H < 480)// || S_W * S_H > 960000)
		ft_exit("Bad resolution! Use from 640x480 to 1200x800!");
	if (ac == 2) {
		cheat = ft_strcmp(av[1], "cheat");
		if (!ft_strcmp(av[1], "editor"))
			status = 2;
	}
	if (!(game = (t_game*)ft_memalloc(sizeof(t_game))))
		ft_exit("Memory was not allocated!");


	init_player(game);
	//load_map(&game->level, &game->player);
	if (!init_sdl(game))
		return (free_init_sdl(game));
	game->status = status;
	// def_icon(game->win, game->data_img, 0, 0);
	def_icon(game, 3, 4);
	main_selector(game);
	
	close_sdl(game);
	
	if (game)
		free(game);
	
	
	return (0);
}

// void	def_icon(SDL_Window	*win, int *img, int shift_x, int shift_y)
// {
// 	SDL_Surface		*icon[2];
// 	int				*icon_img;
// 	int				i;
// 	int				pixel;

// 	if (!(icon[1] = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0)))
// 		ft_exit("Memory was not allocated!");
// 	if (!(icon[0] = SDL_ConvertSurface
// 		(icon[1], SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32), 0)))
// 		ft_exit("Memory was not allocated!");
// 	SDL_FreeSurface(icon[1]);
// 	icon_img = (int *)icon[0]->pixels;
// 	i = -1;
// 	while(++i < 64 * 64)
// 	{
// 		pixel = i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65));
// 		if (img[pixel] == 0xFF980088)
// 		{
// 			icon_img[i] = 0;
// 			continue ;
// 		}
// 		icon_img[i] = img[pixel];
// 	}
// 	SDL_SetWindowIcon(win, icon[0]);
// }
void	def_icon(t_game *game, int shift_x, int shift_y)
{
	SDL_Surface		*icon[2];
	int				*icon_img;
	int				i;
	int				pixel;

	if (!(icon[1] = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0)))
		ft_exit("Memory was not allocated!");
	if (!(icon[0] = SDL_ConvertSurface
		(icon[1], SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32), 0)))
		ft_exit("Memory was not allocated!");
	SDL_FreeSurface(icon[1]);
	icon_img = (int *)icon[0]->pixels;
	i = -1;
	while(++i < 64 * 64)
	{
		pixel = i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65));
		// if (game->data_img[pixel] == 0x980088)
		// {
		// 	icon_img[i] = 0;
		// 	continue ;
		// }
		icon_img[i] = game->data_img[pixel];
	}
	SDL_SetWindowIcon(game->win, icon[0]);
}


