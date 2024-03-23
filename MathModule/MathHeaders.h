#pragma once

typedef unsigned char		BYTE;		// 부호 없는 8비트
typedef unsigned int		UINT32;		// 부호 없는 32비트
typedef signed long long	INT64;	// 부호 있는 64비트.

#define SMALL_NUMBER		(1.e-8f)


#include <cassert>

#include <math.h>

#include <intrin.h>

#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <algorithm>

#include "MathUtil.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Plane.h"
#include "Box.h"
#include "Circle.h"
#include "Sphere.h"

#include "Frustum.h"

#include "Rotator.h"

#include "Matrix3.h"
#include "Matrix4.h"

#include "Color.h"

#include "ScreenPoint.h"

