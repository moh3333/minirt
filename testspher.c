#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define FOV 90.0

// Vector structure
typedef struct s_vec
{
    double x, y, z;
} t_vec;

// Ray structure
typedef struct s_ray
{
    t_vec origin;
    t_vec dir;
} t_ray;

// Sphere structure
typedef struct s_sphere
{
    t_vec center;
    double radius;
} t_sphere;

// Light structure
typedef struct s_light
{
    t_vec position;
    double intensity;
} t_light;

// Color structure
typedef struct s_color
{
    int r, g, b;
} t_color;

// Image structure (for mlx)
typedef struct s_img
{
    void *img;
    int *data;
    int bpp;
    int size_line;
    int endian;
} t_img;

// Main structure to hold the MLX window and image
typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_img img;
    t_vec camera_pos;
    t_sphere sphere;
    t_light light;
} t_mlx;
// Vector operations
t_vec vec_add(t_vec v1, t_vec v2)
{
    t_vec res = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return res;
}

t_vec vec_sub(t_vec v1, t_vec v2)
{
    t_vec res = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    return res;
}

t_vec vec_mul(t_vec v, double scalar)
{
    t_vec res = {v.x * scalar, v.y * scalar, v.z * scalar};
    return res;
}

double dot_product(t_vec v1, t_vec v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Check if a ray intersects a sphere
int intersect_ray_sphere(t_ray ray, t_sphere sphere, double *t)
{
    t_vec oc = vec_sub(ray.origin, sphere.center);
    double a = dot_product(ray.dir, ray.dir);
    double b = 2.0 * dot_product(oc, ray.dir);
    double c = dot_product(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant > 0)
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a); // closest intersection
        return 1;
    }
    return 0;
}
// Calculate color based on intersection
t_color get_color(t_ray ray, t_mlx *mlx)
{
    double t;
    if (intersect_ray_sphere(ray, mlx->sphere, &t))
    {
        // Basic color for sphere, apply lighting later
        return (t_color){255, 0, 0};  // Red color
    }
    return (t_color){0, 0, 0};  // Background color (black)
}

// Trace rays from the camera
void trace_scene(t_mlx *mlx)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            double px = (2 * ((x + 0.5) / (double)WIDTH) - 1) * tan(FOV / 2.0 * M_PI / 180.0) * WIDTH / HEIGHT;
            double py = (1 - 2 * ((y + 0.5) / (double)HEIGHT)) * tan(FOV / 2.0 * M_PI / 180.0);
            
            // Direction of the ray
            t_vec dir = {px, py, -1}; // Assuming camera is at (0, 0, 0) and pointing along the -z axis

            t_ray ray = {mlx->camera_pos, dir};

            // Get the color based on ray-sphere intersection
            t_color color = get_color(ray, mlx);

            // Place color in image buffer
            mlx->img.data[y * WIDTH + x] = (color.r << 16) | (color.g << 8) | color.b;
        }
    }
}
// Initialize MLX and create a window
void mlx_init_window(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Ray Tracing Sphere");
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.size_line, &mlx->img.endian);
}

// Check if the point is in shadow
int is_in_shadow(t_vec point, t_light light, t_sphere sphere)
{
    t_ray shadow_ray = {point, vec_sub(light.position, point)};
    double t;
    return intersect_ray_sphere(shadow_ray, sphere, &t); // If there's an intersection, it's in shadow
}
// Main function to set up the scene and render it
int main(void)
{
    t_mlx mlx;

    mlx.camera_pos = (t_vec){1, 2, -1}; // Camera at origin
    mlx.sphere.center = (t_vec){0, 0, -5}; // Sphere at (0, 0, -5)
    mlx.sphere.radius = 1.0;
    mlx.light.position = (t_vec){0, 5, -5}; // Light source
    mlx.light.intensity = 1.0;

    mlx_init_window(&mlx);

    trace_scene(&mlx);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
    mlx_loop(mlx.mlx);
    return 0;
}
