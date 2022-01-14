/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/06/19 17:37:16 nneronin
 * Updated: 2021/09/21 18:16:39 nneronin
 */

#include "libm.h"

/*
 *	Length of a vector 2D
 */
float	vector_magnitude_v2(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

/*
 *	Length of a vector 3D
 */
float	vector_magnitude_v3(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Space Diagonal
 */
float	pythagoras(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/*
 *	Space Diagonal/Pythagoras
 */
float	space_diagonal(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
 *	Get normal
 */
float	normalize_v3(t_v3 *vec)
{
	float	length;

	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length)
	{
		vec->x /= length;
		vec->y /= length;
		vec->z /= length;
	}
	return (length);
}
