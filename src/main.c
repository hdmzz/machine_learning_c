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
		result += d * d;
	};
	result /= train_count;

	return ( result );
};
//prochaien etape peut etre faire un algoritme qui trouve la derivative d la fonction cost pour aller dans le sens inverse et se rapprocher de 0
//nerd shit
// matrice et derivative en meme temps voila le proleme
//questce qune dderivative
int	main( void )
{
	srand( 69 );
	float	w = rand_float() * 10.0f;
	float	eps = 1e-3;
	//on va trouve la finite difference, une aproximation de la derivee, qu'il faudra soustraire au w pourquoi? pour aller dans le sens inverse
	float	learing_rate = 1e-3;

	for ( size_t i = 0; i < 2000; i++ ) {
		//approximation de la dérivée de la fonction cost 
		float	dcost = ( cost( w + eps ) - cost( w )) / eps;
		//soustraire la difference finie de la fonction cost au poids pour aller dans le sens inverse et donc se rapprocher de 0
		w -= dcost * learing_rate;
		printf( "average error : %f\n", cost( w ));
	};
	printf( "--------------------------------------\n" );
	printf( "%f\n", w );

	return ( 0 );
};
