#pragma once

#include "stdafx.h";

void ImageDataFromBmp(char *filename, BYTE **curBuf, int *m_Width, int *m_Height, BITMAPFILEHEADER *hf, BITMAPINFOHEADER *hInfo);
void Bmp2Raw(BYTE *BmpBuf, int m_Width, int m_Height);
void Y2RGB(BYTE *YBuf, BYTE *RGBBuf, int m_Width, int m_Height);
void MakeBMPFile_xx(char *FileName, BYTE *OutImage, BITMAPFILEHEADER hf, BITMAPINFOHEADER hInfo, int w, int h);