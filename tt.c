 // int main()
// {
// 	t_matrix *s = rotat_matrix(radians(90), 'x');
// 	t_matrix *b = scal_matrix(5,5,5);
// 	t_matrix *c = transl_matrix(10,5,7);
// 	t_tuple *a = tuple_matrix_multi(multiply_matrixs(c, multiply_matrixs(b, s)), creat_p_v(1,0,1,1));
// 	printf("x == %.5f\n", a->x);
// 	printf("y == %.5f\n", a->y);
// 	printf("z == %.5f\n", a->z);
// 	printf("w == %.5f\n", a->w);
	
// }
 
 
 /*  : Computing a point from a distance To  find  the  position,  you  multiply  the  ray’s  direction  by  t  to  find  the  total
distance  traveled,  and  then  add  that  to  the  ray’s  origin. */
// int main()
// {
// 	t_tuple *a = position(creat_ray(creat_p_v(2,3,4,1), creat_p_v(1,0,0,0)), 0);
// 	printf("%.5f  %.5f  %.5f  %.5f\n", a->x, a->y, a->z, a->w);
// 	a = position(creat_ray(creat_p_v(2,3,4,1), creat_p_v(1,0,0,0)), 1);
// 	printf("%.5f  %.5f  %.5f  %.5f\n", a->x, a->y, a->z, a->w);
// 	a = position(creat_ray(creat_p_v(2,3,4,1), creat_p_v(1,0,0,0)), -1);
// 	printf("%.5f  %.5f  %.5f  %.5f\n", a->x, a->y, a->z, a->w);
// 	a = position(creat_ray(creat_p_v(2,3,4,1), creat_p_v(1,0,0,0)), 2.5);
// 	printf("%.5f  %.5f  %.5f  %.5f\n", a->x, a->y, a->z, a->w);

// }
// int get_b(int rgba)
// {
//     // Move 1 byte to the right and mask out the first byte.
//     return ((rgba >> 8) & 0xFF);
// }
// #define BPP sizeof(int32_t)

// int32_t	main(void)
// {
//     // Init mlx with a canvas size of 256x256 and the ability to resize the window.
//     mlx_t* mlx = mlx_init(1000, 500, "MLX42", true);
    
//     if (!mlx) exit(EXIT_FAILURE);

//     // Create a 128x128 image.
//     mlx_image_t* img = mlx_new_image(mlx, 1000, 1000);

//     // Set the channels of each pixel in our image to the maximum byte value of 255. 
//     memset(img->pixels, 0, img->height * img->height * BPP);

//     // Draw the image at coordinate (0, 0).
//     mlx_image_to_window(mlx, img, 0, 0);
// 	const char **str = malloc(12*sizeof(char *));
// 	str[0] = "0";
// 	str[1] = "1";
// 	str[2] = "2";
// 	str[3] = "3";
// 	str[4] = "4";
// 	str[5] = "5";
// 	str[6] = "6";
// 	str[7] = "7";
// 	str[8] = "8";
// 	str[9] = "9";
// 	str[10] = "10";
// 	str[11] = "11";
// 	str[12] = "12";
// 	str[13] = 	NULL;
// 	char *axe = "O";
// 	mlx_put_string(mlx, axe, 500, 250);
// 	t_tuple *a = creat_p_v(550, 300, 1, 1);
// 	int i = 0;
// 	while (str[i])
// 	{
// 		a = tuple_matrix_multi(rotat_matrix(radians((30)), 'x'), a);
// 		mlx_put_string(mlx, str[i], a->x, a->y);
// 		i++;
// 	}
//     // Run the main loop and terminate on quit.  
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }
//  int main()
//  {
// #define HIGHT 1000
// #define WIDTH 500
// int main()
// {
// 	mlx_t *a = mlx_init(WIDTH, HIGHT, "TESTING CLOCK", 0);
// 	mlx_image_t *i = mlx_new_image(a, WIDTH, HIGHT);
// 	mlx_image_to_window(a, i, 0, 0);
// 	a->
// }

