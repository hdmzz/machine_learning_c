#ifndef NN_H
#define NN_H


#include <stddef.h>//size t definition
#include <stdio.h>
#include <time.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif //NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif //NN_ASSERT

typedef struct {
    size_t rows;
    size_t cols;
    float *es;//pointer to the begining of the matrix that contains the float
} Matrix;

#define MAT_AT(m, i, j) (m).es[(i)*(m).cols + (j)]

Matrix mat_alloc(size_t rows, size_t cols);
void mat_sum(Matrix dest, Matrix a); //Il n'y  pas besoin de transmettre un pointeur ici car la structure Matrix comporte un pointeur sur le det de la donnee, soit la matrix
void mat_dot(Matrix dest, Matrix a, Matrix b);
void mat_print(Matrix m, const char *name);
void mat_fill(Matrix m, float x);

float rand_float(void);

#endif //NN_H


#ifdef NN_IMPLEMENTATION

Matrix mat_alloc(size_t rows, size_t cols)
{
    Matrix m = {
        .cols = cols,
        .rows = rows,
        .es = NN_MALLOC(sizeof(float)*rows*cols)
    };
    NN_ASSERT(m.es != NULL); // Vérifie que l'allocation a réussi
    return m;
};

/**
 * Pour additionner deux vecteurs il faut qu'ils aient le meme nombre de ligne et le meme nombre de colonnes
 * la destination est une matrice a ajoute a l matrice A
 */
void mat_sum(Matrix dest, Matrix a)
{
    NN_ASSERT(dest.rows == a.rows);
    NN_ASSERT(dest.cols == a.cols);

    for (size_t i = 0; i < dest.rows; i++) {
        for (size_t j = 0; j < dest.cols; j++) {
            MAT_AT(dest, i, j) +=  MAT_AT(a, i, j);
        };
    };
};

/**
 * la matrice est  organisee de cette facon:
 *      A    B
 *      C    D
 * mais stockee en memoire dans un tableau 1 dimension
 * la formule  pour recuperer l'inndice correpsondant est la suivante
 * indice = num de ligne * nombre de colonnes + num de colonne;
 */
void mat_dot(Matrix dest, Matrix a, Matrix b)
{
    NN_ASSERT(a.rows == b.cols);//pour multiplier deux matrices il faut que le nombre de colonnes de la premiere soit egale au nombre de lignes de la seconde
    size_t n = a.cols;
    //ensuite on verifie que la destination peut bien contenir le produit des deux matrices donc
    NN_ASSERT(dest.rows == a.rows);
    NN_ASSERT(dest.cols ==  b.cols);
    /**
     * lire a l'envers: pouur  chaque colonnes de chaques lignes de la destination qui sera de bonne taille
     */
    for (size_t i = 0; i < dest.rows; i++) {
        for (size_t j = 0; j < dest.cols; j++)  {
            //dabord mettre l'emplacement correspondant de la matrice de destiantion a zero
            MAT_AT(dest, i, j) = 0;
            for (size_t k = 0; k < n; k++) {
                MAT_AT(dest, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);//le nombre k represente le nombres de colonnes de la premiere matrice qui EST egal au nombre de lignes de la deuxieme, c'est pour cela qu'on peut chercher a l'indice de row k dans la matrice b
                //donc k est egal a la colonne dans la matrice A et a la ligne dans la matrice B
            };
        };
    };
};

#define MAT_PRINT(m) mat_print(m, #m);

void mat_print(Matrix m, const char *name)
{
    printf("\n\nMatrix %s\n", name);
    printf("[\n");
    for (size_t i = 0; i < m.rows; i++) {
        for  (size_t j = 0; j < m.cols; j++) {
            printf("    %f ", MAT_AT(m, i, j));
        };
        printf("\n");
    };
    printf("]\n");
};

void mat_fill(Matrix m, float x)
{
    for (size_t i = 0; i < m.rows; i++) {
        for  (size_t j = 0; j < m.cols; j++) {
            MAT_AT(m, i, j) = x;
        };
    };
};

float	rand_float(void)
{
	return ((float)rand() / (float)RAND_MAX);//un nombre flottant entre 0 et 1;
};

void mat_rand(Matrix dest, float low, float high)
{
    for (size_t i = 0; i < dest.rows; i++) {
        for  (size_t j = 0; j < dest.cols; j++) {
            MAT_AT(dest, i, j) = rand_float()*(high -low) + low;
        };
    };
}

#endif // NN_IMPLEMENTATION
