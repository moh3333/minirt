/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:32 by mthamir           #+#    #+#             */
/*   Updated: 2024/12/12 18:13:31 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*if p_v is (1) creat point if its 0 creat vector */

t_tuple *creat_p_v(double x, double y, double z, int p_v)
{
	t_tuple *a;

	a = malloc(sizeof(t_tuple));
	if (!a)
		return (NULL);
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = p_v;
	return (a);
}

/* if it return (0) it's a point else it's a vector */
int is_p_v(t_tuple *a)
{
	return ((a->w == 1));
}

/* compare two floating point number we use a constant  */
int is_equal(double a, double b)
{
	return ((fabs(a-b) < EPSILON));
}
/* add two floating point number */
double	add(double a, double b)
{
	return (a + b);
}

/* subtract two floating point number */
double	subtruct(double a, double b)
{
	return (a - b);
}

/* multiply two floating point number */
double	multiply(double a, double b)
{
	return (a * b);
}

/* divide two floating point number */
double	divide(double a, double b)
{
	return (a / b);
}

/*operation two tuples */
t_tuple *tuples_A_S(t_tuple *a, t_tuple *b , char op)
{
	t_tuple *ret;
	double	(*f)(double p1, double p2);

	if(op == '+')
		f = add;
	else if(op == '-')
		f = subtruct;
	ret = malloc (sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = f(a->x, b->x);
	ret->y = f(a->y, b->y);
	ret->z = f(a->z, b->z);
	ret->w = f(a->w, b->w);
	return (ret);
}
/*get the opposite vector if the given is from a to b it will return the vector from b to a */
t_tuple *t_opposite(t_tuple *a)
{
	t_tuple *opp;

	opp = malloc (sizeof (t_tuple));
	if (!opp)
		return (NULL);
	opp->x = -a->x;
	opp->y = -a->y;
	opp->z = -a->z;
	opp->w = -a->w;
	return (opp);
}
/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar_multply(t_tuple *a, double scalar)
{
	t_tuple *ret;

	ret = malloc(sizeof (t_tuple));
	if (!ret)
		return (NULL);
	ret->x = (multiply(a->x, scalar));
	ret->y = (multiply(a->y, scalar));
	ret->z = (multiply(a->z, scalar));
	ret->w = (multiply(a->w, scalar));
	return (ret);
}

/* calcul square of a number */
double n_square(double num)
{
	return (num * num);
}

/* calculer magnitude of a vector (or its lengh) */
double magnitude(t_tuple *a)
{
	return (sqrt((n_square(a->x) + n_square(a->y) + n_square(a->z))));
}

/* check if its a unit vector */
double	is_unit_v(t_tuple *a)
{
	return ((magnitude(a) == 1));
}

/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple *a)
{
	t_tuple *ret;
	double v;

	ret = malloc (sizeof (t_tuple));
	if (!ret)
		return (NULL);
	v = magnitude(a);
	if (!v)
		return (a);
	ret->x = (a->x / v);
	ret->y = (a->y / v);
	ret->z = (a->z / v);
	ret->w = (a->w / v);
	return (ret);
}
/* if "a" and "b" are vector the dot product is "a"."b" return a number 
we need it to compare the direction of the two vectors */
/* if the two vectors are unit theire dot product is actually the cosine of the ongle between them */
double	Dot_product(t_tuple *a, t_tuple *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_vector(t_tuple *a, t_tuple *b)
{
	t_tuple *ret;

	ret = malloc(sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = ((a->y * b->z) - (a->z * b->y));
	ret->y = ((a->z * b->x) - (a->x * b->z));
	ret->z = ((a->x * b->y) - (a->y * b->x));
	ret->w = 0;
	return (ret);
}

/* colors addition and subtraction */

t_color *colors_operation(t_color *a, t_color *b, char op)
{
	t_color *ret;
	double (*f) (double a, double b);

	if (op == '+')
		f = add;
	else if (op == '-')
		f = subtruct;
	else if (op == '/')
		f = multiply;
	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = f(a->r, b->r);
	ret->g = f(a->g, b->g);
	ret->b = f(a->b, b->b);
	return (ret);
}

/* colors multiplication with a scalar */

t_color *colors_scalar_multiply(t_color *a, double scalar)
{
	t_color *ret;

	ret = malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = multiply(a->r, scalar);
	ret->g = multiply(a->g, scalar);
	ret->b = multiply(a->b, scalar);
	return (ret);
}

/*__________________________  putting theme together   ______________________________*/
/*______________________________________________*/

/*just for testing */


// typedef struct s_projectile	{
// 	t_tuple *position ;
// 	t_tuple *velocity ;
// } 		t_projectile;

// typedef struct s_envirement	{
// 	t_tuple *gravity;
// 	t_tuple *wind;
// }	t_envirement;

// t_projectile *creat_proj(t_tuple *position, t_tuple *velocity)
// {
// 	t_projectile *proj = malloc (sizeof(t_projectile));
// 	if (!proj)
// 		return (NULL);
// 	proj->position = position;
// 	proj->velocity = velocity;
// 	return (proj);
// }

// t_envirement *creat_env(t_tuple *position , t_tuple *wind)
// {
// 	t_envirement *env = malloc (sizeof(t_envirement));
// 	if (!env)
// 		return (NULL);
// 	env->gravity = position;
// 	env->wind = wind;
// 	return (env);
// }

// t_projectile *tick(t_envirement *env, t_projectile *proj)
// {
// 	t_tuple *pr ;
// 	t_tuple *pd ;
// 	pr = tuples_A_S(proj->position, proj->velocity, '+');
// 	pd = tuples_A_S(proj->velocity, tuples_A_S(env->gravity, env->wind, '+'), '+');
// 	return (creat_proj(pr, pd));
// }

// int main()
// {

// 	void *mlx = mlx_init();
// 	void *window = mlx_new_window(mlx, 2000, 2000, "TEST");
// 	t_projectile *proj = creat_proj(creat_p_v(0, 1, 0, 1), Normalize(creat_p_v(1, 1, 0, 0)));
// 	t_envirement *env = creat_env(creat_p_v(0, -0.1, 0, 0), creat_p_v(-0.01, 0, 0, 0));
// 	int ti = 0;
// 	while (proj->position->y > 0)
// 	{
// 		ti++;
// 		proj = tick(env, proj);
// 	}
// }
#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>  // for usleep()

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define GRAVITY -0.1  // downward acceleration (in units per tick)
#define WIND_X -0.01  // horizontal wind speed (in units per tick)

// Define a structure for the projectile
typedef struct s_projectile {
    double x;  // Position in X
    double y;  // Position in Y
    double vx; // Velocity in X direction
    double vy; // Velocity in Y direction
} t_projectile;

// Define a structure for the environment
typedef struct s_environment {
    double gravity; // Gravity vector (negative value for downward force)
    double wind_x;  // Horizontal wind force
} t_environment;

// Structure to store data related to the mlx window and image
typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
} t_data;

// Function to create the window and image for rendering
void init_mlx(t_data *data) {
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Projectile Simulation");
    data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
}

// Function to put a pixel at a given position in the image
void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
        int pixel = (y * data->line_length + x * (data->bpp / 8));
        *(unsigned int *)(data->addr + pixel) = color;
    }
}