// 	mlx_t *a = mlx_init(1000, 500, "donn" , 1);
// 	// mlx_image_t *d =  mlx_new_image(a, 1000, 500);
// 	// mlx_image_to_window(a, d, 1000,500);
// 	int x = 10;
// 	int y = 10;
// 	while (x < 1000)
// 	{
// 		mlx_put_string(a, "0", x, y);
		
// 		x += 10;
// 		y += 5;
// 	}

// 	mlx_loop(a);
//  }
/* testing the skeewing (shearing ) transformation */
// int main()
// {
// 	double arr[6] = {0,0,0,0,0,1};
// 	t_tuple *a = tuple_matrix_multi(skewing_matrix(arr), creat_p_v(2,3,4,1));
// 	printf("x == %.5f\n", a->x);
// 	printf("y == %.5f\n", a->y);
// 	printf("z == %.5f\n", a->z);
// 	printf("w == %.5f\n", a->w);

// }

/* testing rotat a vector or point around an axis x y or z */
// int main()
// {
// 	t_tuple *a = tuple_matrix_multi((rotat_matrix(radians(45), 'z')), creat_p_v(0,1,0,1));
// 	printf("x == %.5f\n", a->x);
// 	printf("y == %.5f  ====  %.5f\n", a->y , (sqrt(2) / 2));
// 	printf("z == %.5f\n", a->z);
// 	printf("w == %.5f\n", a->w);
// }

/* testing scalling a vector or point it affect to both of them by a scallar matrix */
// int main()
// {
	// t_tuple *r = scalling(creat_p_v(2,3,4,1), scal_matrix(-1,1,1));
	// printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
	/* scalling by inverse */
	// t_tuple *r = scalling(creat_p_v(-4,6,8,1), inverse(scal_matrix(2,3,4)));
	// printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
// }

/*test translate a point or vector but it does not affect with vectors && by transalte matrix and its inverse  */
// int main()
// {
// 	t_tuple *r = translat_point(creat_p_v(-3,4,5,1), inverse(transl_matrix(5,-3,2)));
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", r->x, r->y, r->z, r->w);
// }
/* testing the inverse of matrixs */

// int main()
// {
// 	t_matrix a;
// 	t_matrix b;

// 	a.matrix[0][0] = 3;
// 	a.matrix[0][1] = -9;
// 	a.matrix[0][2] = 7;
// 	a.matrix[0][3] = 3;

// 	a.matrix[1][0] = 3;
// 	a.matrix[1][1] = -8;
// 	a.matrix[1][2] = 2;
// 	a.matrix[1][3] = -9;

// 	a.matrix[2][0] = -4;
// 	a.matrix[2][1] = 4;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = -6;
// 	a.matrix[3][1] = 5;
// 	a.matrix[3][2] = -1;
// 	a.matrix[3][3] = 1;
// /*__________________________________*/

// 	b.matrix[0][0] = 8;
// 	b.matrix[0][1] = 2;
// 	b.matrix[0][2] = 2;
// 	b.matrix[0][3] = 2;

// 	b.matrix[1][0] = 3;
// 	b.matrix[1][1] = -1;
// 	b.matrix[1][2] = 7;
// 	b.matrix[1][3] = 0;

// 	b.matrix[2][0] = 7;
// 	b.matrix[2][1] = 0;
// 	b.matrix[2][2] = 5;
// 	b.matrix[2][3] = 4;

// 	b.matrix[3][0] = 6;
// 	b.matrix[3][1] = -2;
// 	b.matrix[3][2] = 0;
// 	b.matrix[3][3] = 5;
	// t_matrix *d = multiply_matrixs(&b, &a);
	// int i = 0;
	// int j = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (j < 4)
	// 	{
	// 		printf("%.5f  |", d->matrix[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// printf("\n");
	// t_matrix *ret = multiply_matrixs( d, inverse(&a));
	// i = 0;
	// j = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (j < 4)
	// 	{
	// 		printf("%.5f  |", ret->matrix[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// if (equal_matrix(&a, multiply_matrixs(multiply_matrixs(&a, &b), inverse(&b))))
	// 	printf("vereything works as expected \n");
	// else
	// 	printf("rak ghir katkhawer\n");
	

