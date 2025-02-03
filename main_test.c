#include <libc.h>
#include <math.h>
#include "minirt.h"


// t_matrix *get_rotat_matrice(t_tuple *normal)
// {
// 	double beta = radians(Dot_p(r, *normal));
// 	t_matrix *cr = i_mat();
	
// 	t_matrix *tr  =  i_mat()
	
// }
// t_tuple *cpv(double x, double y, double z, double p_v)
// {
// 	t_tuple *a;

// 	a = malloc(sizeof(t_tuple));
// 	if (!a)
// 		return (NULL);
// 	a->x = x;
// 	a->y = y;
// 	a->z = z;
// 	a->w = p_v;
// 	return (a);
// }
// double	sq(double num)
// {
// 	return(pow(num, 2));
// }
// double magnitude(t_tuple a)
// {
// 	return (sqrt((sq(a.x) + sq(a.y) + sq(a.z))));
// }

// /* normalization its nedded when we have an arbitry vector mean a vector that u have the choise where it will goes */
// t_tuple *Normalize(t_tuple a)
// {
// 	double v;

// 	v = magnitude(a);
// 	if (!v)
// 		return (cpv(a.x, a.y, a.z, a.w));
// 	return (cpv(a.x/v, a.y/v, a.z/v,a.w));
// }
// t_tuple *Cross_p(t_tuple a, t_tuple b)
// {
// 	return (cpv(((a.y * b.z) - (a.z * b.y)), ((a.z * b.x) - (a.x * b.z)), ((a.x * b.y) - (a.y * b.x)), 0));
// }
// double	Dot_p(t_tuple a, t_tuple b)
// {
// 	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
// }
// double radians(double degrees)
// {
// 	return ((degrees / 180.0) * 3.14159265);
// }
// int main()
// {
// 	t_tuple *normal = cpv(0.8165,0.4082,0.4082, 0.0);
// 	t_tuple r = {0.0,1.0,0.0,0.0};
// 	t_tuple *axe = Normalize(*Cross_p(r, *normal));
// 	double axec = Dot_p(r, *normal);
// 	printf("%f,\n", axec);
// 	double rd = acos(axec);
// 	printf("%f,\n", rd);
// 	printf("%f, %f, %f \n", axe->x,axe->y,axe->z);
// }

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

char	**split_line(char const *s, char c, char c1)
{
	int		i[4];
	char	**str;

	i[1] = 0;
	i[0] = count_double_array_size(s, c, c1);
			
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
int main()
{
	char *h = "kebqdi,befiu   ,bouc, eqiphicq,c    cqjedeq   eqou ";
	char **d = split_line(h, ',', ' ');
	int i = 0;
	while (d[i]){
		printf("%s\n", d[i]);
		i++;
	}	

}