// Function to create a projectile
t_projectile create_projectile(double x, double y, double vx, double vy) {
    t_projectile proj = {x, y, vx, vy};
    return proj;
}

// Function to create the environment
t_environment create_environment(double gravity, double wind_x) {
    t_environment env = {gravity, wind_x};
    return env;
}

// Function to update the projectile's position based on velocity and environment
void update_projectile(t_projectile *proj, t_environment *env) {
    proj->x += proj->vx;  // Update position in X
    proj->y += proj->vy;  // Update position in Y
    proj->vy += env->gravity;  // Apply gravity (affects vertical velocity)
    proj->vx += env->wind_x;   // Apply wind (affects horizontal velocity)
}

// Function to render the projectile on the screen as a red dot
void draw_projectile(t_data *data, t_projectile *proj) {
    int color = 0x00FF0000; // Red color
    my_mlx_pixel_put(data, (int)proj->x, (int)proj->y, color);
}

// Main simulation loop
int main() {
    t_data data;
    t_projectile proj = create_projectile(400, 100, 2, 0);  // Start at x = 400, y = 100, with velocity (vx = 2, vy = 0)
    t_environment env = create_environment(GRAVITY, WIND_X); // Gravity = -0.1, Wind = -0.01

    init_mlx(&data);

    // Main loop: update and render the projectile's position until it reaches the ground (y <= 0)
    while (proj.y >= 0) {
        mlx_clear_window(data.mlx, data.win);  // Clear the window for the new frame

        update_projectile(&proj, &env);  // Update the projectile's position based on gravity and wind

        draw_projectile(&data, &proj);   // Draw the updated projectile on the screen

        mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0); // Update the window with the new image

        usleep(10000);  // Pause to control the simulation speed (10 milliseconds per frame)
    }

    // Cleanup and exit
    // mlx_destroy_image(data.mlx, data.img);
    // mlx_destroy_window(data.mlx, data.win);
    // mlx_destroy_display(data.mlx);
    free(data.mlx);

    printf("The projectile has hit the ground.\n");
    return 0;
}
