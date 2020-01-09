/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:15:01 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:26:01 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>
int raytrace_torus1(t_rt_param *par)
{
	t_quartic	q;
	t_vector3	o;
	int 		sol;
	t_orus		*t;

	t = par->object;

	o = sub_vect(par->origin, t->centre);
	double a = 1 - pow(dot(par->ray, t->normal), 2);
	double b = 2 * (dot(o, par->ray) -
			dot(t->normal, o) * dot(t->normal, par->ray));
	double c = dot_same(o) - dot(t->normal, o) * dot(t->normal, par->ray);
	double d = dot_same(o) + pow(t->o_dia, 2) - pow(t->i_dia, 2);
	q.a = 1;
	q.b = 4 * dot(par->ray, o);
	q.c = 2 * d + q.b * q.b * 0.25 - 4 * pow(t->o_dia, 2) * a;
	q.d = q.b * d - 4 * pow(t->o_dia, 2) * b;
	q.e = d * d - 4 * pow(t->o_dia, 2) * c;
	sol = solve_quartic(q, par);
	if (sol >= 2)
	{
		par->v = 1;
		par->v_2 = 1;
		if (par->i > par->i_2)
			d_swap(&(par->i), &(par->i_2));
		if (sol == 4)
		{
			par->v_3 = 1;
			par->v_4 = 1;
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i_3 > par->i_4)
				d_swap(&(par->i_3), &(par->i_4));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
		}
	}
	return (sol);
}

int raytrace_torus(t_rt_param *par)
{
	t_quartic	q;
	int 		sol;
	t_orus *t;

	t = par->object;
	t_vector3 x = sub_vect(par->origin, t->centre);
	double dx = dot(par->ray, x);
	double xv = dot(x, t->normal);
	double xx = dot_same(x);
	double dv = dot(par->ray, t->normal);
	double Rr = t->o_dia * t->o_dia - t->i_dia * t->i_dia;
	q.a = 1;
	q.b = 4 * dx;
	q.c = 4 * dx * dx + 2 * xx + 2 * Rr - 4 * t->o_dia * t->o_dia * (1 - dv * dv);
	q.d = 4 * dx * xx + 4 * Rr * dx - 8 * t->o_dia * t->o_dia * (dx - dv * xv);
	q.e = xx * xx + Rr * Rr + 2 * Rr * xx - 4 * t->o_dia * t->o_dia * (xx - xv * xv);
	sol = solve_quartic(q, par);
	if (sol >= 2)
	{
		par->v = 1;
		par->v_2 = 1;
		if (par->i > par->i_2)
			d_swap(&(par->i), &(par->i_2));
		if (sol == 4)
		{
			par->v_3 = 1;
			par->v_4 = 1;
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i_3 > par->i_4)
				d_swap(&(par->i_3), &(par->i_4));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
		}
	}
	return (sol);
}

t_vector3 normal_vector_torus1(t_vector3 point, void *tor)
{
	t_orus		*t;
	double		k;
	double		m;
	t_vector3	a;

	t = tor;
	k = dot(sub_vect(point, t->centre), t->normal);
	a = point_from_ray(point, t->normal, -k);
	m = sqrt(t->i_dia * t->i_dia - k * k);
	return (sub_vect(
		direction_vector(a, point),
		scalar_vect(sub_vect(t->centre, a), m / (t->o_dia + m))));
}

t_vector3 normal_vector_torus(t_vector3 point, void *tor)
{
	t_orus		*t;
	double		k;
	t_vector3	a;
	t_vector3	pr;

	t = tor;
	k = dot(sub_vect(point, t->centre), t->normal);
	a = point_from_ray(point, t->normal, -k);
	pr = normalise_vector(sub_vect(a, t->centre));
	pr = point_from_ray(t->centre, pr, t->o_dia);
	return (direction_vector(pr, point));
}
