#include "../minirt.h"

void *ft_malloc(size_t size)
{
	return(calloc(1, size));
}

t_comps *new_comps()
{
	t_comps *new;

	new = ft_malloc(sizeof(t_comps));
	return (new);
}

t_intersect *new_intersect()
{
	t_intersect *ret;

	ret = ft_malloc(sizeof(t_intersect));
	if (!ret)
		return (NULL);
	ret->next = NULL;
	return (ret);
}

t_camera *new_camera(double hsize, double vsize, double fov, t_matrix *transformation)
{
	t_camera *cam;
	double half_view = 0;

	cam = ft_malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	half_view = tan(fov / 2);
	cam->aspect_ratio = hsize / vsize;
	if (cam->aspect_ratio >= 1.0)
	{
		cam->half_width = half_view;
		cam->half_hight = half_view / cam->aspect_ratio;
	}
	else
	{
		cam->half_width = half_view * cam->aspect_ratio;
		cam->half_hight = half_view;
	}
	cam->horizontal_size = hsize;
	cam->pixel_size = (cam->half_width * 2) / cam->horizontal_size;
	cam->vertical_size = vsize;
	cam->field_of_view = fov;
	cam->transform = transformation;
	cam->transform_inverse = inverse(transformation);
	return (cam);
}


t_color *new_color(double r, double g, double b)
{
	t_color *col = ft_malloc(sizeof(t_color));
	col->r = r;
	col->g = g;
	col->b = b;
	return (col);
}

uint64_t get_col(t_color * color)
{
	uint64_t r = fmax(0.0, fmin(255.0, color->r * 255.0));
	uint64_t g = fmax(0.0, fmin(255.0, color->g * 255.0));
	uint64_t b = fmax(0.0, fmin(255.0, color->b * 255.0));
	return (((uint64_t)r << 24) | ((uint64_t)g << 16) | ((uint64_t)b << 8) | 0xFF);
}
/* colors addition and subtraction */

t_color *colors_operation(t_color *a, t_color *b, double (*f) (double a, double b))
{
	return (new_color(f(a->r, b->r), f(a->g, b->g), f(a->b, b->b)));
}

/* colors multiplication with a scalar */

t_color *color_s_mul(t_color *a, double scalar)
{
	return (new_color(mul(a->r, scalar), mul(a->g, scalar), mul(a->b, scalar)));
}

/* get teh rgba format of a color from a number */

t_color *to_rgba(double color)
{
	return (new_color((((uint64_t)color >> 16) & 0xFF) / 255.0, (((uint64_t)color >> 8) & 0xFF) / 255.0, (((uint64_t)color) & 0xFF) / 255.0));
}

t_tuple *cpv(double x, double y, double z, double p_v)
{
	t_tuple *a;

	a = ft_malloc(sizeof(t_tuple));
	if (!a)
		return (NULL);
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = p_v;
	return (a);
}

/*operation two tuples */
t_tuple *tpl_o(t_tuple a, t_tuple b , double	(*f)(double p1, double p2))
{
	return (cpv(f(a.x, b.x), f(a.y, b.y), f(a.z, b.z), f(a.w, b.w)));
}

/*get the opposite vector if the given is from a to b it will return the vector from b to a */
t_tuple *opp(t_tuple a)
{
	return (cpv(-a.x, -a.y, -a.z, 0));
}

/*we use scalar for dividing or multiplying a vector by a number called scalar*/
t_tuple *scalar(t_tuple a, double scalar)
{
	return (cpv(mul(a.x, scalar), mul(a.y, scalar), mul(a.z, scalar), a.w));
}

double magnitude(t_tuple a)
{
	return (sqrt((sq(a.x) + sq(a.y) + sq(a.z))));
}

/* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
t_tuple *Normalize(t_tuple a)
{
	double v;

	v = magnitude(a);
	if (!v)
		return (cpv(a.x, a.y, a.z, a.w));
	return (cpv(a.x/v, a.y/v, a.z/v,a.w));
}

/* creat a ray with origine and direction */
t_ray *ray(t_tuple origine, t_tuple direction)
{
	t_ray *ret;

	ret = ft_malloc (sizeof(t_ray));
	if (!ret)
		return (NULL);
	ret->o = origine;
	ret->d = direction;
	return (ret);
}

/*get the position of a point in a ray */
t_tuple *position(t_ray *ray, double distance)
{
	return (tpl_o(ray->o , *(scalar(ray->d, distance)), add));
}

/* translate  point */
t_tuple *transl(t_tuple *point, t_matrix *tr_mtx)
{
	return (tup_mat_mul(tr_mtx, point));
}

/* scall point */
t_tuple *scall(t_tuple *point, t_matrix *scal_mtx)
{
	return (tup_mat_mul(scal_mtx, point));
}

/* transform a ray */
t_ray *transform(t_ray *t, t_matrix *mat)
{
	return (ray(*tup_mat_mul(mat, &t->o), *Normalize(*tup_mat_mul(mat , &t->d))));
}

/* creat a new sphere object */
t_spher *spher(t_tuple *center, double raduis, int id, t_matrix *tr)
{
	t_spher *ret;

	ret = ft_malloc (sizeof(t_spher));
	if (!ret)
		return (NULL);
	ret->c = center;
	ret->r = raduis;
	ret->id = id;
	ret->transform = tr;
	ret->material = material();
	ret->inverse_m = inverse(ret->transform);
	ret->transpose_in = transpose(ret->inverse_m);
	return (ret);
}

/* get the element of the quadratiq equation */
static double *eq_inter(t_ray *ray1 , double arr[])
{
	arr[0] = Dot_p(ray1->d, ray1->d);
	arr[1] = 2.0 * (Dot_p(ray1->o, ray1->d));
	arr[2] = (Dot_p(ray1->o, ray1->o) - 1);
	arr[3] = sq(arr[1]) - (4.0 * (arr[0] * arr[2]));
	return (arr);
}

/* check intersection between a ray and a spher */
t_intersect	*intersect(t_ray *ray, t_spher *sph)
{
	t_intersect *inter;
	t_ray *ray1;
	double arr[4];

	ray1 = transform(ray, sph->inverse_m);
	eq_inter(ray1, arr);
	inter = new_intersect();
	if (!inter || arr[3] < EPSILON)
		return (NULL);

	double dn = (2 * (arr[0]));
	double sqr_dis = sqrt(arr[3]);
	inter->t[0] = (-arr[1] - sqr_dis) / dn;
	inter->t[1] = (-arr[1] + sqr_dis) / dn;
	inter->object.type = SPHER;
	inter->object.shape = *sph;
	inter->ray = ray1;
	inter->next = NULL;
	return (inter);
}

/* set the transformation matrix on sphere struct */
void	set_tranform(t_spher *sph, t_matrix *mat)
{
	sph->transform = mat;
	sph->inverse_m = inverse(mat);
	sph->transpose_in = transpose(sph->inverse_m);
}

t_light *light_source(t_tuple *position, t_color *color, double brightness)
{
	t_light *light;

	light = ft_malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = *position;
	light->brightness = brightness;
	light->color = *color;
	return (light);
}

/* compare two floating point number we use a constant  */
int isequal(double a, double b)
{
	return ((fabs(a-b) < EPSILON));
}
/* add two floating point number */
double	add(double a, double b)
{
	return (a + b);
}

/* subtract two floating point number */
double	sub(double a, double b)
{
	return (a - b);
}

/* multiply two floating point number */
double	mul(double a, double b)
{
	return (a * b);
}

/* divide two floating point number */
double	divi(double a, double b)
{
	return (a / b);
}

/* get squar of a number */
double	sq(double num)
{
	return(pow(num, 2));
}

