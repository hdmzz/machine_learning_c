//on veut siùuler une OR gate
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define train_count (sizeof(train_data) / sizeof(train_data[0]))

float	train_data[][3] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

/**
 * @param x le resultat de l'addition
 */
float	relu(float x)
{
	return x > 0 ? x : 0;
};

float	sigmoidf(float x)
{
	return ( 1 / ( 1 + expf( -x )));
};

/**
 * @param w1 le poid arbitraire qui servira a multipllier le premier argument
 * @param w2 le poid arbitraire qui servira a multipllier le second argument

 * Le but de cette fonction est de calculer le cout des poids que le transmet c'est a dire de voire l'erreu
 * que produise les deux poids initiaux,
 * le but etant d'ajuster ces poids pour trouver ceux qui fit parfaitement
 * donc on regarde le resultat de l'operation Premier argument * Premier Poid + Secondd Argument * Second Poid
 * On fait cela pour chaque ligne de la table de veritée et on ajuste les poids
 * @Function Relu utilisée pour enlever les resultats négatifs
 */
float	cost(float w1, float w2, float b)
{
	float	result = 0.0f;
	for ( size_t i = 0; i < train_count; i++ ) {
		float	x1 = train_data[i][0];
		float	x2 = train_data[i][1];
		float	y = sigmoidf(x1*w1 + x2*w2 + b);
		float	d = y - train_data[i][2];
		result += d*d;
	};
	result /= train_count;

	return ( result );
};

float	rand_float( void )
{
	return ((float)rand() / (float)RAND_MAX);//un nombre flottant entre 0 et 1;
};


/**
 * @main Le deroule des operations:
 * definir les 2 poids de depart puis un epslion et la learning rate
 */
int	main(void)
{
	srand(69);
	float	w1 = rand_float();
	float	w2 = rand_float();
	float 	b = rand_float();

	float	eps = 1e-3;//
	float	rate = 1e-1;//learning rate

	for (size_t i = 0; i < 5000; i++) {
		float	c = cost(w1, w2, b);
		float	dw1 = (cost(w1 + eps, w2, b) - c) / eps;
		float	dw2 = (cost(w1, w2 + eps, b) - c) / eps;
		float	db = (cost(w1, w2, b + eps) - c) / eps;

		w1 -= rate*dw1;
		w2 -= rate*dw2;
		b -= rate*db;
	};
	printf("w1: %f, w2: %f, cost: %f\n", w1, w2, cost(w1, w2, b));
	return (0);
}
