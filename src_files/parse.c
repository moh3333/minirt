/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:15:40 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/03 20:21:55 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*___________________________________________ split lines ______________________________________________________*/


int all_spaces(char *s)
{
	int i = 0;
	while (s[i]){
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}


static int count_double_array_size(const char *s, char c, char c1)
{
    int i = 0;
    int count = 0;

    while (s[i] != '\0') 
    {
        while (s[i] == c || s[i] == c1) 
            i++;
        if (s[i] != '\0' && s[i] != c && s[i] != c1) 
            count++;
        while (s[i] != '\0' && s[i] != c && s[i] != c1) 

            i++;
    }
    return count;
}


static int	count_single_array_size(const char *s, char c, char c1)
{
	int	j;

	j = 0;
	while (s[j] != c && s[j] != c1 && s[j] != '\0')
		j++;
	return (j);
}

char	**split_line(char *s, char c, char c1)
{
	int		i[4];
	char	**str;

	i[1] = 0;
	i[0] = count_double_array_size(s, c, c1);
	if (!s || all_spaces(s))
		return (NULL);	
	str = (char **) malloc ((i[0] + 1) * sizeof (char *));
	if (str == NULL)
		return (NULL);
	while (i[1] < i[0])
	{
		i[3] = -1;
		while (*s == c || *s == c1)
			s++;
		i[2] = count_single_array_size(s, c, c1);
		str[i[1]] = malloc ((i[2] + 1) * sizeof(char));
		if (!str[i[1]])
			return (NULL);
		while (++(i[3]) < i[2])
			str[i[1]][i[3]] = s[i[3]];
		str[i[1]][i[3]] = 0;
		s = s + i[2];
		(i[1])++;
	}
	str[i[1]] = NULL;
	return (str);
}

/*_____________________________________________get_next_lines____________________________________________________*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*s++ != 0)
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_copy(str, s, 0);
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ret;
	int		i;

	str = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ret = str;
	str = ft_copy(str, s1, 0);
	str = ft_copy(str, s2, ft_strlen(s1));
	str[i] = '\0';
	return (ret);
}

int	check_for_nl(char	**buff)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *buff;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_get_buff(int fd, char *buffer)
{
	char	*ret;
	int		i;

	i = 1;
	while (i > 0)
	{
		ret = malloc (((size_t)10 + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		i = read (fd, ret, 10);
		if (i == -1)
			return (NULL);
		if (i == 0)
			return (buffer);
		ret[i] = '\0';
		buffer = ft_strjoin(buffer, ret);
		if (!buffer)
			return (NULL);
		if (check_for_nl(&ret) == 1)
			break ;
	}
	return (buffer);
}

static int	get_i(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if (tmp[i] == '\n')
		i++;
	return (i);
}

static char	*get_line_(char *buffer)
{
	char	*ret;
	int		i;

	i = 0;
	i = get_i(buffer);
	ret = malloc ((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		ret[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		ret[i] = ' ';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || read (fd, buffer, 0) < 0)
		return (buffer = NULL, NULL);
	buffer = ft_get_buff(fd, buffer);
	if (!buffer || buffer [0] == 0)
		return (NULL);
	line = get_line_(buffer);
	if (!line || line [0] == 0)
		return (NULL);
	buffer = ft_strdup(buffer + ft_strlen(line));
	if (all_spaces(line))
		return (get_next_line(fd));
	return (line);
}

/*_____________________________________________ utils ____________________________________________________*/

bool ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

char	*ft_copy(char *s1, char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[j] != '\0')
		s1[i++] = s2[j++];
	return (s1);
}

/*________________________________________check fi valid float  ____________________________________________________*/

int  is_float(char *s)
{
	int i = 0;
	int floating_point;

	floating_point = 0;
	while (*s == 9 || *s == 10 || *s == 11 || *s == 12 || *s == 13 || *s == 32)
		s++;
	if(*s == 45 || *s == 43)
		i++;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i]){
		if (s[i] == '.' && !floating_point && i++)
			floating_point++;
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

/*________________________________________from string to double ____________________________________________________*/

double char_to_double(char *s)
{
	double result;
	double sign;
	int i;
	double check_floating_point;

	result = 0.0;
	sign = 1.0;
	i = 0;
	check_floating_point = 0;
	while (*s == 9 || *s == 10 || *s == 11 || *s == 12 || *s == 13 || *s == 32)
		s++;
	if(*s == 45 || *s == 43)
		if(*s++ == 45)
			sign *= -1.0;
	while ((*s >= '0' && *s <= '9') || (*s == '.' && !check_floating_point)){
		if(*s == '.' && s++)
			check_floating_point = 1;
		result = (result * 10.0) + (*s - 48);
		if (check_floating_point)
			i++;
		s++;
	}
	return ((result * sign / pow(10.0, (double)(i))));
}

/*________________________________________ print_errors  ____________________________________________________*/

void print_error(char *error)
{
	int i;

	i = 0;
	write (2, "Error\n", sizeof("Error\n"));
	while(error[i])
		write(2, &error[i++], 1);
	write (2, "\n", 1);
}

/*________________________________________ check if rt file  ____________________________________________________*/

bool check_extension(char *file_name)
{
	int i;

	i = 0;
	if (ft_strlen(file_name) < 4)
		return (print_error(VALID_NAME), false);
	while (file_name[i++]);
	if((file_name[i--] == 't' && file_name[i--] == 'r' && file_name[i] == '.'))
		return (print_error(RT_FILE_EXTENSION), false);
	return (true);
}

/*________________________________________ read all lines in file  ____________________________________________________*/

t_line *get_rt_lines(int fd)
{
	int i;
	t_line *l;

	i = 0;
	l = ft_malloc(sizeof(t_line));
	l->line[i] = get_next_line(fd);;
	while (l->line[i] && ++i)
		l->line[i] = get_next_line(fd);
	l->count = i;
	return (l);
}

/*________________________________________ parse and read the file   ____________________________________________________*/

t_line	*parse_file(char *file_name)
{
	int fd;
	t_line *l;

	if (!check_extension(file_name))
		return (print_error(RT_FILE_EXTENSION), NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILS), NULL);
	l = get_rt_lines(fd);
	close(fd);
	return (l);
}