/* if "a" and "b" are vector the dot product is "a"."b" return a number 
wec need it to ompare the direction of the two vectors */
/* if the two vectors are unit theire dot product is actually the cosine of the ongle between them */
double	Dot_p(t_tuple a, t_tuple b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/* cross product if "a" and "b" are vector the cross product is "a"^"b" return another vector
that is perpendicular to both of the original vectors. */
t_tuple *Cross_p(t_tuple a, t_tuple b)
{
	return (cpv(((a.y * b.z) - (a.z * b.y)), ((a.z * b.x) - (a.x * b.z)), ((a.x * b.y) - (a.y * b.x)), 0));
}

/* change from degrees to radians */
double radians(double degrees)
{
	return ((degrees / 180) * 3.14159265);
}

/* identity matrix multipliyng by any matrix it gives the same matrix */

t_matrix *i_mat(void)
{
	t_matrix *a;

	a = ft_malloc(sizeof(t_matrix));
	if (!a)
		return (NULL);
	a->matrix[0][0] = 1;
	a->matrix[1][1] = 1;
	a->matrix[2][2] = 1;
	a->matrix[3][3] = 1;
	return (a);
}

/* get the translation matrix we need to translate a point */

t_matrix *transl_mat(double x, double y, double z)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][3] = x;
	ret->matrix[1][3] = y;
	ret->matrix[2][3] = z;
	return (ret);
}

/* get the scalling matrix */
t_matrix *scal_mat(double x, double y, double z)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][0] = x;
	ret->matrix[1][1] = y;
	ret->matrix[2][2] = z;
	return (ret);
}

/* rotat a vector or a point to an axis x y or z */
t_matrix *rotat_matrix(double radians, char axis)
{
	t_matrix *ret;
	int r[2];

	r[0] = 0;
	r[1] = 0;
	ret = i_mat();
	if (axis == 'x' && ++(r[0]) && ++(r[0]) && ++(r[1]))
		;
	else if (axis == 'y' && ++(r[1]) && ++(r[1]))
		;
	else if (axis == 'z' && ++(r[1]))
		;
	ret->matrix[r[0]][r[0]] = cos(radians);
	ret->matrix[r[1]][r[1]] = ret->matrix[r[0]][r[0]];
	if (axis == 'z')
	{
		ret->matrix[r[1]][r[0]] = sin(radians);
		ret->matrix[r[0]][r[1]] = -(ret->matrix[r[1]][r[0]]);
	}
	else
	{
		ret->matrix[r[0]][r[1]] = sin(radians);
		ret->matrix[r[1]][r[0]] = -(ret->matrix[r[0]][r[1]]);
	}
	return (ret);
}

/* get the skewing (shearing matrix) */
t_matrix *skew_mat(double *arr)
{
	t_matrix *ret;

	ret = i_mat();
	ret->matrix[0][1] = arr[0];
	ret->matrix[0][2] = arr[1];
	ret->matrix[1][0] = arr[2];
	ret->matrix[1][2] = arr[3];
	ret->matrix[2][0] = arr[4];
	ret->matrix[2][1] = arr[5];
	return (ret);
}

/* checks if two matrix are equals*/

int equal_mat(t_matrix *a, t_matrix *b)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (!isequal(a->matrix[i][j], b->matrix[i][j]))
				return (0);
		}
	}
	return (1);
}

/*helper function that help multiplying two matrixs */
static double	get(t_matrix *a, t_matrix *b, int row, int col)
{
	double result;
	int i;

	result = 0;
	i = -1;
	while (++i < 4)
		result += (a->matrix[row][i] * b->matrix[i][col]);
	return (result);
}
/*multiplying two matrixs gives another matrix */
t_matrix	*mul_mat(t_matrix *a, t_matrix *b)
{
	int i;
	int j;
	t_matrix *ret;

	i = -1; 
	ret = ft_malloc (sizeof(t_matrix));
	if (!ret)
		return (NULL);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = get(a, b, i, j);
	}
	return (ret);
}

