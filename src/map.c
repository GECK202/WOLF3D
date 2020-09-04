/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/04 17:51:51 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


static int		hex_to_int(char sym)
{
	static char *hex = {"0123456789ABCDEF"};
	int i;

	i = -1;
	while (++i < 16)
	{
		if (sym == hex[i])
			return (i);
	}
	return (-1);
}

static int		read_base_color(t_map *map, char *data)
{
	int tmp;
	int i;
	int	cmp[16];
	
	i = -1;
	while (++i < 16)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	map->roof = (Uint32)(0xFF000000 | (cmp[2] << 20) | (cmp[3] << 16) |
	(cmp[4] << 12) | (cmp[5] << 8) | (cmp[6] << 4) | cmp[7]);
	map->floor = (Uint32)(0xFF000000 | (cmp[10] << 20) | (cmp[11] << 16) |
	(cmp[12] << 12) | (cmp[13] << 8) | (cmp[14] << 4) | cmp[15]);
	return (1);
}

static int		read_map(t_map *map, char *data, int cell, t_player *pl)
{
	int			tmp;
	int			i;
	int			cmp[16];
	SDL_Point	p;
	t_type		t;

	if (cell == -1)
		return (read_base_color(map, data));
	i = -1;
	while (++i < 16)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	p.y = cell / 64;
	p.x = cell - p.y * 64;
	t = (t_type)cmp[0];
	if (t == WALL)
	{
		map->elem[p.y][p.x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
		map->elem[p.y][p.x].modify = cmp[4];
		map->elem[p.y][p.x].lock = 1;
		i = 2;
		if (cmp[4])
		{
			while ((i += 3) < 15)
				map->elem[p.y][p.x].side[0] = (cmp[i] << 8) | (cmp[i + 1] << 4) | cmp[ i + 2];
		}
		else
		{
			map->elem[p.y][p.x].side[0] = map->elem[p.y][p.x].number;
			map->elem[p.y][p.x].side[2] = map->elem[p.y][p.x].number;
			map->elem[p.y][p.x].side[1] = map->elem[p.y][p.x].number + 1;
			map->elem[p.y][p.x].side[3] = map->elem[p.y][p.x].number + 1;
		}
	}
	else
	{
		map->elem[p.y][p.x].number = -1;
		map->elem[p.y][p.x].lock = 0;
		if (t == PLAYER)
		{
			pl->obj.pos.x = p.x + 0.5;
			pl->obj.pos.y = p.y + 0.5;
		}
	}
	
	
	return (1);
}
//*
void	load_map(t_level *level, t_player *pl)
{
	int			number;
	char 		file[11];
	int			fd;
	char		buf[18];
	int			n;
	int 		cell;

	number = 1;
	ft_strcpy(file, "maps/map00");
	file[8] = number / 10 + '0';
	file[9] = number % 10 + '0';
	check_segv(file);

	if ((fd = open(file, 0x0000)) < 0)
		ft_exit("Hey man! It is are not a map!!!");
	cell = -2;
	while ((n = read(fd, buf, 18)))
	{
		++cell;
		if (cell == 4096 || n != 18 || buf[17] != '\n' || !read_map(&(level->map), buf, cell, pl))
		{
			close(fd);
			//printf("in %d\n",cell);
			ft_exit("not valid map!");
		}
	}
	close(fd);
	//printf("out %d\n",cell);
	if (cell < 4095)
		ft_exit("not valid map!");
}


//void	load_map()
//{
//	
//}

/*
void	load_map(t_level *level, t_player *pl)
{
	int i;
	int j;
	int number;

	level->number = 1;
	
	//set_color(&level->roof, 55, 55, 55);
	//set_color(&level->floor, 120, 120, 120);
	
	//set_color(&level->map.roof, 100,150,250);
	//set_color(&level->map.floor, 250,250,100);
	
	//level->map.width = 64;
	//level->map.height = 64;
	//level->map.max = 4096;//level->map.width * level->map.height;
	//int map[64][64];
	
	check_segv("maps/map1");
	SDL_RWops *rw = SDL_RWFromFile("maps/map1", "rb");
	if(rw != NULL) 
	{
    	size_t len = sizeof(level->map);
    	SDL_RWread(rw, &level->map, len, 1);
    	SDL_RWclose(rw);
	}
	else
		ft_exit("Failed load map");
	
	j = -1;
	while (++j < 64)
	{
		i = -1;
		while (++i < 64)
		{
			number = level->map.elem[j][i].number;
			if (number >= 0)
				level->map.elem[j][i].lock = 1;
			else
				level->map.elem[j][i].lock = 0;
			//level->map.elem[j][i].number = number;
			level->map.elem[j][i].side[0] = number;
			level->map.elem[j][i].side[1] = number + 1;
			level->map.elem[j][i].side[2] = number;
			level->map.elem[j][i].side[3] = number + 1;
		}
	}
		
	pl->obj.pos.x = (float)29 + 0.5;
	pl->obj.pos.y = (float)50 + 0.5;
	
	level->map.floor = 0x646464;	
	
	//if (!(level->map.elem = (t_map_elem *)ft_memalloc(
	//	sizeof(t_map_elem) * level->map.max)))
	//	ft_exit("Failed to alloc t_map_elem");
	
	/*
	j = -1;
	//while (++j < level->map.height)
	//{
	//	i = -1;
	//	while (++i < level->map.width)
	//	{
			level->map.elem[j * level->map.width + i].lock = 0;
			level->map.elem[j * level->map.width + i].number = 0;
			level->map.elem[j * level->map.width + i].side[0] = -1;
			level->map.elem[j * level->map.width + i].side[1] = -1;
			level->map.elem[j * level->map.width + i].side[2] = -1;
			level->map.elem[j * level->map.width + i].side[3] = -1;
			if (i == 0 || i == level->map.width - 1 || j == 0 || j == level->map.height - 1)
			{
				level->map.elem[j * level->map.width + i].lock = 1;
				level->map.elem[j * level->map.width + i].number = 0;
				level->map.elem[j * level->map.width + i].side[0] = 0;
				level->map.elem[j * level->map.width + i].side[1] = 0;
				level->map.elem[j * level->map.width + i].side[2] = 0;
				level->map.elem[j * level->map.width + i].side[3] = 0;
			}
		}		
	}
	//*/
	/*
	const char m[] ="22222222222"\
					"21001001012"\
					"20000+00002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21001110012"\
					"20010001002"\
					"20010901002"\
					"21010000012"\
					"22222222222";
					
	const char m3[] ="22222222222"\
					"21001001012"\
					"20000+00002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"22000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"22000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"22000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000000002"\
					"21000000012"\
					"21000000012"\
					"20000000002"\
					"20000900002"\
					"21000000012"\
					"20000000002"\
					"21000000012"\
					"22222222212";
					
	const char m2[] ="11111111111"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"20000000003"\
					"11111111111";
	
	//const char m2[] = "
	
	int k = 0;
	char c;
	int n;
	char b;
	int x,y;
	
	c = m[k];
	//ft_putchar(c);
	n = c - '0';
	printf("n=%d\n",n);
	
	while (c)
	{
		//b = i + '0';
		//ft_putchar(b);
		if (c == '+')
		{
			y = k/level->map.width;
			x = k - y * level->map.width;
			pl->obj.pos.x = (float)x + 0.5;
			pl->obj.pos.y = (float)y + 0.5;
			n = 0;
		}
		else
			n = c - '0';
		//printf("n=%d, i=%d\n",n, i);
		if (n)
			level->map.elem[k].lock = 1;
		else
			level->map.elem[k].lock = 0;
		if (n == 9)
			n = 10;
		else
			//n = n - 1;
			n = n+13;
		level->map.elem[k].number = n;
		level->map.elem[k].side[0] = n;
		level->map.elem[k].side[1] = n;
		level->map.elem[k].side[2] = n;
		level->map.elem[k].side[3] = n;
		k++;
		c = m[k];
	}
	
	k = 60;
	n = 3;
	level->map.elem[k].lock = 1;
	level->map.elem[k].number = n;
	level->map.elem[k].side[0] = 6;
	level->map.elem[k].side[1] = 7;
	level->map.elem[k].side[2] = 11;
	level->map.elem[k].side[3] = 10;
//*/		
//}
//*/
