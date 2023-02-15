/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_exporter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:06:26 by mgarcia-          #+#    #+#             */
/*   Updated: 2023/02/15 02:47:54 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			create_file(char *name, int i, int j)
{
	char	*filename;
	int		path;
	int		fd;

	path = 0;
	filename = (char *)ec_malloc(ft_strlen(name) + 8);
	while (name[i])
		if (name[i++] == '/')
			path++;
	i = 0;
	while (path && name[i])
		if (name[i++] == '/')
			path--;
	ft_strcat(filename, IMG_PATH);
	j = 7;
	while (name[i] && name[i] != '.')
		filename[j++] = name[i++];
	filename[j] = '\0';
	ft_strcat(filename, ".bmp");
	if (!((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
													S_IRUSR | S_IWUSR)) > 0))
		fatal("in do_the_bmp_thing() while creating file");
	free(filename);
	return (fd);
}

void		create_header(t_scene scene, t_bmphead *header, t_dibhead *dib)
{
	header->type[0] = 0x42;
	header->type[1] = 0x4D;
	header->size = (scene.resolution_x * scene.resolution_y * 4) + 54;
	header->reserved = 0x00000000;
	header->offset = 0x36;
	dib->size = 40;
	dib->width = scene.resolution_x;
	dib->height = -scene.resolution_y;
	dib->colplanes = 1;
	dib->bits_per_pixel = 32;
	dib->compression = 0;
	dib->img_size = (scene.resolution_x * scene.resolution_y * 4);
	dib->x_ppm = 2835;
	dib->y_ppm = 2835;
	dib->color_number = 0;
	dib->important_color = 0;
}

void		write_header(int fd, t_bmphead header, t_dibhead dib)
{
	write(fd, &header.type, 2);
	write(fd, &header.size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &dib.size, 4);
	write(fd, &dib.width, 4);
	write(fd, &dib.height, 4);
	write(fd, &dib.colplanes, 2);
	write(fd, &dib.bits_per_pixel, 2);
	write(fd, &dib.compression, 4);
	write(fd, &dib.img_size, 4);
	write(fd, &dib.x_ppm, 4);
	write(fd, &dib.y_ppm, 4);
	write(fd, &dib.color_number, 4);
	write(fd, &dib.important_color, 4);
}

void		write_file(int fd, t_scene scene, t_minirt minirt)
{
	char	*pixel_array;
	int		image_size;
	int		i;
	int		j;

	pixel_array = (char *)ec_malloc(minirt.current_camera->size_line * scene.resolution_y);
	image_size = scene.resolution_x * scene.resolution_y;
	i = 0;
	j = 0;
	while (i < image_size)
	{
		pixel_array[j++] = minirt.current_camera->img_px[i] & 255;
		pixel_array[j++] = (minirt.current_camera->img_px[i] & 255 << 8) >> 8;
		pixel_array[j++] = (minirt.current_camera->img_px[i] & 255 << 16) >> 16;
		pixel_array[j++] = 0;
		i++;
	}
	write(fd, pixel_array, minirt.current_camera->size_line * scene.resolution_y);
	free(pixel_array);
}

void		do_the_bmp_thing(t_minirt minirt, t_scene scene, char *name)
{
	t_bmphead	header;
	t_dibhead	dib;
	int			fd;
	int			i;
	int			j;

	i = 0;
	j = 0;
	fd = create_file(name, i, j);
	create_header(scene, &header, &dib);
	write_header(fd, header, dib);
	write_file(fd, scene, minirt);
	close(fd);
}