/* multipling a matrix by  tuple creat another tuple */

t_tuple *tup_mat_mul(t_matrix *mtx, t_tuple *tpl)
{
	return (cpv((mtx->matrix[0][0] * tpl->x) + (mtx->matrix[0][1] * tpl->y) + (mtx->matrix[0][2] * tpl->z) + (mtx->matrix[0][3] * tpl->w),\
	(mtx->matrix[1][0] * tpl->x) + (mtx->matrix[1][1] * tpl->y) + (mtx->matrix[1][2] * tpl->z) + (mtx->matrix[1][3] * tpl->w),\
	(mtx->matrix[2][0] * tpl->x) + (mtx->matrix[2][1] * tpl->y) + (mtx->matrix[2][2] * tpl->z) + (mtx->matrix[2][3] * tpl->w),\
	(mtx->matrix[3][0] * tpl->x) + (mtx->matrix[3][1] * tpl->y) + (mtx->matrix[3][2] * tpl->z) + (mtx->matrix[3][3] * tpl->w)));
}
/*transpose take a matrix and change its rows to collomns and its collomns to rows */

t_matrix *transpose(t_matrix *a)
{
	t_matrix *ret;
	int i;
	int j;

	i = -1;
	ret = ft_malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[j][i] = a->matrix[i][j];
	}
	return (ret);
}

/*getting the determinant of the 3*3 matrix u have the choice to work with the cols o rows
u will get the same  result  */
double det_3(t_3_3 *a)
{
	return ((cof_3(a, 0, 0) * a->matrix[0][0]) + \
		(cof_3(a, 0, 1) * a->matrix[0][1]) + \
		(cof_3(a, 0, 2) * a->matrix[0][2]));
}

double	cofactor(t_matrix *a, int row , int col)
{
	t_3_3 *sub = sub_m3(a, row, col);
	return ((det_3(sub)) * cof_sign(row, col));
}

double determinant(t_matrix *a)
{
	return ((cofactor(a, 0, 0) * a->matrix[0][0]) + \
		(cofactor(a, 0, 1) * a->matrix[0][1]) + \
		(cofactor(a, 0, 2) * a->matrix[0][2]) + \
		(cofactor(a, 0, 3) * a->matrix[0][3]));
}

/*checks the matrix inverbility is it return 0 mean thats not invertible */
double invertible(t_matrix *a)
{
	return (determinant(a));
}

/* get th inverse of a matrix */
t_matrix *inverse(t_matrix *a)
{
	t_matrix *ret;
	int i;
	int j;
	double det;

	if (!invertible(a))
		return (a);
	det = determinant(a);
	ret = ft_malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret->matrix[i][j] = (cofactor(a, i, j) / det);
	}
	return (transpose(ret));
}

/* submatrix 2*2 remove a collamn and a row from a 3*3 matrix */

t_2_2 *sub_m2(t_3_3 *a, int row, int col)
{
	t_2_2 *d;
	int i[4];

	d = (t_2_2 *)ft_malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	i[0] = 0;
	i[2] = 0;
	while ((i[0]) < 3 && (i[2]) < 2)
	{
		if (i[0] == row)
			++(i[0]);
		i[1] = 0;
		i[3] = 0;
		while ((i[1]) < 3 && (i[3]) < 2)
		{
			if (i[1] == col)
				++(i[1]);
			d->matrix[i[2]][i[3]] = a->matrix[i[0]][i[1]] ;
			i[1]++;
			i[3]++;
		}
		i[0]++;
		i[2]++;
	}
	return (d);
}

/* is the determinant of a 3*3 submatrix after removing a row and col */

double	ft_minor(t_3_3 *a, int row, int col)
{
	return (det_2(sub_m2(a, row, col)));
}

/* get the cofactor sign depending on the case the row and col removed share in the matrix */

