#pragma once

#ifndef __Matrix3_H__
#define __Matrix3_H__

#include "OverPassPrerequisites.h"

#include "OverPassVector3.h"

namespace OverPass
{
	
	class  Matrix3
	{
	public:
		float arr[3][3];
		Matrix3()
		{
			arr[0][0] = 1.0;
		}
		~Matrix3()
		{
		}
	};
}
#endif
