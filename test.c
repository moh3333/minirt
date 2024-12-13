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
    mlx_destroy_image(data.mlx, data.img);
    mlx_destroy_window(data.mlx, data.win);
    mlx_destroy_display(data.mlx);
    free(data.mlx);

    printf("The projectile has hit the ground.\n");
    return 0;
}
