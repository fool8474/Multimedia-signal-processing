#include <math.h>
#include "ImageProcess.h"

void ImageProcess :: SetImageProcess(BYTE *IYBuf, BYTE *IRBuf, BYTE *IGBuf, BYTE *IBBuf, BYTE *IOutBuf, BYTE *IRGBBuf, BYTE *IIpImg, int Im_Width, int Im_Height) {
	YBuf = IYBuf;
	RBuf = IRBuf;
	GBuf = IGBuf;
	BBuf = IBBuf;
	OutBuf = IOutBuf;
	RGBBuf = IRGBBuf;
	IpImg = IIpImg;
	m_Width = Im_Width;
	m_Height = Im_Height;
}

void ImageProcess::RGB2GrayScale() {
	printf("Make GrayScale Image\n");
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

void ImageProcess::NagativeImage() {
	byte x;

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			x = *(YBuf + i * m_Width + j);
			x = 255 - x;
			*(OutBuf + i * m_Width + j) = x;
		}
	}
}

void ImageProcess::BrightnessChange(int changeNum) {

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			currentY = *(YBuf + i * m_Width + j);
			changedY = currentY + changeNum;

			if (changedY > 255) changedY = 255;
			if (changedY < 0) changedY = 0;

			*(OutBuf + i * m_Width + j) = (BYTE)changedY;
		}
	}
}

void ImageProcess::ContrastChange(double changeNum) {

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			currentY = *(YBuf + i * m_Width + j);
			changedY = currentY * changeNum;
			
			if (changedY > 255) changedY = 255;
			if (changedY < 0) changedY = 0;

			*(OutBuf + i * m_Width + j) = (BYTE)changedY;
		}
	}
}