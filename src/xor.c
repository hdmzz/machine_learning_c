#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/**
 * La porte XOR peut se traduire par : (x | y) & ~(x & y);
 */
//definir le model, pour la porte XOR il faut ue structure qui comprend plusieurs neurones et les poids correspondant aux portes
//pour lesquelles on a deja entrainé le model
typedef struct {
	float	or_w1;
	float	or_w2;
	float	or_b;
	float	nand_w1;
	float	nand_w2;
	float	nand_b;
	float	and_w1;
	float	and_w2;
	float	and_b;
} Xor;

/**
 * on definit une structure pour les tables de veritées que l'on appelera  sample
 * qui estt un tableau de 3 float
 * puis on ecrit les tables de véritée
*/
typedef float sample[3];

size_t train_count = 4;

sample	xor_train[] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 0},
};

// NAND-gate
sample	or_train[] = {
	{0, 0, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

sample	and_train[] = {
	{0, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 1},
};

sample	nand_train[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 0},
};

sample	nor_train[] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 0},
};

sample	*train = xor_train;

float	sigmoidf(float x)
{
	return ( 1 / ( 1 + expf( -x )));
};


/**
 *Il nous faut une fonction qui initialise le model avec des chiffres random,
 que l'on appelera rand_xor et qui renvoie un model de tip Xor
*/

float	rand_float( void )
{
	return ((float)rand() / (float)RAND_MAX);//un nombre flottant entre 0 et 1;
};

Xor	rand_xor(void)
{
	Xor	m;
	m.or_w1 = rand_float();
	m.or_w2 = rand_float();
	m.or_b = rand_float();
	m.nand_w1 = rand_float();
	m.nand_w2 = rand_float();
	m.nand_b = rand_float();
	m.and_w1 = rand_float();
	m.and_w2 = rand_float();
	m.and_b = rand_float();

	return m;
};

void	print_xor(Xor m)
{
	printf("or_w1 = %f\n", m.or_w1);
	printf("or_w2 = %f\n", m.or_w2);
	printf("or_b = %f\n", m.or_b);
	printf("nand_w1 = %f\n", m.nand_w1);
	printf("nand_w2 = %f\n", m.nand_w2);
	printf("nand_b = %f\n", m.nand_b);
	printf("and_w1 = %f\n", m.and_w1);
	printf("and_w2 = %f\n", m.and_w2);
	printf("and_b = %f\n", m.and_b);
};

/**
 * La fonction forward est la fonction qui alimente le model
 * ou plutot c'est le modele le x1 et x2 passe d'abod dans les couche OR et NAND
 * Puis le resultat des couches passe dans le modele AND
 * la sortie de ce model represente la porte XOR
 * @a servira pour l'entrainement de la OR gate
 * @b la NAND Gate
 * @return le model de la AND Gate
*/
float	forward(Xor m, float x1, float x2)
{
	float	a = sigmoidf(m.or_w1*x1 + m.or_w2*x2 + m.or_b);
	float	b = sigmoidf(m.nand_w1*x1 + m.nand_w2*x2 + m.nand_b);

	return (sigmoidf(m.and_w1*a + m.and_w2*b + m.and_b));
};

/**
 * Fonctionement:
 * pour chaque element des tables de veritées, extraire le x1, x2 de la table
 * puis faire passer (forward) les valeures dans le modele
 * calculer l'erreur
*/
float	cost(Xor m)
{
	float	result = 0.0f;

	for (size_t i = 0; i < train_count; i++) {
		float	x1 = train[i][0];
		float	x2 = train[i][1];
		float	y = forward(m, x1, x2);
		float	d = y - train[i][2];
		result += d*d;
	};

	return (result);
};

/**
 * La fonction finite difference calcul les derivees aproximatives des parametres du modele XOR,
 * Pour chaque parametres du modele m,
 * 1- Sauvegarde de la valeure actuelle
 * 2- Incrementation du parametre de epsilon qui est ici une valeur tres petite;
 * 3- Calcul de la nouvelle valeure du cout
 * 4- Calcul de la dervee approxiative en utilisant la differnece finie
 * 5- Restaure la valeure originale du parametre, pourquoi??
 * la fonction cost appelle la fonction forward qui utilise le modele en entier,
 * il faut donc que les parametre reprennent leur valeurs initiales, si on laisse les valeurs modifie
 * le resultat serait faussé, la suite est simple on garde les valeurs de chaque derivee approximatives dans le
 * modele g, qui est renvoyé puis la fonction learn est modifie la version de depart du modele en assignant a celui ci
 * les valeurs du modele de depart * learning rate;
*/
Xor	finite_diff(Xor m, float eps)
{
	Xor g;
	float	c = cost(m);
	float	saved;

	saved = m.or_w1;
	m.or_w1 += eps;
	g.or_w1 = (cost(m) - c)/eps;
	m.or_w1 = saved;

	saved = m.or_w2;
	m.or_w2 += eps;
	g.or_w2 = (cost(m) - c)/eps;
	m.or_w2 = saved;

	saved = m.or_b;
	m.or_b += eps;
	g.or_b = (cost(m) - c)/eps;
	m.or_b = saved;

	saved = m.nand_w1;
	m.nand_w1 += eps;
	g.nand_w1 = (cost(m) - c)/eps;
	m.nand_w1 = saved;

	saved = m.nand_w2;
	m.nand_w2 += eps;
	g.nand_w2 = (cost(m) - c)/eps;
	m.nand_w2 = saved;

	saved = m.nand_b;
	m.nand_b += eps;
	g.nand_b = (cost(m) - c)/eps;
	m.nand_b = saved;

	saved = m.and_w1;
	m.and_w1 += eps;
	g.and_w1 = (cost(m) - c)/eps;
	m.and_w1 = saved;

	saved = m.and_w2;
	m.and_w2 += eps;
	g.and_w2 = (cost(m) - c)/eps;
	m.and_w2 = saved;

	saved = m.and_b;
	m.and_b += eps;
	g.and_b = (cost(m) - c)/eps;
	m.and_b = saved;

	return g;
};


Xor	learn(Xor m, Xor g, float rate)
{
	m.or_w1 -= rate*g.or_w1;
	m.or_w2 -= rate*g.or_w2;
	m.or_b -= rate*g.or_b;
	m.nand_w1 -= rate*g.nand_w1;
	m.nand_w2 -= rate*g.nand_w2;
	m.nand_b -= rate*g.nand_b;
	m.and_w1 -= rate*g.and_w1;
	m.and_w2 -= rate*g.and_w2;
	m.and_b -= rate*g.and_b;

	return m;
};

int	main(void)
{
	srand(time(0));
	Xor		m = rand_xor();
	float	epsilon = 1e-1;
	float	learnin_rate = 1e-1;

	for (size_t i = 0; i < 100*1000; i++) {
		Xor		g = finite_diff(m, epsilon);
		m = learn(m , g, learnin_rate);
	};

	printf("------------------------------\n");
	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			printf("%zu ^ %zu = %f\n", i, j, forward(m, i, j));
		}
	}
	return (0);
};
