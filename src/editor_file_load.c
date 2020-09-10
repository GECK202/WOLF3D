/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/10 11:27:45 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		hex_to_int(char sym)
{
	static char	*hex = {"0123456789ABCDEF"};
	int			i;

	i = -1;
	while (++i < 16)
	{
		if (sym == hex[i])
			return (i);
	}
	return (-1);
}

int		read_base_color(t_map *map, char *data)
{
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

int		read_map(t_editor *ed, char *data, int cell)
{
	int			i;
	int			cmp[16];
	SDL_Point	p;
	int			s;

	if (cell == -1)
		return (read_base_color(&ed->map, data));
	i = -1;
	while (++i < 17)
		if ((cmp[i] = hex_to_int(data[i])) == -1)
			return (0);
	p.y = cell / 64;
	p.x = cell - p.y * 64;
	if ((ed->type_map[p.y][p.x] = cmp[0]))
	{
		ed->map.elem[p.y][p.x].number = (cmp[1] << 8) | (cmp[2] << 4) | cmp[3];
		ed->map.elem[p.y][p.x].modify = cmp[4];
		i = 2;
		s = 0;
		while ((i += 3) < 15)
			ed->map.elem[p.y][p.x].side[s++] = (cmp[i] << 8) | (cmp[i + 1] << 4) |
				cmp[i + 2];
	}
	else
		ed->map.elem[p.y][p.x].number = -1;
	return (1);
}

void	read_file(int fd, t_editor *ed, int *cell)
{
	int			n;
	char		buf[18];

	*cell = -2;
	while ((n = read(fd, buf, 18)))
	{
		++(*cell);
		if (*cell == 4096 || n != 18 || buf[17] != '\n' || !read_map(ed, buf,
			*cell))
		{
			close(fd);
			ft_exit("not valid map!");
		}
	}
}

void	load_ed_map(t_editor *ed)
{
	char		number;
	char		file[11];
	int			fd;
	int			cell;

	number = 1;
	ft_strcpy(file, "maps/map00");
	file[8] = number / 10 + '0';
	file[9] = number % 10 + '0';
	check_segv(file);
	if ((fd = open(file, 0x0000)) < 0)
		ft_exit("Hey man! It is are not a map!!!");
	read_file(fd, ed, &cell);
	close(fd);
	if (cell < 4095)
		ft_exit("not valid map!");
}
