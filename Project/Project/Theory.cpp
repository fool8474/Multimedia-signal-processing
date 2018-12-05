#include "Theory.h"
#include <math.h>

void NNI(double NNINumber) {
	int x[10] = { 10,20,30,40,50,60,70,80,90,100 };
	int y[25];

	for (int i = 0; i < 25; i++) {
		int Y_source = (int)((i / NNINumber) + 0.5);
		if (Y_source >= 10) {
			Y_source = 9;
		}

		y[i] = x[Y_source];
		printf("%d ", y[i]);
	}

	printf("\n");
}

void Gonzzalez_Woods(int m_Height, int m_Width, byte* YBuf) {
	int i, j;
	double T;
	double average = 0;
	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			average += *(YBuf + i * m_Width + j);
		}
	}

	T = average / (m_Height * m_Width);

	double prevT = 0;

	while (true) {
		double G1 = 0;
		int G1count = 0;
		double G2 = 0;
		int G2count = 0;
		for (i = 0; i < m_Height; i++) {
			for (j = 0; j < m_Width; j++) {
				if (T > *(YBuf + i * m_Width + j)) {
					G1 += *(YBuf + i * m_Width + j);
					G1count++;
				}

				else {
					G2 += *(YBuf + i * m_Width + j);
					G2count++;
				}
			}
		}

		G1 /= G1count;
		G2 /= G2count;

		prevT = T;
		T = (G1 + G2) / 2;

		double resultT = T - prevT;
		if (resultT < 0) {
			resultT = -resultT;
		}

		if (resultT < 0.2) {
			break;
		}

		printf("T °ªÀº %f\n", T);
	}
}

void getStandardDevation() {
	int i;
	double arrayX[] = { 4.5393,    4.9886,    1.0338,    1.9595,    3.1060,    4.2193,    6.2575,
						3.4201,    6.5231 ,   4.9508  ,  6.3482,    4.2539   , 2.6864,    1.0372,
						4.3110,   5.6371,    3.4148,    2.9184 ,   3.3827,    1.8068 ,   3.0140,
						3.6385,    4.0917,    3.8724,    5.2227 ,   4.2186  ,  7.6280 ,   4.6240,
						7.6090,    2.5538,    5.0531 ,   3.4795,    5.2003 ,   5.1879  , 0.3720,
						1.3459,    1.1180,    4.8037 ,   6.9404 ,   3.3464  ,  5.6246  ,  5.0911,
						1.8967,    4.7949 ,   2.4962  ,  7.0325,    3.9349 ,   7.2720 ,   3.1499,
						5.1789 };

	int sizeX = sizeof(arrayX);
	printf("size X = %d\n", sizeX);
	sizeX = sizeof(arrayX) / sizeof(arrayX[1]);

	double sum = 0;
	for (i = 0; i < sizeX; i++) {
		sum += arrayX[i];
	}

	double averageArray = sum / sizeX;
	printf("averageX = %f\n", averageArray);

	double sumOfstandardDevation = 0;
	for (i = 0; i < sizeX; i++) {
		sumOfstandardDevation += pow(arrayX[i] - averageArray, 2);
	}
	double averageSD = sumOfstandardDevation / sizeX;
	printf("standardDevation = %f\n", averageSD);
	double std_dev = sqrt(averageSD);
}

void getEntropy(int m_Height, int m_Width, BYTE* YBuf) {
	int i, j;
	int *histogram = new int[256];

	for (i = 0; i < 256; i++) {
		*(histogram + i) = 0;

	}

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			*(histogram + *(YBuf + i * m_Width + j)) += 1;
		}
	}

	float *probability = new float[256];
	float fullSize = m_Width * m_Height;
	printf("fullSize = %d\n", &fullSize);

	for (i = 0; i < 256; i++) {
		*(probability + i) = *(histogram + i) / fullSize;
		printf("histogram : %d ,", *(histogram + i));
		printf("probability : %f \n", *(probability + i));
	}

	float sumOfEntropy = 0;
	float log;

	for (i = 0; i < 256; i++) {

		float curP = *(probability + i);
		if (curP != 0) {
			log = log10(curP) / log10(2.0);
			sumOfEntropy += curP * log;
		}
	}

	sumOfEntropy = -sumOfEntropy;
	printf("Sum : %f\n", sumOfEntropy);
}