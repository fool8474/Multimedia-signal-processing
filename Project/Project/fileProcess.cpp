#include "fileProcess.h";
#include <math.h>

void ImageDataFromBmp(char *filename, BYTE **CurBuf, int *m_Width, int *m_Height, BITMAPFILEHEADER *hf, BITMAPINFOHEADER *hInfo) {
	FILE *InFile;
	errno_t err;
	err = fopen_s(&InFile, filename, "rb");

	if (InFile == NULL) {
		printf(" -> NO BMP File : %s\n", filename);
		return;
	}

	memset(hf, 0, sizeof(BITMAPFILEHEADER));
	memset(hInfo, 0, sizeof(BITMAPFILEHEADER));

	fread(hf, sizeof(BITMAPFILEHEADER), 1, InFile);
	if ((*hf).bfType != 0x4D42) return; //BMPª¸ªãªÊª¤íÞùê
	fread(hInfo, sizeof(BITMAPINFOHEADER), 1, InFile);

	*m_Width = (*hInfo).biWidth;
	*m_Height = (*hInfo).biHeight;

	fread(*CurBuf, sizeof(char), (*m_Width)*(*m_Height) * 3, InFile);
	fclose(InFile);

	return;
}

void Bmp2Raw(BYTE *BmpBuf, int m_Width, int m_Height) {
	int i, j;
	int depth = 3;

	BYTE *RawBuf = new BYTE[m_Width*m_Height * 3];

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width * 3; j += 3) {
			RawBuf[i*m_Width*depth + j    ] = BmpBuf[i*m_Width*depth + j + 2];
			RawBuf[i*m_Width*depth + j + 1] = BmpBuf[i*m_Width*depth + j + 1];
			RawBuf[i*m_Width*depth + j + 2] = BmpBuf[i*m_Width*depth + j    ];
		}
	}

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width * 3; j++) {
			BmpBuf[i*m_Width * depth + j] = RawBuf[(m_Height - 1 - i)*m_Width * depth + j];
		}
	}

	delete[]RawBuf;
}

void Y2RGB(BYTE *YBuf, BYTE *RGBBuf, int m_Width, int m_Height) {
	int i, j;
	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			*(RGBBuf + i * 3 * m_Width + 3 * j)     = *(YBuf + i * m_Width + j);
			*(RGBBuf + i * 3 * m_Width + 3 * j + 1) = *(YBuf + i * m_Width + j);
			*(RGBBuf + i * 3 * m_Width + 3 * j + 2) = *(YBuf + i * m_Width + j);
		}
	}
}

void MakeBMPFile_xx(char *FileName, BYTE *OutImage, BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo, int w, int h) {
	FILE *OutFile;
	int m_Width, m_Height;

	hInfo.biWidth = w;
	hInfo.biHeight = h;
	m_Width = hInfo.biWidth;
	m_Height = hInfo.biHeight;

	errno_t err;

	err = fopen_s(&OutFile, FileName, "wb");

	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), OutFile);
	fwrite(&hInfo, sizeof(char), sizeof(BITMAPINFOHEADER), OutFile);
	fwrite(OutImage, m_Width * m_Height * 3, 1, OutFile);

	fclose(OutFile);
}

