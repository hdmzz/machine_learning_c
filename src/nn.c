#define NN_IMPLEMENTATION
#include "nn.h"

int	main(void)
{
	srand(time(0));
    Matrix a = mat_alloc(2, 2);
    mat_rand(a, 10, 20);

    mat_print(a);
    
    printf("\n");

    Matrix b = mat_alloc(3, 2);
    mat_rand(b, 5, 10);

    mat_print(b);

    printf("\n");

    Matrix dest = mat_alloc(a.rows, b.cols);
    mat_dot(dest, a, b);

    printf("\n");

    mat_print(dest);

	return (0);
}
