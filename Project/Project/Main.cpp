#include <math.h>
#include "fileProcess.h"
#include "ImageProcess.h"

int m_Width = 1280;
int m_Height = 720;

BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;
BYTE *YBuf, *RBuf, *GBuf, *BBuf, *OutBuf, *RGBBuf, *IpImg;
ImageProcess ip;

void SelectImageProcessingMethod(int select);

int _tmain(int argc, _TCHAR* argv[]) {
	int i, j, k, l;

	IpImg = new BYTE[m_Width * m_Height * 3];
	RGBBuf = new BYTE[m_Width * m_Height * 3];

	YBuf   = new BYTE[m_Width * m_Height];
	RBuf   = new BYTE[m_Width * m_Height];
	GBuf   = new BYTE[m_Width * m_Height];
	BBuf   = new BYTE[m_Width * m_Height];
	OutBuf = new BYTE[m_Width * m_Height];

	const char* targetName = "targetFile.bmp";
	
	ImageDataFromBmp((char*)targetName, &RGBBuf, &m_Width, &m_Height, &hf, &hInfo);
	Bmp2Raw(RGBBuf, m_Width, m_Height);
	printf("check Image Size = %d %d \n", m_Width, m_Height);

	ip.SetImageProcess(YBuf, RBuf, GBuf, BBuf, OutBuf, RGBBuf, IpImg, m_Width, m_Height);
	ip.RGB2GrayScale();

	SelectImageProcessingMethod(2);

	Y2RGB(OutBuf, IpImg, m_Width, m_Height);
	Bmp2Raw(IpImg, m_Width, m_Height);
	const char * outputName = "02_Contrast1_5.bmp";
	MakeBMPFile_xx((char*)outputName, IpImg, hf, hInfo, m_Width, m_Height);

	delete[]IpImg, YBuf, RBuf, GBuf, OutBuf;

	printf(" END \n");
}

void SelectImageProcessingMethod(int select) {

	switch (select) {
	case 0:
		ip.NagativeImage();
		break;

	case 1:
		ip.BrightnessChange(-50);
		break;

	case 2:
		ip.ContrastChange(1.5);
		break;
	}
}