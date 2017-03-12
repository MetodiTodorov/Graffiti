#include <stdafx.h>
#include "HistEqTask.h"

#include <windows.h>
#include <amp.h>

///////////////////////////////////////////////////////////////////////////////
HistEqTask::HistEqTask(wxImage img)
	: ImgTask(img, 1)
{
}

///////////////////////////////////////////////////////////////////////////////
void HistEqTask::Step(int step)
{
	DoEqualization();
}

///////////////////////////////////////////////////////////////////////////////
std::string	HistEqTask::GetName() const
{
	return "HistEq";
}

///////////////////////////////////////////////////////////////////////////////
// http://fourier.eng.hmc.edu/e161/lectures/contrast_transform/node2.html
void HistEqTask::DoEqualization()
{
	auto rgb = src_.GetData();
	auto pixels = src_.GetWidth() * src_.GetHeight();
	auto bytes = pixels * 3;
	
	std::map<BYTE, int> rCount, gCount, bCount;
	for (int i = 0; i < bytes; i++)
	{
		if ((i % 3) == 0)
			rCount[rgb[i]]++;
		else if ((i % 3) == 1)
			gCount[rgb[i]]++;
		else
			bCount[rgb[i]]++;
	}

	auto hRed = CalcProbability(rCount, pixels);
	auto yRed = DerProbability(hRed);
	auto remapRed = GetRemapFunc(yRed);

	auto hGreen = CalcProbability(gCount, pixels);
	auto yGreen = DerProbability(hGreen);
	auto remapGreen = GetRemapFunc(yGreen);

	auto hBlue = CalcProbability(bCount, pixels);
	auto yBlue = DerProbability(hBlue);
	auto remapBlue = GetRemapFunc(yBlue);
	
	auto rgbNew = new BYTE[bytes];
	for (int i = 0; i < bytes; i++)
	{
		if (i % 3 == 0)
			rgbNew[i] = remapRed[rgb[i]];
		else if (i % 3 == 1)
			rgbNew[i] = remapGreen[rgb[i]];
		else
			rgbNew[i] = remapBlue[rgb[i]];
	}
	dst_.SetData(rgbNew);
}

///////////////////////////////////////////////////////////////////////////////
std::map<BYTE, float> HistEqTask::CalcProbability(const std::map<BYTE, int>& cnt, int pxls)
{
	std::map<BYTE, float> pr;
	for (auto it : cnt)
	{
		pr[it.first] = it.second / float(pxls);
	}		

	return pr;
}

///////////////////////////////////////////////////////////////////////////////
std::map<BYTE, float> HistEqTask::DerProbability(const std::map<BYTE, float>& pr)
{
	std::map<BYTE, float> yPrim;
	float prev = 0.0f;
	for (auto it : pr)
	{
		prev += it.second;
		yPrim[it.first] = prev;
	}		

	return yPrim;
}

///////////////////////////////////////////////////////////////////////////////
std::map<BYTE, BYTE> HistEqTask::GetRemapFunc(const std::map<BYTE, float>& yPrim)
{
	std::map<BYTE, BYTE> remap;
	for (auto it : yPrim)
	{
		remap[it.first] = static_cast<BYTE>(it.second * 255);
	}
	return remap;
}

///////////////////////////////////////////////////////////////////////////////