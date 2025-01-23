#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define train_count (sizeof(train) / sizeof(train[0]))
//x = entree, y = resultat w est le model mathematique
float	train[][2] = {
	{0, 0},
	{1, 2},
	{2, 4},
	{3, 6},
	{4, 8},
};

float	rand_float( void )
{
	return (( float )rand() / (float)RAND_MAX );//un nombre flottant entre 0 et 1;
};

float	cost( float w )
{
	float	result = 0.0f;
	for ( size_t i = 0; i < train_count; i++ ) {
		float	x = train[i][0];
		float	y = x * w;
		float	d = y - train[i][1];
		result += d*d;
		printf("expected %f, results %f\n", train[i][1], y);
	};
	result /= train_count;

	return ( result );
};

int	main( void )
{
	srand( 69 );
	float	w = rand_float() * 10.0f;
	printf("average error : %f\n",  cost(w));
	return ( 0 );
};
