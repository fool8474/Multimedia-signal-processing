#include <math.h>
#include "ImageProcess.h"

void ImageProcess::SetImageProcess(BYTE *ICyBuf, BYTE *ICbBuf, BYTE *ICrBuf, BYTE *IYBuf, BYTE *IRBuf, BYTE *IGBuf, BYTE *IBBuf, BYTE *IOutBuf, BYTE *IRGBBuf, BYTE *IIpImg, int Im_Width, int Im_Height) {
	
	CyBuf = ICyBuf;
	CbBuf = ICbBuf;
	CrBuf = ICrBuf;
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

void ImageProcess::ToBinaryImage(byte dividePoint) {
	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			currentY = *(YBuf + i * m_Width + j);
			if (currentY > dividePoint) currentY = 255;
			else currentY = 0;

			*(OutBuf + i * m_Width + j) = currentY;
		}
	}
}

void ImageProcess::ChangeColorInRange(int xStartPoint, int xEndPoint, int yStartPoint, int yEndPoint, BYTE R, BYTE G, BYTE B) {
	for (i = xStartPoint; i < xEndPoint; i++) {
		for (j = yStartPoint; j < yEndPoint; j++) {
			*(RGBBuf + (i)* m_Width * 3 + 3 * (j)+0) = R;
			*(RGBBuf + (i)* m_Width * 3 + 3 * (j)+1) = G;
			*(RGBBuf + (i)* m_Width * 3 + 3 * (j)+2) = B;
		}
	}
}

void ImageProcess::MosaicImage(int mosaicSize) {
	int sum = 0;

	for (i = 0; i < m_Height; i += mosaicSize) {
		for (j = 0; j < m_Width; j += mosaicSize) {
			for (k = i; k < i + mosaicSize; k++) {
				for (l = j; l < j + mosaicSize; l++) {
					sum += *(YBuf + k * m_Width + l);
					//printf("%d", &sum);
				}
			}

			int avg = int(sum / (mosaicSize * mosaicSize));

			for (k = i; k < i + mosaicSize; k++) {
				for (l = j; l < j + mosaicSize; l++) {
					*(OutBuf + k * m_Width + l) = BYTE(avg);
				}
			}

			sum = 0;
		}
	}
}

void ImageProcess::ToYCbCr() {
	BYTE r, g, b;

	double cbf, crf, yf;

	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			r = *(RBuf + i * m_Width + j);
			g = *(GBuf + i * m_Width + j);
			b = *(BBuf + i * m_Width + j);

			yf = (0.299*r) + (0.587*g) + 128 + (0.114 * b) + 128;
			*(CyBuf + i * m_Width + j) = (BYTE)yf;
			cbf = (-0.16874*r) + (-0.3313*g) + 128 + (0.500 * b) + 128;
			*(CbBuf + i * m_Width + j) = (BYTE)cbf;
			crf = (0.500*r) + (-0.4187*g) + 128 + (-0.0813 * b) + 128;
			*(CrBuf + i * m_Width + j) = (BYTE)crf;
		}
	}
}

void ImageProcess::ConvGradient(double changeNum) {
	BYTE rightMask, leftMask;
	int gradient;

	for (i = 0; i < m_Height - 1; i++) {
		for (j = 0; j < m_Width; j++) {
			rightMask = *(YBuf + i * m_Width + j + 1);
			leftMask = *(YBuf + i * m_Width + j);

			gradient = 1 * rightMask + (-1) * leftMask;
			gradient = abs(gradient) * 2;

			if (gradient > 255)
				gradient = 255;

			*(OutBuf + i * m_Width + j + 1) = abs(gradient);
		}
	}
}

void ImageProcess::ConvHighPass() {
	int highPass[3][3] = { {-1,-1,-1},{-1,9,-1},{-1,-1,-1} };
	CalFilter3by3(highPass);
}

void ImageProcess::ConvEmbossing() {
	int result;
	int emBoss[3][3] = { {0,0,1},{0,0,0},{-1,0,0} };
	CalFilter3by3(emBoss);
	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			result = *(OutBuf + i * m_Width + j) + 128;
			if (result > 255) result = 255;
			*(OutBuf + i * m_Width + j) = result;
		}
	}
}

void ImageProcess::ConvSobelEdge(int edgePoint) {
	long fx, fy;
	long sum, edge;
	int sobelX[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };
	int sobelY[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	
	for (i = 1; i < m_Height - 1; i++) {
		for (j = 1; j < m_Width - 1; j++) {

			fx = 0; fy = 0;

			for (k = -1; k <= 1; k++) {
				for (l = -1; l <= 1; l++) {
					fx += *(YBuf + (i + k)*m_Width + (j + l)) * sobelX[k + 1][l + 1];
					fy += *(YBuf + (i + k)*m_Width + (j + l)) * sobelY[k + 1][l + 1];
				}
			}

			fx *= fx;
			fy *= fy;

			sum = abs(fx) + abs(fy);
			edge = sqrt(sum);

			if (edge > edgePoint)
				edge = 255;

			else
				edge = 0;

			*(OutBuf + i * m_Width + j) = edge;
		}
	}
}

void ImageProcess::CalFilter3by3(int filter[3][3]) {
	int result;

	for (i = 1; i < m_Height - 1; i++) {
		for (j = 1; j < m_Width - 1; j++) {

			result = 0;

			for (k = -1; k <= 1; k++) {
				for (l = -1; l <= 1; l++) {
					result += *(YBuf + (i + k)*m_Width + (j + l)) * filter[k + 1][l + 1];
				}
			}

			if (result > 255)
				result = 255;

			else if (result < 0)
				result = 0;

			*(OutBuf + i * m_Width + j) = result;
		}
	}
}

void ImageProcess::BinaryByHistogram(double binaryBoundary) {
	double hist[256];
	BYTE current;
	for (i = 0; i < 256; i++) hist[i] = 0;

	for (i = 0; i < m_Width * m_Height; i++) {
		current = *(YBuf + i);
		hist[current] += 1;
	}

	for (i = 0; i < 256; i++) {
		hist[i] = hist[i] / (m_Width * m_Height);
		printf("%f\n", hist[i]);
	}


	for (i = 0; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			current = *(YBuf + i * m_Width + j);
			if (hist[current] > binaryBoundary)
				current = (BYTE)255;
			else current = (BYTE)0;

			*(OutBuf + i * m_Width + j) = (BYTE)current;
		}
	}
}

