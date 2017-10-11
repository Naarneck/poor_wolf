/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_xpm_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:42:39 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 16:42:42 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_xpm_hex.h"

int		ft_atoi_hex(char *str)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
	{
		if (n > 0xffffff)
			return (0xffffff);
		if (str[i] >= '0' && str[i] <= '9')
			n = (n * 16) + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			n = (n * 16) + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			n = (n * 16) + (str[i] - 'A' + 10);
		i++;
	}
	return (n);
}

int		find_name(char *name, t_values *values)
{
	int t;

	t = 0;
	while (t < 256)
	{
		if (name[0] == values->name[t][0] && name[1] == values->name[t][1])
		{
			free(name);
			return (t);
		}
		t++;
	}
	free(name);
	return (0);
}

void	def_table_fill(char *line, t_values *val)
{
	val->name[val->i][0] = line[1];
	val->name[val->i][1] = line[2];
	val->name[val->i][2] = '\0';
	val->color[val->i][0] = '0';
	val->color[val->i][1] = 'x';
	val->color[val->i][2] = line[7];
	val->color[val->i][3] = line[8];
	val->color[val->i][4] = line[9];
	val->color[val->i][5] = line[10];
	val->color[val->i][6] = line[11];
	val->color[val->i][7] = line[12];
	val->color[val->i][8] = '\0';
	val->i++;
}

void	convert_xpm_hex(const char *fname, int **hex_a, int tex_size)
{
	char		*line;
	t_values	val;

	val.i = 0;
	val.k = -1;
	val.fd = open(fname, O_RDONLY);
	*hex_a = malloc(sizeof(int) * (tex_size * tex_size));
	while (get_next_line(val.fd, &line) == 1)
	{
		if ((line[0] == '\"') && (line[14] == ',') && (line[12] != ' ')
		&& (line[13] == '\"'))
			def_table_fill(line, &val);
		else if ((line[0] == '\"') && (line[(tex_size * 2) + 1] == '\"')
		&& (ft_strlen(line) > (unsigned long)(tex_size * 2)))
		{
			val.i = 1;
			while (val.i < tex_size * 2)
			{
				val.ni = find_name(ft_strsub(line, val.i, 2), &val);
				(*hex_a)[++val.k] = ft_atoi_hex(val.color[val.ni]);
				val.i += 2;
			}
		}
		free(line);
	}
}
