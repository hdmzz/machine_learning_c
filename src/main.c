#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define train_count (sizeof(train_data) / sizeof(train_data[0]))
#define test_count (sizeof(test_data) / sizeof(test_data[0]))
//x = entree, y = resultat w est le model mathematique
float	train_data[][2] = {
	{0, 0},
	{1, 2},
	{2, 4},
	{3, 6},
	{4, 8},
};

float	test_data[][2] = {
	{5, 10},
	{6, 12},
	{7, 14},
	{8, 16},
	{9, 18},
};

float	rand_float( void )
{
	return (( float )rand() / (float)RAND_MAX );//un nombre flottant entre 0 et 1;
};

float	predict( float x, float w, float b )
{
	// resultat recupere du model //! on introduit la notion de biais
	return (x * w + b);
};

void	validate_model(float w, float b)
{
	for ( size_t i = 0; i < test_count; i++ ) {
		float	x = test_data[i][0];
		float	predicted = predict(x, w, b);
		float	actual = test_data[i][1];
		printf("input: %f, predicted: %f, actual: %f\n", x, predicted, actual);
	};
};

float	cost( float w, float b )
{
	float	result = 0.0f;
	for ( size_t i = 0; i < train_count; i++ ) {
		float	x = train_data[i][0];//entree
		float	y = predict(x, w, b);
		float	d = y - train_data[i][1]; //difference entre le resultat calculé et le resultat attendu
		result += d * d;//on stock le carre du resultat dans la variable result, le carre car cela permet de voir les petites erreurs et d'avoir une valeur absolue
	};
	result /= train_count;//on veut voir la valeur pondérré de l'erreur sur le jeu de données

	return ( result );
};



int	main( void )
{
	srand(69);
	float	w = rand_float() * 10.0f;
	float	b = rand_float() * 5.0f;
	float	eps = 1e-3;
	float	learing_rate = 1e-3;
	float	error_treshold = 1e-6;

	float	best_w = w;
	float	best_b = b;
	float	best_error = __FLT_MAX__;
	long	i = 0;
	float	current_error = cost(w, b);

	while (current_error > error_treshold) {
		float	previous_error = current_error;
		current_error = cost(w, b);
		if ( current_error < best_error ) {
			best_w = w;
			best_b = b;
			best_error = current_error;
		};

		if ( current_error > previous_error ) {
			learing_rate *= 0.9;
		} else {
			learing_rate *= 1.1;
		};

		//!calcul des gradients
		float	dw = (cost(w + eps, b) - current_error) / eps;
		float	db = (cost(w, b + eps) - current_error) / eps;

		w -= dw * learing_rate;
		b -= db * learing_rate;
		if ( i % 500 == 0 )
		printf( "average error : %f, weight: %f, bias: %f\n", current_error, w, b);
	};
	printf( "--------------------------------------\n" );
	printf( "w: %f, b: %f\n", w, b );
	validate_model(best_w, best_b);

	return ( 0 );
};