int ft_strstrlen(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

/*________________________________________ from string to vector   ____________________________________________________*/

t_tuple *char_to_vec(char *cam_line, int type)
{
	char **cord;
	double arr[3];
	int i = 0;

	cord = split_line(cam_line, ',', ',');
	if (ft_strstrlen(cord) != 3)
		return (print_error(INVALID_CORD), NULL);
	while (cord && cord[i]){
		if (is_float(cord[i]))
			arr[i] = char_to_double(cord[i]);
		i++;
	}
	return (cpv(arr[0], arr[1], arr[2], type));
}

/*________________________________________ init the camera   ____________________________________________________*/

void init_camera(char **line, int exist, t_rt *rt)
{
	double fov;

	if (exist)
		return (print_error(DUPLICAT_CAM));
	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_CAM));
	if(!is_float(line[3]))
		return (print_error(INVALID_FOV));
	fov = char_to_double(line[3]);
	if (!(fov >= 0.0 && fov <= 180.0))
		return (print_error(INVALID_FOV));
	rt->cam = new_camera(1600,900, radians(fov), view_transformation(char_to_vec(line[1], 1), char_to_vec(line[2], 1), cpv(0,1,0,0)));
	rt->cam->origine = char_to_vec(line[1], 1);
}

/*________________________________________ from string to color ____________________________________________________*/

t_color *char_to_color(char *s)
{
	char **col;
	double arr[3];
	int i = 0;

	col = split_line(s, ',', ',');
	if (ft_strstrlen(col) != 3)
		return (print_error(INVALID_CORD), NULL);
	while (col && col[i]){
		if (is_float(col[i]))
			arr[i] = char_to_double(col[i]);
		i++;
	}
	return(new_color(arr[0]/255.0, arr[1]/255.0, arr[2]/255.0));
}

/*________________________________________ init ambiant color ____________________________________________________*/

void init_ambiant(char **line,int exist,t_rt *rt)
{
	double amb_ratio;
	t_color *ambiant;
	if (exist)
		return (print_error(DUPLICAT_AMB));
	if(!is_float(line[1]))
		return (print_error(INVALID_AMB_R));
	amb_ratio = char_to_double(line[1]);
	if (!(amb_ratio >= 0.0 && amb_ratio <= 1.0))
		return (print_error(INVALID_AMB_R));
	ambiant = char_to_color(line[2]);
	rt->world->ambiant_color = color_s_mul(ambiant, amb_ratio);
}

/*________________________________________ init light  ____________________________________________________*/

void init_light(char **line, int exist ,t_rt *rt)
{
	double light_ratio;
	t_color *light_col;
	t_tuple *pos;

	if (exist)
		return (print_error(DUPLICAT_LIGHT));
	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_LIGHT));
	if(!is_float(line[2]))
		return (print_error(INVALID_AMB_R));
	pos = char_to_vec(line[1], 1);
	light_ratio = char_to_double(line[2]);
	if (!(light_ratio >= 0.0 && light_ratio <= 1.0))
		return (print_error(INVALID_AMB_R));
	light_col = char_to_color(line[3]);
	rt->world->light = light_source(pos , light_col, light_ratio);
}

/*________________________________________ init sphere  ____________________________________________________*/

void init_spher(char **line, t_rt *rt, int id)
{
	t_spher *s;
	t_tuple *crd;
	double raduis;
	t_matrix *tr;
	t_color *col;

	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_OBJ));
	if (!is_float(line[2]))
		return (print_error(INVALID_SPHERE_RD));
	raduis = char_to_double(line[2]) / 2.0;
	crd = char_to_vec(line[1], 1);
	col = char_to_color(line[3]);
	rt->world->object[rt->world->object_count].type = SPHER;
	tr = mul_mat(transl_mat(crd->x, crd->y, crd->z), scal_mat(raduis, raduis, raduis));
	rt->world->object[rt->world->object_count].shape = *spher(cpv(0,0,0,1), 1, id, tr);
	rt->world->object[rt->world->object_count].shape.material->color = *char_to_color(line[3]);
	rt->world->object_count++;
}

