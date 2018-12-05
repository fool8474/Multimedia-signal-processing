#include <math.h>
#include "fileProcess.h"
#include "ImageProcess.h"
#include "Theory.h"

int m_Width = 1280;
int m_Height = 720;

BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;
BYTE *YBuf, *RBuf, *GBuf, *BBuf, *OutBuf, *RGBBuf, *IpImg, *CrBuf, *CbBuf, *CyBuf;
ImageProcess ip;


void SelectImageProcessingMethod(int select);
void getOutputImage(boolean isRGB, boolean doSave);

int _tmain(int argc, _TCHAR* argv[]) {

	IpImg  = new BYTE[m_Width * m_Height * 3];
	RGBBuf = new BYTE[m_Width * m_Height * 3];
	YBuf   = new BYTE[m_Width * m_Height];
	RBuf   = new BYTE[m_Width * m_Height];
	GBuf   = new BYTE[m_Width * m_Height];
	BBuf   = new BYTE[m_Width * m_Height];
	OutBuf = new BYTE[m_Width * m_Height];
	CrBuf  = new BYTE[m_Width * m_Height];
	CbBuf  = new BYTE[m_Width * m_Height];
	CyBuf  = new BYTE[m_Width * m_Height];

	const char* targetName = "targetFile.bmp";
	
	ImageDataFromBmp((char*)targetName, &RGBBuf, &m_Width, &m_Height, &hf, &hInfo);
	Bmp2Raw(RGBBuf, m_Width, m_Height);
	printf("check Image Size = %d %d \n", m_Width, m_Height);

	ip.SetImageProcess(CyBuf, CbBuf, CrBuf, YBuf, RBuf, GBuf, BBuf, OutBuf, RGBBuf, IpImg, m_Width, m_Height);
	ip.RGB2GrayScale();

	SelectImageProcessingMethod(22); // Change This Number To Select Method
	getOutputImage(false, false); // False : GrayScale True : RGB / True : Save
	
	delete[]IpImg, YBuf, RBuf, GBuf, OutBuf, CrBuf, CbBuf, CyBuf;

	printf("END \n");

	return 0;
}

void getOutputImage(boolean isRGB, boolean doSave) {
	const char * outputName = "22_histogramBinary150.bmp";

	if (doSave) {
		if (isRGB) {
			Y2RGB(YBuf, IpImg, m_Width, m_Height);
			Bmp2Raw(RGBBuf, m_Width, m_Height);
		}

		else {
			Y2RGB(OutBuf, IpImg, m_Width, m_Height);
			Bmp2Raw(IpImg, m_Width, m_Height);
		}

		MakeBMPFile_xx((char*)outputName, IpImg, hf, hInfo, m_Width, m_Height);
	}
}

void SelectImageProcessingMethod(int select) {

	switch (select) {
	case 0:
		ip.NagativeImage(); break;

	case 1:
		ip.BrightnessChange(-50); break;

	case 2:
		ip.ContrastChange(1.5); break;

	case 3:
		ip.ToBinaryImage(150); break;

	case 4:
		ip.ChangeColorInRange(80, 500, 400, 600, 255, 120, 120); break;

	case 5:
		ip.MosaicImage(30); break;

	case 6:
		ip.ToYCbCr(); break;

	case 7:
		ip.ConvGradient(1); break;

	case 8:
		ip.ConvHighPass(); break;

	case 9:
		ip.ConvEmbossing(); break;

	case 10:
		ip.ConvSobelEdge(150); break;

	case 11:
		ip.BinaryByHistogram(0.01); break;

		/* upper 20 is Theory Range */
	case 20:
		NNI(2.7); break;

	case 21:
		Gonzzalez_Woods(m_Height, m_Width, YBuf); break;

	case 22:
		getStandardDevation(); break;
	}
}