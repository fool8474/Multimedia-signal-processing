#include "Theory.h"

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
