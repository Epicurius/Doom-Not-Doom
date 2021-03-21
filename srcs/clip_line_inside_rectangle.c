
#include "doom.h"

enum
{
	CS_TOP = 0x1,
	CS_BOTTOM = 0x2,
	CS_RIGHT = 0x4,
	CS_LEFT = 0x8,
};

unsigned int	compute_outcode(int x, int y, t_i2 min, t_i2 max)
{
	unsigned int i = 0;

	if (y > max.y)
		i |= CS_TOP;
	else if (y < min.y)
		i |= CS_BOTTOM;
	if (x > max.x)
		i |= CS_RIGHT;
	else if (x < min.x)
		i |= CS_LEFT;
	return (i);
}

//	Cohen Sutherland clipping line in rectangle algorithm
int	cohen_sutherland(t_i2 *v1, t_i2 *v2, t_i2 min, t_i2 max)
{
	double x;
	double y;
	unsigned int outcode_ex;
	unsigned int outcode_v1;
	unsigned int outcode_v2;

	outcode_v1 = compute_outcode(v1->x, v1->y, min, max);
	outcode_v2 = compute_outcode(v2->x, v2->y, min, max);
	// Both v inside rectangle.
	if (outcode_v1 & outcode_v2)
		return (0);
	while (1)
	{
		// Both v moved inside rectangle.
		if (outcode_v1 == 0 && outcode_v2 == 0)
			return (1);
		else
		{
			outcode_ex = outcode_v1 ? outcode_v1 : outcode_v2;
			if (outcode_ex & CS_TOP)
			{
				x = v1->x + (v2->x - v1->x) * (max.y - v1->y) / (v2->y - v1->y);
				y = max.y;
			}
			else if (outcode_ex & CS_BOTTOM)
			{
				x = v1->x + (v2->x - v1->x) * (min.y - v1->y) / (v2->y - v1->y);
				y = min.y;
            		}
			else if (outcode_ex & CS_RIGHT)
			{
				y = v1->y + (v2->y - v1->y) * (max.x - v1->x) / (v2->x - v1->x);
				x = max.x;
			}
			else
			{
				y = v1->y + (v2->y - v1->y) * (min.x - v1->x) / (v2->x - v1->x);
				x = min.x;
			} 
			if (outcode_ex == outcode_v1)
			{
				v1->x = x;
				v1->y = y;
				outcode_v1 = compute_outcode(v1->x, v1->y, min, max);
			}
			else
			{
				v2->x = x;
				v2->y = y;
				outcode_v2 = compute_outcode(v2->x, v2->y, min, max);
			}
		}
	}
}

/*
void line_clamp_in_rectangle()
{
	t_i2 v1 = {4, -1};
	t_i2 v2 = {8, 11};
	t_i2 min = {0,0};
	t_i2 max = {10,10};
        cohen_sutherland(&v1, &v2, min, max);
	printf("%d %d | %d %d\n", v1.x, v1.y, v2.x, v2.y);
}*/