// }

/*waiting */

/*testing the determinant of the 3*3 matrix */
// int main()
// {
// 	t_3_3 a;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 6;

// 	a.matrix[1][0] = -5;
// 	a.matrix[1][1] = 8;
// 	a.matrix[1][2] = -4;

// 	a.matrix[2][0] = 2;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;

// 	double r = cofactor_3(&a, 0, 0);
// 	double r1 = cofactor_3(&a, 1, 0);
// 	double r2 = cofactor_3(&a, 2, 0);
// 	// double r3 = determinant_2(submatrix_2(&a));
// 	printf("%.0f\n", r);
// 	printf("%.0f\n", r1);
// 	printf("%.0f\n", r2);
// 	printf("%.0f\n", determinant_3(&a));
// 	printf("%.0f\n", (((r*a.matrix[0][0])+(r1*a.matrix[1][0])+(r2*a.matrix[2][0]))));
// }

/* testing the minor of the 3*3 matrix */
// int main()
// {
// 	t_3_3 a;

// 	a.matrix[0][0] = 3;
// 	a.matrix[0][1] = 5;
// 	a.matrix[0][2] = 0;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = -1;
// 	a.matrix[1][2] = -7;

// 	a.matrix[2][0] = 6;
// 	a.matrix[2][1] = -1;
// 	a.matrix[2][2] = 5;

// 	double r = ft_minor(&a, 1, 0);
// 	printf("%.0f\n", r);
// }

/* testing submatrix 2 and 3 */

// int main()
// {
// 	t_matrix a;

// 	a.matrix[0][0] = -6;
// 	a.matrix[0][1] = 1;
// 	a.matrix[0][2] = 1;
// 	a.matrix[0][3] = 6;

// 	a.matrix[1][0] = -8;
// 	a.matrix[1][1] = 5;
// 	a.matrix[1][2] = 8;
// 	a.matrix[1][3] = 6;

// 	a.matrix[2][0] = -1;
// 	a.matrix[2][1] = 0;
// 	a.matrix[2][2] = 8;
// 	a.matrix[2][3] = 2;

// 	a.matrix[3][0] = -7;
// 	a.matrix[3][1] = -1;
// 	a.matrix[3][2] = -1;
// 	a.matrix[3][3] = 1;

// 	t_3_3 *h = submatrix_3(&a, 2, 1);

// 	int i, j;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			printf("  %.0f |", h->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	} 
// 	printf("\n");
// 	t_2_2 *d = submatrix_2(h, 0, 2);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		j = 0;
// 		while (j < 2)
// 		{
// 			printf("  %.0f |", d->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	} 
// }



/* determinant of 2*2 matrix test */
// int main()
// {
// 	t_2_2 *a;
// 	a = malloc(sizeof(t_2_2));
// 	a->matrix[0][0] = 1;
// 	a->matrix[0][1] = 5;
// 	a->matrix[1][0] = -3;
// 	a->matrix[1][1] = 2;
// 	printf("%.0f\n", determinant_2(a));
// }

/* transpose test */

// int main()
// {
// 	t_matrix a;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;

// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", a.matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("_____________\n");
// 	t_matrix *ret = transpose(&a);
// 	i = 0;
// 	j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

/*multiply a identity matrice by a tuple and by a matrix test */

// int main()
// {
// 	t_matrix a;
// 	t_tuple b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;

// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;

// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;

// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	b.x = 1;
// 	b.y = 2;
// 	b.z = 3;
// 	b.w = 1;
// 	t_matrix *iden = identity_matrix();
// 	iden->matrix[0][1] = 6;
// 	t_tuple *re = tuple_matrix_multi(iden, &b);
// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", iden->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", re->x, re->y, re->z, re->w);
// 	printf("__________________________________________\n");
// 	t_matrix *ret = multiply_matrixs(&a, identity_matrix());

