#include "Theory.h"
#include <math.h>
#define PI (3.1415)

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




BYTE grayY[8][8] = { {137, 139, 139, 136, 134, 137, 145, 152 },
						 {137, 137, 138, 138, 135, 136, 143, 152 },
						 {137, 139 ,140, 139 ,134, 144, 145, 150 },
						 {134, 140, 140, 138 ,140, 144, 145, 146},
						 {137, 139, 141 ,136 ,134, 137, 145, 140 },
						 {137, 139, 140, 140 ,144, 146, 144, 133},
						 {140, 140, 142, 146, 148, 143, 134 ,128 },
						 {142, 139, 139, 145, 149, 143, 132, 128 } };

BYTE QTable[8][8] = { {16, 11, 10, 16, 24, 40, 51, 61 },
					{12, 12, 14, 19, 26, 58, 60, 55 },
					 {14, 13 ,16, 24 ,40, 57, 69, 56 },
					 {14, 17, 22, 29 ,51, 87, 80, 62},
					 {18, 22, 37 ,56 ,68, 109, 103, 77 },
					 {23, 35, 55, 64 ,81, 101, 113, 92},
					 {49, 64, 78, 87, 103, 121, 120 ,101 },
					 {72, 92, 95, 98, 112, 100, 103, 99 } };

BYTE zigzag[8][8] = {0, 1, 5, 6,14,15,27,28,
					 2, 4, 7,13,16,26,29,42,
					 3, 8,12,17,25,30,41,43,
					 9,11,18,24,31,40,44,53,
				 	 10,19,23,32,39,45,52,54,
			 		 20,22,33,38,46,51,55,60,
					 21,34,37,47,50,56,59,61,
					 35,36,48,49,57,58,62,63 };

float *DCT;

void calDCT() {
	int i, j;
	DCT = new float[8 * 8];
	float curResult;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			curResult = 0;

			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < 8; l++) {
					curResult += grayY[k][l] * cos(float((2 * k + 1)*i*PI) / 16) * cos(float((2 * l + 1)*j*PI) / 16);
				}
			}

			curResult = curResult / 4;

			*(DCT + (i * 8) + j) = curResult;
		}
	}

	for (i = 0; i < 64; i++) {

		if (i % 8 == 0) {
			printf("\n");
		}

		printf("%f ", *(DCT + i));
	}
}

void quentization() {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			*(DCT + (i * 8) + j) = int(*(DCT + (i * 8) + j) / QTable[i][j] + 0.5);
		}
	}

	printf("\n");

	for (i = 0; i < 64; i++) {

		if (i % 8 == 0) {
			printf("\n");
		}

		printf("%f ", *(DCT + i));
	}

	printf("\n\n");
}

void calZigzag() {
	int i, j;
	int DCT_coeff_zigzag[64];

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			BYTE loc = zigzag[i][j];

			DCT_coeff_zigzag[loc] = zigzag[i][j];
		}
	}

	for (i = 0; i < 64; i++) {
		printf("%d ", DCT_coeff_zigzag[i]);
	}
	printf("\n\n");
}

void JPEG_Encoding() {
	int i, j;

	calDCT();
	quentization();
	calZigzag();
}