double cof_sign(int r, int c)
{
	if ((!(r % 2) && (c % 2)) || ((r % 2) && (!(c % 2))))
		return (-1);
	return (1);
}

/* gettin the cofactor of the 3*3 matrix */

double cof_3(t_3_3 *a, int row , int col )
{
	return ((ft_minor(a, row , col) * cof_sign(row, col)));
}

/* get determinant of 2*2 matrix */

double det_2(t_2_2 *a)
{
	return(sub( mul(a->matrix[0][0], a->matrix[1][1]),\
		 mul(a->matrix[0][1], a->matrix[1][0])));
}

/* submatrix 3*3 remove a collamn and a row from a  4*4 matrix */

t_3_3 *sub_m3(t_matrix *a, int row, int col)
{
	t_3_3 *d;
	int i, j;

	d = (t_3_3 *)ft_malloc (sizeof(t_3_3));
	if (!d)
		return (NULL);
	i = 0;
	j = 0;
	while (i < 4)
	{
		if (i == row && row < 3)
			i++;
		if (i == row && row == 3)
			break;
		// get_sub(a->matrix[i], d->matrix,row ,  col);
		int p = 0;
		int s = 0;

		while (p < 4)
		{
			if (p == col && col < 3)
				p++;
			if (p == col && col == 3)
				break;
			d->matrix[j][s] = a->matrix[i][p];
			s++;
			p++;
		}
		i++;
		j++;
	}
	return (d);
}


t_tuple *reflect(t_tuple in, t_tuple normal)
{
	return (tpl_o(in, *(scalar(normal, mul(Dot_p(in, normal), 2))),  sub));
}

double get_closest(double *t)
{
	if (t[0] < EPSILON)
		return (t[1]);
	else if (t[1] < EPSILON)
		return (t[0]);
	return (fmin(t[0], t[1]));
}

t_material *material()
{
	t_material *mate = ft_malloc(sizeof(t_material));

	mate->color = *new_color(1.0,1.0,1.0);
	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	return (mate);
}

t_color *compute_ambiant(t_light *light, t_material *m)
{
	t_color *effective_color;
	effective_color = colors_operation(color_s_mul(&light->color, light->brightness), &m->color, mul);
	return (color_s_mul(effective_color, m->ambiant));
}

t_color *compute_diffuse(t_material *m, t_light *light, t_tuple *pos, t_tuple *normalv, t_tuple *lightv)
{
	double light_dot_normal;
	lightv = Normalize(*(tpl_o(light->position, *pos, sub)));
	light_dot_normal = Dot_p(*lightv,*normalv);
	if(light_dot_normal >= EPSILON)
		return (color_s_mul(colors_operation(&light->color, &m->color, mul), (m->diffuse * light_dot_normal)));
	return (new_color(0.0,0.0,0.0));
}

t_color *compute_specular(t_material *m, t_light *light, t_tuple *normalv, t_tuple *eyev,t_tuple *lightv)
{
	t_tuple *reflectv;
	double factor;
	double reflect_dot_eye;
	reflectv = reflect(*Normalize(*opp(*lightv)), *normalv);
	reflect_dot_eye = Dot_p(*reflectv, *(eyev));
	if (reflect_dot_eye > EPSILON){
		factor = pow(reflect_dot_eye, m->shininess);
		return (color_s_mul(&light->color, (m->specular * factor)));
	}
	return (new_color(0.0,0.0,0.0));
}

t_color *compute_lightning(t_material *m, t_light *light, t_tuple *pos,t_tuple *eyev, t_tuple *normalv)
{
	t_color *ambiant;
	t_color *diffuse;
	t_color *specular;
	t_tuple *lightv;
	lightv = Normalize(*(tpl_o(light->position, *pos, sub))); 
	specular = new_color(0.0,0.0,0.0);
	ambiant = compute_ambiant(light, m);
	diffuse = compute_diffuse(m, light, pos, normalv, lightv);
	specular = compute_specular(m, light, normalv, eyev, lightv);
	return (colors_operation(colors_operation(diffuse, ambiant, add), specular, add));
}
double hit(double *arr)
{
	if (arr[0] < EPSILON && arr[1] < EPSILON)
		return (0);
	return (1);
}

