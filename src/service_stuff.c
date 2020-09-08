/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/08 09:23:28 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_segv(char *file)
{
	int		fd;
	int		ret;
	char	buff[6];

	fd = open(file, O_RDONLY);
	if (!fd)
		ft_exit("U TRYINA SEGV ME?");
	ret = read(fd, buff, 5);
	if (!ret || ret < 0)
		ft_exit("U GIVING BAD FILES ARENT YA");
}

void	ft_exit(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
	exit(-1);
}

//void	free_l(t_game *game)
//{
//	free(game);
//}

int		free_init_sdl(t_game *game)
{
	close_sdl(game);
	//free_l(game);
	ft_exit("BAD THINGS HAPPENING TO SDL");
	return (-1);
}

/*
int		free_word_line(char **line, char **word)
{
	int i;

	i = 0;
	if (word)
	{
		if (word[i])
		{
			while (word[i])
			{
				free(word[i]);
				word[i] = NULL;
				++i;
			}
		}
		free(word);
		word = NULL;
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (i);
}
//*/
