/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_xpm_hex.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:42:46 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 16:42:48 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_XPM_HEX_H
# define CONVERT_XPM_HEX_H
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef	struct	s_values
{
	char		name[256][3];
	char		color[256][9];
	int			ni;
	int			k;
	int			i;
	int			fd;
}				t_values;

void			convert_xpm_hex(const char *fname, int **hex_a, int tex_size);

#endif