/*________________________________________ get the rotation matrice of plane   ____________________________________________________*/

t_matrix *get_rotat_matrice(t_tuple *normal)
{
	t_tuple r = {0.0,1.0,0.0,0.0};
	t_tuple *axe = Normalize(*Cross_p(r, *normal));
	double beta = acos(Dot_p(r, *normal));
	t_matrix *cr = i_mat();
	cr->matrix[0][1] = (-axe->z);
	cr->matrix[1][0] = axe->z;
	cr->matrix[1][2] = -axe->x;
	cr->matrix[2][1] = axe->x;
	cr->matrix[0][0] = 0;
	cr->matrix[1][1] = 0;
	cr->matrix[2][2] = 0;
	cr->matrix[3][3] = 0;
	t_matrix *tr  = mul_mat(cr, cr);
	cr->matrix[0][1] = sin(beta) * (-axe->z);
	cr->matrix[1][0] = sin(beta) * axe->z;
	cr->matrix[1][2] = sin(beta) * -axe->x;
	cr->matrix[2][1] = sin(beta) * axe->x;
	int i = 0;
	int j = 0;
	while (i < 4){
		j  = 0;
		while (j < 4){
			tr->matrix[i][j] = (1- cos(beta)) * tr->matrix[i][j];
			j++;
		}
		i++;
	}
	t_matrix *final = i_mat();
	i = 0;
	j = 0;
	while (i < 4){
		j = 0;
		while (j < 4){
			final->matrix[i][j] = final->matrix[i][j] + tr->matrix[i][j] + cr->matrix[i][j];
			j++;
		}
		i++;
	}
	return (final);
}

/*________________________________________ inti the  plane   ____________________________________________________*/

void	init_plane(char **line, t_rt *rt, int id)
{
	t_color *col;
	t_tuple *normal;
	t_tuple *point;
	t_matrix *tr  = i_mat();

	if (ft_strstrlen(line) != 4)
		return (print_error(BAD_INFORM_OBJ));
	col = char_to_color(line[3]);
	normal = char_to_vec(line[2], 0);
	point = char_to_vec(line[1], 1);
	if (!(normal->x >= -1.0 && normal->x <= 1.0) ||!(normal->y >= -1.0 && normal->y <= 1.0) || !(normal->z >= -1.0 && normal->z <= 1.0) || magnitude(*normal) != 1)
		return (print_error(INVALID_PL_NORMAL));
	rt->world->object[rt->world->object_count].type = PLANE;
	t_matrix *rot = get_rotat_matrice(normal);
	rt->world->object[rt->world->object_count].shape_pl = *plane(id, mul_mat(transl_mat(point->x, point->y, point->z), get_rotat_matrice(normal)));
	rt->world->object_count++;
}

// init_cylinder(char **line, t_rt *rt, int id)
// {

// }

/*________________________________________ inti objects in scean    ____________________________________________________*/

void init_objects(char **line, t_rt *rt, int num_obj)
{
	static int arr[3];

	if (ft_strcmp("sp", line[0])){
		init_spher(line, rt, arr[0]);
		(arr[0])++;
	}
	else if (ft_strcmp("pl", line[0])){
		init_plane(line, rt, arr[1]);
		(arr[1])++;
	}
	// else if (ft_strcmp("cy", line[0])){
	// 	init_cylinder(line, rt, arr[2]);
	// 	(arr[2])++;
	// }
}

/*________________________________________ inti global strcuct    ____________________________________________________*/

void	init_struct(char **line, t_rt *rt)
{
	static int	check_identifier[3];
	static int num_obj;
	int i = 0;

	check_identifier[0] = 0;
	check_identifier[1] = 0;
	check_identifier[2] = 0;
	if (ft_strcmp(line[0], "C")){
			init_camera(line, check_identifier[0], rt);
		(check_identifier[0])++;
	}
	else if (ft_strcmp(line[0], "A")){
		init_ambiant(line, check_identifier[1], rt);
		(check_identifier[1])++;
	}
	else if (ft_strcmp(line[0], "L")){
		init_light(line, check_identifier[2], rt);
		(check_identifier[2])++;
	}
	else{
		init_objects(line, rt, num_obj);
	}
}



void parse_init_structs(t_line *l, t_rt *rt)
{
	int i;
	char **line;
	
	i = 0;
	while(i < l->count)
	{
		line = split_line(l->line[i], 32, 9);
		if (line && line[i] && line[i][0])
			init_struct(line , rt);
		i++;
	}
}

int main(int ac, char **av)
{
	t_line l;
	static t_rt rt;
	rt.world = world();
	int i = 0;
	if(ac == 2){
		l = *parse_file(av[1]);
		parse_init_structs(&l, &rt);
		render(&rt);
	}
}