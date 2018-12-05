#include <math.h>
#include "fileProcess.h"

void RGB2GrayScale(int m_Width, int m_Height, BYTE *RGBBuf, BYTE *YBuf, BYTE *RBuf, BYTE *GBuf, BYTE *BBuf, BYTE *OutBuf) {

	printf("Make GrayScale Image\n");
	int i, j;
	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			*(RBuf + i * m_Width + j) = *(RGBBuf + (i)* m_Width * 3 + 3 * j + 0);
			*(GBuf + i * m_Width + j) = *(RGBBuf + (i)* m_Width * 3 + 3 * j + 1);
			*(BBuf + i * m_Width + j) = *(RGBBuf + (i)* m_Width * 3 + 3 * j + 2);

			*(YBuf + i * m_Width + j) = (*(RBuf + i * m_Width + j) + *(GBuf + i * m_Width + j)) / 3;
			*(OutBuf + i * m_Width + j) = *(YBuf + i * m_Width + j);
		}
	}
}
