#pragma once

class RendererInterface {
public:
	virtual bool Init(const ScreenPoint& InSize) = 0;
};