t_world *world()
{
	t_world *world;

	world = ft_malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	return (world);
}

static void add_to_list(t_intersect **head, t_intersect *new)
{
	t_intersect *tmp;

	if (!*head)
    {
        *head = new;
        return;
    }
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_intersect *world_intersection(t_world *world, t_ray *r)
{
	t_intersect *head;
	t_intersect *inter;
	int i;

	i = 0;
	inter = NULL;
	head = NULL;
	while (i < world->object_count)
	{

		if (world->object[i].type == SPHER)
			inter = intersect(r, &world->object[i].shape);
		else if (world->object[i].type == PLANE)
			inter = pl_intersect(r, &world->object[i].shape_pl);
		else if (world->object[i].type == CYLINDER)
			inter = cyl_intersect(r, &world->object[i].shape_cyl);
		if (inter)
			add_to_list(&head, inter);
		i++;
	}
	return (get_first_intersect(head, r));
}

t_intersect *get_first_intersect(t_intersect *list, t_ray *r)
{
    t_intersect *tmp = list;
    t_intersect *ret = new_intersect(); 

    ret->ray = r;
    ret->t[0] = HUGE_VAL;
    while (tmp) {
		if (hit(tmp->t))
		{
			tmp->t[0] = get_closest(tmp->t);
        	if (tmp->t[0] < ret->t[0]) 
			{
            	ret->t[0] = tmp->t[0];
            	ret->object = tmp->object;
			}
        }
        tmp = tmp->next;
    }
	if (ret->t[0] == HUGE_VAL)
		return (NULL);
    return ret;
}

t_color *shade_hit(t_world *w, t_comps *comp)
{
	t_material *m;

	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	if (comp->shadow)
		return (compute_ambiant(w->light, m));
	return (compute_lightning(m, w->light, comp->point, comp->eyev, comp->normalv));
}

t_comps	*prepare_computing(t_intersect *list, t_ray *r, t_world *w)
{
	t_comps *comp;
	(void)w;
	comp = new_comps();
	
	comp->t = list->t[0];
	comp->object = list->object;
	comp->point  = position(r, comp->t);
	comp->eyev = opp(r->d);
	if (comp->object.type == SPHER){
		comp->normalv = normal_at(&comp->object.shape, comp->point);
		if (Dot_p(*comp->normalv, *comp->eyev) < EPSILON)
		{
			comp->inside = true;
			comp->normalv = opp(*comp->normalv);
		}
		else
			comp->inside = false;
	}
	else if (comp->object.type == PLANE)
		comp->normalv = list->object.shape_pl.normalv;
	else if (comp->object.type == CYLINDER){
		comp->normalv = normal_at_cyl(&comp->object.shape_cyl, comp->point);
		if (Dot_p(*comp->normalv, *comp->eyev) <= 0.0)
			comp->normalv = opp(*comp->normalv);
	}
	t_tuple *shadow_ray = tpl_o(w->light->position, *comp->point, sub);
	double distance = magnitude(*shadow_ray);
	comp->shadow = false;
	t_ray *r1 = ray(*comp->point, *Normalize(*shadow_ray));
	t_intersect *inter = world_intersection(w, r1);
	if (inter && (distance - inter->t[0]) >= EPSILON)
		comp->shadow = true;
	return (comp);
}

t_color *color_at(t_world *w, t_ray *r)
{
	t_intersect *ret = world_intersection(w, r);
	if (!ret)
		return (NULL);
	return (shade_hit(w, prepare_computing(ret, r, w)));
}

t_matrix *view_transformation(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_matrix *ret;
	to->w = 0;
	t_tuple *forward = Normalize(*to);
	t_tuple *left = Cross_p(*forward, *Normalize(*up));
	t_tuple *true_up = Cross_p(*left, *forward);

	ret = i_mat();
	ret->matrix[0][0] = left->x;
	ret->matrix[0][1] = left->y;
	ret->matrix[0][2] = left->z;
	ret->matrix[1][0] = true_up->x;
	ret->matrix[1][1] = true_up->y;
	ret->matrix[1][2] = true_up->z;
	ret->matrix[2][0] = -forward->x;
	ret->matrix[2][1] = -forward->y;
	ret->matrix[2][2] = -forward->z;
	return (mul_mat(ret, transl_mat(-from->x, -from->y, -from->z)));
}

t_ray *ray_for_pixel(t_camera *cam, double x, double y)
{
	double x_offset = (x + 0.5) * cam->pixel_size;
	double y_offset = (y + 0.5) * cam->pixel_size;
	double world_x = cam->half_width - x_offset;
	double world_y = cam->half_hight - y_offset;
	t_tuple *pixel = tup_mat_mul(cam->transform_inverse , cpv(world_x,world_y,-1,1));
	t_tuple *direction = Normalize(*tpl_o(*pixel, *cam->origine, sub));
	return (ray(*cam->origine, *direction));
}

void render(t_rt *rt)
{
	double x = 0;
	double y = 0;
	t_ray *r;
	t_color *col;
	rt->cam->mlx =  mlx_init(rt->cam->horizontal_size, rt->cam->vertical_size, "test", 1);
	mlx_image_t *image = mlx_new_image(rt->cam->mlx ,rt->cam->horizontal_size, rt->cam->vertical_size);
	rt->cam->origine = cpv(rt->cam->transform_inverse->matrix[0][3],rt->cam->transform_inverse->matrix[1][3],rt->cam->transform_inverse->matrix[2][3],1);
	printf("%f %f %f \n", rt->cam->origine->x, rt->cam->origine->y, rt->cam->origine->z);
	while (y < rt->cam->vertical_size)
	{
		x = 0;
		while (x < rt->cam->horizontal_size)
		{
			r = ray_for_pixel(rt->cam, x, y);
			col = color_at(rt->world, r);
			if(col)
				mlx_put_pixel(image, x, y, get_col(col));
			else
				mlx_put_pixel(image, x, y, BLACK);
			x++;
		}
		y++;
	}
	mlx_image_to_window(rt->cam->mlx, image, 0, 0);
	mlx_loop(rt->cam->mlx);
}

t_plane *plane(int id, t_matrix *tr)
{
	t_plane *pl = ft_malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->id = id;
	pl->material = material();
	pl->transform = tr;
	pl->inverse_m = inverse(tr);
	pl->transpose_inverse = transpose(pl->inverse_m);
	pl->normalv = cpv(0,1,0,0);
	return (pl);
}

t_intersect *pl_intersect(t_ray *r1, t_plane *pl)
{
	t_intersect *ret;
	t_ray *r_ob_space;

	r_ob_space = transform(r1, pl->inverse_m);
	ret = new_intersect();
	if (fabs(r_ob_space->d.y) <= EPSILON)
		return (NULL);
	ret->t[0] = -(r_ob_space->o.y) / r_ob_space->d.y;
	if (ret->t[0] < EPSILON)
		return (NULL);
	ret->object.shape_pl = *pl;
	ret->object.type = PLANE;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}

t_cylinder *cylinder(double *trunc, int id, t_matrix *tr, bool capped)
{
	t_cylinder *cyl;

	cyl = ft_malloc(sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->id = id;
	cyl->capped = capped;
	cyl->truncated = false;
	if (trunc){
		cyl->truncated = true;
		cyl->min = trunc[0];
		cyl->max = trunc[1];
	}
	cyl->material = material();
	cyl->transform  = tr;
	cyl->inverse_m = inverse(tr);
	cyl->transpose_inverse = transpose(cyl->inverse_m);
	return (cyl);
}

void swap(double *a, double *b)
{
	double tmp = *b;
	*b = *a;
	*a = tmp;
}

t_intersect *cyl_intersect(t_ray *r, t_cylinder *cyl)
{
	t_ray *r_ob_space;
	t_intersect *ret;
	double arr[4];
	double in_bounds[2];

	ret = new_intersect();
	r_ob_space = transform(r, cyl->inverse_m);
	arr[0] = sq(r_ob_space->d.x) + sq(r_ob_space->d.z);
	if (arr[0] > EPSILON){
		arr[1] = 2.0 * ((r_ob_space->o.x * r_ob_space->d.x) + (r_ob_space->o.z * r_ob_space->d.z));
		arr[2] = sq(r_ob_space->o.x) + sq(r_ob_space->o.z) - 1;
		arr[3] = sq(arr[1]) - (4.0 * arr[0] * arr[2]);
		if (arr[3] < 0.0)
			return (NULL);
		ret->t[0] = (-arr[1] - sqrt(arr[3])) / (2.0 * arr[0]);
		ret->t[1] = (-arr[1] + sqrt(arr[3])) / (2.0 * arr[0]);
		if(ret->t[0] > ret->t[1])
			swap(&ret->t[0], &ret->t[1]);
		in_bounds[0] = r_ob_space->o.y + ret->t[0] * r_ob_space->d.y;
		if(!(cyl->min < in_bounds[0] && in_bounds[0] < cyl->max))
			ret->t[0] = -INFINITY;
		in_bounds[1] = r_ob_space->o.y + ret->t[1] * r_ob_space->d.y;
		if(!(cyl->min < in_bounds[1] && in_bounds[1] < cyl->max))
			ret->t[1] = -INFINITY;
	}
	if (cyl->capped)
		intersect_caps_cyl(cyl, r_ob_space, &ret->t[0], &ret->t[1]);
	ret->object.shape_cyl = *cyl;
	ret->object.type = CYLINDER;
	ret->ray = r_ob_space;
	ret->next = NULL;
	return (ret);
}

int	check_cap(t_ray *r , double t)
{
	double x = r->o.x + t * r->d.x;
	double z = r->o.z + t * r->d.z;

	return (((sq(x)+sq(z)) <= 1));
}

void intersect_caps_cyl(t_cylinder *cyl, t_ray *r, double *t1, double *t2) {
    if (!cyl->capped || fabs(r->d.y) < EPSILON) // Only check caps if cylinder is capped
        return;
    double t;
    // Check bottom cap
    t = (cyl->min - r->o.y) / r->d.y;
    if (check_cap(r, t)) {
        if (*t1 == -INFINITY)
            *t1 = t;
        else if (*t2 == -INFINITY)
            *t2 = t;
    }
    // Check top cap
    t = (cyl->max - r->o.y) / r->d.y;
    if (check_cap(r, t)) {
        if (*t1 == -INFINITY)
            *t1 = t;
        else if (*t2 == -INFINITY)
            *t2 = t;
    }
}


t_tuple *normal_at_cyl(t_cylinder *cyl, t_tuple *p)
{
	double dist = sq(p->x) + sq(p->z);
	if (dist < 1.0 && p->y >= (cyl->max - EPSILON))
		return (cpv(0,1,0,0));
	else if (dist < 1.0 && p->y <= (cyl->min + EPSILON))
		return (cpv(0,-1,0,0));
	return (Normalize(*cpv(p->x, 0, p->z, 0)));
}

/* get the normal vector on a point on the spher*/
t_tuple *normal_at(t_spher *sph, t_tuple *point)
{
	t_tuple *object_p;
	t_tuple *world_normal;
	
	object_p = tup_mat_mul(sph->inverse_m, point);
	object_p->w = 0;
	world_normal = tup_mat_mul(sph->transpose_in, object_p);
	world_normal->w = 0;
	return (Normalize(*world_normal));
}