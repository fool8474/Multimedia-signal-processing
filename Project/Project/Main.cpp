#include <math.h>
#include "fileProcess.h"
#include "ImageProcess.h"

int m_Width = 1280;
int m_Height = 720;

BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;

int _tmain(int argc, _TCHAR* argv[]) {
	int i, j, k, l;
	BYTE *IpImg = new BYTE[m_Width * m_Height * 3];
	BYTE *RGBBuf = new BYTE[m_Width * m_Height * 3];

	BYTE *YBuf   = new BYTE[m_Width * m_Height];
	BYTE *RBuf   = new BYTE[m_Width * m_Height];
	BYTE *GBuf   = new BYTE[m_Width * m_Height];
	BYTE *BBuf   = new BYTE[m_Width * m_Height];
	BYTE *OutBuf = new BYTE[m_Width * m_Height];

	const char* targetName = "targetFile.bmp";
	
	ImageDataFromBmp((char*)targetName, &RGBBuf, &m_Width, &m_Height, &hf, &hInfo);
	Bmp2Raw(RGBBuf, m_Width, m_Height);
	printf("check Image Size = %d %d \n", m_Width, m_Height);
	
	RGB2GrayScale(m_Width, m_Height, RGBBuf, YBuf, RBuf, GBuf, BBuf, OutBuf);

	Y2RGB(OutBuf, IpImg, m_Width, m_Height);
	Bmp2Raw(IpImg, m_Width, m_Height);
	const char * outputName = "01_GrayScale.bmp";
	MakeBMPFile_xx((char*)outputName, IpImg, hf, hInfo, m_Width, m_Height);

	delete[]IpImg;
	delete[]YBuf;
	delete[]RBuf;
	delete[]GBuf;
	delete[]RGBBuf;
	delete[]OutBuf;

	printf(" END \n");
}
