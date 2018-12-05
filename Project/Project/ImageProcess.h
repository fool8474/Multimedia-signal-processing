#pragma once

#include "stdafx.h"

class ImageProcess {
private :
		BYTE *YBuf, *RBuf, *GBuf, *BBuf, *OutBuf, *RGBBuf, *IpImg;
		int i, j, k, l;
		int m_Width;
		int m_Height;
public :
	void SetImageProcess(BYTE *IYBuf, BYTE *IRBuf, BYTE *IGBuf, BYTE *IBBuf, BYTE *IOutBuf, BYTE *IRGBBuf, BYTE *IIpImg, int Im_Width, int Im_Height);
	void RGB2GrayScale();
	void NagativeImage();
};