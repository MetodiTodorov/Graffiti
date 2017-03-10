#pragma once

///////////////////////////////////////////////////////////////////////////////
#include "ImgTask.h"

///////////////////////////////////////////////////////////////////////////////
class HistEqTask : public ImgTask
{
public:
	HistEqTask(wxImage img);
	virtual ~HistEqTask() = default;

	virtual void		Step(int step) override;
	virtual std::string	GetName() const override;

private:
	void					DoEqualization();
	std::map<BYTE, float>	CalcProbability(const std::map<BYTE, int>& count, int pxls);
	std::map<BYTE, float>	DerProbability(const std::map<BYTE, float>& pr);
	std::map<BYTE, BYTE>	GetRemapFunc(const std::map<BYTE, float>& der);
};

///////////////////////////////////////////////////////////////////////////////