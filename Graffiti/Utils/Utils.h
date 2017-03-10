#pragma once

///////////////////////////////////////////////////////////////////////////////
wxBitmapType PathToBmpType(const wxString& path);

std::vector<concurrency::graphics::float_4> ImgToFloat4(const wxImage& img);
void Float4ToImg(const std::vector<concurrency::graphics::float_4>& from, wxImage& to);

std::vector<unsigned> ImgToARGB(const wxImage& img);
void ARGBToImg(const std::vector<unsigned>& from, wxImage& to);

BYTE GetAlpha(unsigned argb);
BYTE GetRed(unsigned argb);
BYTE GetGreen(unsigned argb);
BYTE GetBlue(unsigned argb);

void SetAlpha(BYTE alpha, unsigned& argb);
void SetRed(BYTE red, unsigned& argb);
void SetGreen(BYTE green, unsigned& argb);
void SetBlue(BYTE blue, unsigned& argb);

///////////////////////////////////////////////////////////////////////////////

