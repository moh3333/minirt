/* r(t)=O+t⋅d
O is the ray's origin (starting point),
d is the direction of the ray (a normalized vector),
t is a scalar (real number) that scales the direction to find points along the ray.
*/

/* (p−C)⋅(p−C)=r 
C is the center of the sphere,
r is the radius,
p is any point on the surface of the sphere.

*/

/* (r(t)−C)⋅(r(t)−C)=r 
(O+t⋅d−C)⋅(O+t⋅d−C)=r 
(O−C)⋅(O−C)+2t(O−C)⋅d+sq(t) (d⋅d)=sq(r)
A sq(t)+Bt+C=0
A=d⋅d,
B=2(O−C)⋅d,
C=(O−C)⋅(O−C)−r 
*/

/*  quadratic equation */
/*   		-b (+ or -) sqrt(sq(b) - 4 AC)
   t  = 	_________________________________
						2A
*/

/*	discriminant (sq(b) - 4AC) tells us how many intersections there are:
 if greater than 0 there are two point for the intersection
 if equal than 0 there is one point for the intersection
 if smaller than 0 there are no point for the intersection
*/

/* If t is negative, the intersection point is behind the ray's origin
(so you might discard those solutions depending on the context,
as rays are usually considered to move forward)
*/