void ImageProcess::GetDiffVideo() {
	for (i = 1; i < m_Height; i++) {
		for (j = 1; j < m_Width; j++) {
			int A = *(YBuf + (i)*m_Width + j - 1);
			int C = *(YBuf + (i-1)*m_Width + j);
			int x = *(YBuf + (i)*m_Width + j);

			int diff = x - (A + C) / 2;
			diff += 30;

			if (diff > 255) {
				diff = 255;
			}

			else if (diff < 0) {
				diff = 0;
			}

			*(OutBuf + i * m_Width + j) = diff;
		}
	}
}

void ImageProcess::GetCorrelation() {
	for (i = 1; i < m_Height; i++) {
		for (j = 0; j < m_Width; j++) {
			double rightPix = *(YBuf + i * m_Width + j) / 255.0;
			double leftPix = *(YBuf + (i - 1) * m_Width + j) / 255.0;
			double diff = rightPix - leftPix;
			if (diff < 0) {
				diff = -diff;
			}
			double result = 1 / (1 + diff);

			result *= 255;

			if (result > 255) {
				result = 255;
			}

			else if (result < 0) {
				result = 0;
			}

			*(OutBuf + i * m_Width + j) = int(result);
		}
	}
}

void ImageProcess::GetDiffVideoWith2Image(BYTE* YBuf2) {

	for (i = 0; i < m_Width; i++) {
		for (j = 0; j < m_Height; j++) {
		
			int result = *(YBuf + i * m_Width + j) - *(YBuf2 + i * m_Width + j);	
			if (result < 0) { result = -result; }

			*(OutBuf + i * m_Width + j) = (BYTE)result;
		}
	}
}

void ImageProcess::InputWatermark(BYTE* YBuf2) {
	for (i = 0; i < m_Width; i++) {
		for (j = 0; j < m_Height; j++) {
			int curWatermark = *(YBuf2 + i * m_Width + j);
			if (curWatermark >= 128) {
				*(YBuf2 + i * m_Width + j) = 255;
			}

			else {
				*(YBuf2 + i * m_Width + j) = 0;
			}

			curWatermark = *(YBuf + i * m_Width + j);
			curWatermark = curWatermark & 0x7f; //in light case, curWatermark&0xFE;
			curWatermark = curWatermark + (unsigned char)(*(YBuf2 + i * m_Width + j) / 255 * 128); //in light case, do /255.
			*(OutBuf + i * m_Width + j) = curWatermark;
		}
	}
}

void ImageProcess::ExtractWatermark() {
	for (i = 0; i < m_Width; i++) {
		for (j = 0; j < m_Height; j++) {
			int curWatermark = *(OutBuf + i * m_Width + j);
			curWatermark = (curWatermark & 0x80); //in light case, curWatermark&0x01 * 255
			if (curWatermark > 50) {
				curWatermark = 255;
			}

			*(OutBuf + i * m_Width + j) = curWatermark;
		}
	}
}

void ImageProcess::GetIrisRange() {

	int curStartX = 240;
	int curStartY = 240; // this Variable choosed by Image's Iris Center.
	int curRange = 8; // 8*8

	double curResult = 0;
	double T = 0;
	double YSquareAverage = 0;
	int count = 0;

	while (true) {
		curResult = 0;

		for (j = curStartY; j < curStartY + curRange; j++) {
			curResult += *(YBuf + curStartX * m_Width + j);
			curResult += *(YBuf + (curStartX + curRange) * m_Width + j);
		}

		for (i = curStartX; i < curStartX + curRange; i++) {
			curResult += *(YBuf + i * m_Width + curStartY);
			curResult += *(YBuf + i * m_Width + curStartY + curRange);
		}
		//check square's pixels sum which placed edge

		curResult /= (curRange * 4 - 4);

		if (count != 0) {
			T = curResult - YSquareAverage;
			if (T < 0) T = -T;
		}

		else {
			YSquareAverage = curResult;
		}

		curRange += 2;
		curStartX -= 1;
		curStartY -= 1;

		printf("curResult : %f, curT : %f\n", curResult, T);
		
		count += 1;

		if (T > 10) {
			break;
		}

		if (count > 200) {
			break;
		}
	}

	// copy YBuf to Outbuf
	for (i = 0; i < m_Width; i++) {
		for (j = 0; j < m_Height; j++) {
			*(OutBuf + i * m_Width + j) = *(YBuf + i * m_Width + j);
		}
	}

	// to Draw Iris Edge
	for (j = curStartY; j < curStartY + curRange; j++) {
		*(OutBuf + curStartX * m_Width + j) = 255;
		*(OutBuf + (curStartX + curRange) * m_Width + j) = 255;
	}
	for (i = curStartX; i < curStartX + curRange; i++) {
		*(OutBuf + i * m_Width + curStartY) = 255;
		*(OutBuf + i * m_Width + curStartY + curRange) = 255;
	}
}