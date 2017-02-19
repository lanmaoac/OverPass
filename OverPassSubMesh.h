#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassRenderOperation.h"
namespace OverPass
{
	class SubMesh
	{

	public:
		Mesh* parent;
		SubMesh();
		~SubMesh();
		void _getRenderOperation(RenderOperation& rend);
	protected:
		std::string mMaterialName;
		bool mMatInitialised;
	public:
		bool isMatInitialised(void) const;
	};
}