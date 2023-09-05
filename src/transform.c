/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:52:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/04 22:36:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static t_point	scale_point(t_point point, double scaling_factor)
{
	point.x *= scaling_factor;
	point.y *= scaling_factor;
	return (point);
}

static t_point	translate_point(t_point point, int x_offset, int y_offset)
{
	point.x += x_offset;
	point.y += y_offset;
	return (point);
}

static t_point	rotate_point_z(t_point point, float angle)
{
	t_point	rotated;

	rotated.x = point.x * cos(angle) - point.y * sin(angle);
	rotated.y = point.x * sin(angle) + point.y * cos(angle);
	return (rotated);
}

static t_point	project_iso(t_point point, float iso_angle, int z)
{
	t_point	projected;

	projected.x = (point.x - point.y) * cos(iso_angle);
	projected.y = (point.x + point.y) * sin(iso_angle) - z;
	return (projected);
}

t_point	transform(t_point point, t_param *param, int z)
{
	point = scale_point(point, param->scale);
	z *= param->z_scale;
	point = rotate_point_z(point, param->z_angle);
	if (param->toggle.iso == ON)
		point = project_iso(point, ISO_ANGLE, z);
	point = translate_point(point, param->x_offset, param->y_offset);
	return (point);
}
