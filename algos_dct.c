#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM 8
#define PI 3.1415926

// DCT - Discrete Cosine Transform
void DCT(short data[NUM][NUM])
{
	short output[NUM][NUM];
	double ALPHA, BETA;

	short u = 0;
	short v = 0;
	short i = 0;
	short j = 0;

	for (u = 0; u < NUM; u++) {
		for (v = 0; v < NUM; v++) {
			if (u == 0) {
				ALPHA = sqrt(1.0 / NUM);
			} else {
				ALPHA = sqrt(2.0 / NUM);
			}

			if (v == 0) {
				BETA = sqrt(1.0 / NUM);
			} else {
				BETA = sqrt(2.0 / NUM);
			}

			double tmp = 0.0;
			for (i = 0; i < NUM; i++) {
				for (j = 0; j < NUM; j++) {
					tmp += data[i][j] * \
					cos((2 * i + 1) * u * PI / (2.0 * NUM)) * \
					cos((2 * j + 1) * v * PI / (2.0 * NUM));
				}
			}
			output[u][v] = round(ALPHA * BETA * tmp);
		}
	}

	memset(data, 0, NUM * NUM * sizeof(short));
	memcpy(data, output, NUM * NUM * sizeof(short));
}

// Inverse DCT
void IDCT(short data[NUM][NUM])
{
	short output[NUM][NUM];
	double ALPHA, BETA;

	short u = 0;
	short v = 0;
	short i = 0;
	short j = 0;

	for (i = 0; i < NUM; i++) {
		for (short j = 0; j < NUM; j++) {

			double tmp = 0.0;
			for (short u = 0; u < NUM; u++) {
				for (v = 0; v < NUM; v++) {
					if (u == 0) {
						ALPHA = sqrt(1.0 / NUM);
					} else {
						ALPHA = sqrt(2.0 / NUM);
					}

					if (v == 0) {
						BETA = sqrt(1.0 / NUM);
					} else {
						BETA = sqrt(2.0 / NUM);
					}

					tmp += ALPHA * BETA * data[u][v] * \
					cos((2 * i + 1) * u * PI / (2.0 * NUM)) * \
					cos((2 * j + 1) * v * PI / (2.0 * NUM));
				}
			}
			output[i][j] = round(tmp);
		}
	}
	memset(data, 0, NUM * NUM * sizeof(short));
	memcpy(data, output, NUM * NUM * sizeof(short));
}

int main(void)
{
	short i = 0;
	short j = 0;
	short u = 0;
	short v = 0;

	// 8 x 8 DT raw data
	short input[NUM][NUM] =
	{
		/*{89, 101, 114, 125, 126, 115, 105, 96},
		{97, 115, 131, 147, 149, 135, 123, 113},
		{114, 134, 159, 178, 175, 164, 149, 137},
		{121, 143, 177, 196, 201, 189, 165, 150},
		{119, 141, 175, 201, 207, 186, 162, 144},
		{107, 130, 165, 189, 192, 171, 144, 125},
		{97, 119, 149, 171, 172, 145, 117, 96},
		{88, 107, 136, 156, 155, 129, 97, 75}*/
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128},
		{-128, -128, -128, -128, -128, -128, -128, -128}
	};
 
	DCT(input);
	printf("The result of DCT:\n");
	for (u = 0; u < NUM; u++) {
		for (v = 0; v < NUM; v++) {
			printf("%hd\t", input[u][v]);
		}
		printf("\n");
	}
 
	IDCT(input);
	printf("The result of IDCT:\n");
	for (i = 0; i < NUM; i++) {
		for (short j = 0; j < NUM; j++) {
			printf("%hd\t", input[i][j]);
		}
		printf("\n");
	}
 
	return 0;
}

/**
* from http://blog.csdn.net/pathuang68/article/details/4193990
* gcc algos_dct.c -o algos_dct -std=c99 -lm
*/

