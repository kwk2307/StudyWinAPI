#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    void Load(const wstring& _strFilePath);
    
    HDC GetDC() { return m_dc; }
    UINT GetWidth() { return m_bitInfo.bmWidth; }
    UINT GetHeight() { return m_bitInfo.bmHeight; }
public:
    CTexture();
    ~CTexture();
};

