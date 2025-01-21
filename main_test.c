#include "minirt.h"

int main()
{
	// t_matrix *d = scal_mat(10,0.01,10);
	// t_matrix *t = transl_mat(0,0,5);
	t_matrix *rx = rotat_matrix((M_PI/2), 'x');
	// t_matrix *ry = rotat_matrix(-(M_PI/4), 'y');
	t_matrix *s = scal_mat(10,0.01,10);
	t_matrix *d = mul_mat(rx, s);
	// d = mul_mat(rotat_matrix((M_PI/2), 'x'), d);
	// d = mul_mat(rotat_matrix(-(M_PI/4), 'y'), d);
	// d = mul_mat(transl_mat(0,0,5), d);
	// t_matrix *d = mul_mat(scal_mat(10,0.01,10),mul_mat(rotat_matrix(-(M_PI/4), 'y'), mul_mat(rotat_matrix((M_PI/2), 'x'), transl_mat(0,0,5))));
	int i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.5f  |", d->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


/*1.00000  |0.00000  |0.00000  |0.00000  |
0.00000  |0.00000  |-1.00000  |0.00000  |
0.00000  |1.00000  |0.00000  |0.00000  |
0.00000  |0.00000  |0.00000  |1.00000  |*/

/*10.00000  |0.00000  |0.00000  |0.00000  |
0.00000  |0.01000  |0.00000  |0.00000  |
0.00000  |0.00000  |10.00000  |0.00000  |
0.00000  |0.00000  |0.00000  |1.00000  |*/



/*	10  | 0 | 0| 0
	0 | 0 |
*/





/*10.00000  |0.00000  |0.00000  |0.00000  |
0.00000  |0.00000  |-10.00000  |0.00000  |
0.00000  |0.01000  |0.00000  |0.00000  |
0.00000  |0.00000  |0.00000  |1.00000  |*/