#include <math.h>
#include "fileProcess.h"
#include "ImageProcess.h"
#include "Theory.h"

int m_Width = 512;
int m_Height = 512;
// change Size by input Image

BITMAPFILEHEADER hf;
BITMAPINFOHEADER hInfo;
BYTE *YBuf, *RBuf, *GBuf, *BBuf, *OutBuf, *RGBBuf, *IpImg, *CrBuf, *CbBuf, *CyBuf;
BYTE *IpImg2, *RGBBuf2, *YBuf2, *RBuf2, *BBuf2, *GBuf2;
ImageProcess ip;
const char* targetName;

void SelectImageProcessingMethod(int select);
void getOutputImage(boolean isRGB, boolean doSave);
void getInputImage(const char * targetName, BYTE * inputBuf, BYTE * inputR, BYTE * inputG, BYTE * inputB, BYTE * inputY);
void initializeVariables();

int _tmain(int argc, _TCHAR* argv[]) {

	initializeVariables();
	
	targetName = "IRIS_RGB.bmp";
	getInputImage(targetName, RGBBuf, RBuf, GBuf, BBuf, YBuf);
	targetName = "watermark_horse.bmp";
	getInputImage(targetName, RGBBuf2, RBuf2, GBuf2, BBuf2, YBuf2);

	ip.SetImageProcess(CyBuf, CbBuf, CrBuf, YBuf, RBuf, GBuf, BBuf, OutBuf, RGBBuf, IpImg, m_Width, m_Height);

	SelectImageProcessingMethod(17); // Change This Number To Select Method
	getOutputImage(false, true); // False : GrayScale True : RGB / True : Save

	delete[]IpImg, YBuf, RBuf, GBuf, OutBuf, CrBuf, CbBuf, CyBuf;

	return 0;
}

void initializeVariables() {
	IpImg = new BYTE[m_Width * m_Height * 3];
	RGBBuf = new BYTE[m_Width * m_Height * 3];
	YBuf = new BYTE[m_Width * m_Height];
	RBuf = new BYTE[m_Width * m_Height];
	GBuf = new BYTE[m_Width * m_Height];
	BBuf = new BYTE[m_Width * m_Height];
	OutBuf = new BYTE[m_Width * m_Height];
	CrBuf = new BYTE[m_Width * m_Height];
	CbBuf = new BYTE[m_Width * m_Height];
	CyBuf = new BYTE[m_Width * m_Height];

	IpImg2 = new BYTE[m_Width * m_Height * 3];
	RGBBuf2 = new BYTE[m_Width * m_Height * 3];
	YBuf2 = new BYTE[m_Width*m_Height];
	RBuf2 = new BYTE[m_Width*m_Height];
	GBuf2 = new BYTE[m_Width*m_Height];
	BBuf2 = new BYTE[m_Width*m_Height];
}

void getInputImage(const char * targetName, BYTE * inputBuf, BYTE * inputR, BYTE * inputG, BYTE * inputB, BYTE * inputY) {
	int i, j;

	ImageDataFromBmp((char*)targetName, &inputBuf, &m_Width, &m_Height, &hf, &hInfo);
	Bmp2Raw(inputBuf, m_Width, m_Height);

	for (i = 0; i < m_Height; i++)
	{
		for (j = 0; j < m_Width; j++)
		{
			*(inputR + i * m_Width + j) = *(inputBuf + (i)* m_Width * 3 + 3 * (j)+0);
			*(inputB + i * m_Width + j) = *(inputBuf + (i)* m_Width * 3 + 3 * (j)+1);
			*(inputG + i * m_Width + j) = *(inputBuf + (i)* m_Width * 3 + 3 * (j)+2);
			*(inputY + i * m_Width + j) = (*(inputR + i * m_Width + j) + *(inputG + i * m_Width + j) + *(inputB + i * m_Width + j)) / 3;
			*(OutBuf + i * m_Width + j) = *(inputY + i * m_Width + j);
		}
	}
}

void getOutputImage(boolean isRGB, boolean doSave) {
	const char * outputName = "17_getIrisEdge.bmp";

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

	case 12:
		ip.GetDiffVideo(); break;

	case 13:
		ip.GetCorrelation(); break;

	case 14:
		ip.GetDiffVideoWith2Image(YBuf2); break;

	case 15 :
		ip.InputWatermark(YBuf2); break;

	case 16 :
		ip.ExtractWatermark(); break;

	case 17 :
		ip.GetIrisRange(); break;

		/* upper 20 is Theory Range */
	case 20:
		NNI(2.7); break;

	case 21:
		Gonzzalez_Woods(m_Height, m_Width, YBuf); break;

	case 22:
		getStandardDevation(); break;

	case 23:
		getEntropy(m_Height, m_Width, YBuf); break;

	case 24:
		JPEG_Encoding(); break;
	}
}