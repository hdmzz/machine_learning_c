#define NN_IMPLEMENTATION
#include "nn.h"

int	main(void)
{
	srand(time(0));
    Matrix w1 = mat_alloc(2, 2);
    Matrix b1 = mat_alloc(1, 2);
    Matrix w2 = mat_alloc(2, 2);
    Matrix b2 = mat_alloc(1, 1);

    mat_rand(w1, 0, 1);
    mat_rand(b1, 0, 1);
    mat_rand(w2, 0, 1);
    mat_rand(b2, 0, 1);

    MAT_PRINT(w1);
    MAT_PRINT(b1);
    MAT_PRINT(w2);
    MAT_PRINT(b2);

	return (0);
}