// 	i = 0;
// 	j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

/*multiply a matrice by a tuple test */

// int main()
// {
// 	t_matrix a;
// 	t_tuple b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;
// 	a.matrix[1][0] = 2;
// 	a.matrix[1][1] = 4;
// 	a.matrix[1][2] = 4;
// 	a.matrix[1][3] = 2;
// 	a.matrix[2][0] = 8;
// 	a.matrix[2][1] = 6;
// 	a.matrix[2][2] = 4;
// 	a.matrix[2][3] = 1;
// 	a.matrix[3][0] = 0;
// 	a.matrix[3][1] = 0;
// 	a.matrix[3][2] = 0;
// 	a.matrix[3][3] = 1;

// 	b.x = 1;
// 	b.y = 2;
// 	b.z = 3;
// 	b.w = 1;

// 	t_tuple *ret = tuple_matrix_multi(&a, &b);
// 	printf("%.0f\n%.0f\n%.0f\n%.0f\n", ret->x, ret->y, ret->z, ret->w);

// }
/*  test for multiplying matrices */

// int main()
// {
// 	t_matrix a;
// 	t_matrix b;

// 	a.matrix[0][0] = 1;
// 	a.matrix[0][1] = 2;
// 	a.matrix[0][2] = 3;
// 	a.matrix[0][3] = 4;
// 	a.matrix[1][0] = 5;
// 	a.matrix[1][1] = 6;
// 	a.matrix[1][2] = 7;
// 	a.matrix[1][3] = 8;
// 	a.matrix[2][0] = 9;
// 	a.matrix[2][1] = 8;
// 	a.matrix[2][2] = 7;
// 	a.matrix[2][3] = 6;
// 	a.matrix[3][0] = 5;
// 	a.matrix[3][1] = 4;
// 	a.matrix[3][2] = 3;
// 	a.matrix[3][3] = 2;

// 	b.matrix[0][0] = -2;
// 	b.matrix[0][1] = 1;
// 	b.matrix[0][2] = 2;
// 	b.matrix[0][3] = 3;
// 	b.matrix[1][0] = 3;
// 	b.matrix[1][1] = 2;
// 	b.matrix[1][2] = 1;
// 	b.matrix[1][3] = -1;
// 	b.matrix[2][0] = 4;
// 	b.matrix[2][1] = 3;
// 	b.matrix[2][2] = 6;
// 	b.matrix[2][3] = 5;
// 	b.matrix[3][0] = 1;
// 	b.matrix[3][1] = 2;
// 	b.matrix[3][2] = 7;
// 	b.matrix[3][3] = 8;

// 	t_matrix *ret = multiply_matrixs(&a, &b);

// 	int i = 0;
// 	int j = 0;
// 	while (i < 4){
// 		j = 0;
// 		while (j < 4){
// 			printf(" %.0f  |", ret->matrix[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}

// }

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
// 	t_projectile *proj = creat_proj(creat_p_v(0, 1, 0, 1), Normalize(creat_p_v(1, 1, 0, 0)));
// 	t_envirement *env = creat_env(creat_p_v(0, -0.1, 0, 0), creat_p_v(-0.01, 0, 0, 0));
// 	int ti = 0;
// 	while (1)
// 	{
// 		ti++;
// 		printf("proj y == %.5f\n", proj->position->y);
// 		printf("proj x == %.5f\n", proj->position->x);
// 		printf("proj z == %.5f\n", proj->position->z);
// 		printf("volecity y == %.5f\n", proj->velocity->y);
// 		printf("volecity x == %.5f\n", proj->velocity->x);
// 		printf("volecity z == %.5f\n", proj->velocity->z);
// 		proj = tick(env, proj);
// 		printf("\n");
// 		sleep(1);
// 	}
// 	printf("the projectile touch the ground");
// }
/* waiting */