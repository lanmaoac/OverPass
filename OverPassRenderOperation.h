#pragma once

#include "OverPassPrerequisites.h"
namespace OverPass
{
	class RenderOperation
	{
	public:
		bool useIndex;
		bool teaOrBox;
		enum meshType
		{
			TEAPOT = 1,
			BOX = 2,
		};
		meshType mMeshType;
		RenderOperation() :
			useIndex(true),
			teaOrBox(false)
		{
			mMeshType = TEAPOT;
		}
		~RenderOperation()
		{

		}
	};
}
