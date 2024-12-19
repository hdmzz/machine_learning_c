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

float	rand_float( void ) {
	return (( float )rand() / (float)RAND_MAX );//un nombre flottant entre 0 et 1;
};

int	main( void )
{
	srand( 69 ); // Initialisation du générateur de nombres aléatoires
	float	w = rand_float() * 10.0f;
//on va mutiplier le x jusquq ce qu'on trouve e bon resultat vec le w
	for ( size_t i = 0; i < train_count; i++ ) {
		float	x = train[i][0];
		float	y  = x * w;
		printf("expected %f, results %f\n", train[i][1], y);
	};
	return ( 0 );
}
