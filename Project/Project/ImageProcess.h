#pragma once

#include "stdafx.h"

class ImageProcess {
private :
		BYTE *YBuf, *RBuf, *GBuf, *BBuf, *OutBuf, *RGBBuf, *IpImg, *CyBuf, *CbBuf, *CrBuf;
		int i, j, k, l;
		int m_Width;
		int m_Height;
		byte currentY;
		int changedY;

public :
	void SetImageProcess(BYTE *ICyBuf, BYTE *ICbBuf, BYTE *ICrBuf, BYTE *IYBuf, BYTE *IRBuf, BYTE *IGBuf, BYTE *IBBuf, BYTE *IOutBuf, BYTE *IRGBBuf, BYTE *IIpImg, int Im_Width, int Im_Height);
	void RGB2GrayScale();
	void NagativeImage();
	void BrightnessChange(int changeNum);
	void ContrastChange(double changeNum);
	void ToBinaryImage(byte dividePoint);
	void ChangeColorInRange(int xStartPoint, int xEndPoint, int yStartPoint, int yEndPoint, BYTE R, BYTE G, BYTE B);
	void MosaicImage(int mosaicSize);
	void ToYCbCr();
	void ConvGradient(double changeNum);
	void ConvHighPass();
	void ConvEmbossing();
	void ConvSobelEdge(int edgePoint);
	void CalFilter3by3(int filter[3][3]);
	void BinaryByHistogram(double binaryBoundary);
	void getDiffVideo();
	void getCorrelation();
};