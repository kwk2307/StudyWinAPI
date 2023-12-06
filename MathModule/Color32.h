#pragma once
struct Color32 {
public:
	union
	{
		struct
		{
			BYTE B, G, R, A;
		};

		UINT32 ColorValue;
	};
};