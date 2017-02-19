#include "OverPassSubMesh.h"
#include "OverPassMesh.h"

namespace OverPass
{
	
	SubMesh::SubMesh()
		:parent(0)
		,mMatInitialised(false)
	{

	}
	

	SubMesh::~SubMesh()
	{

	}
	bool SubMesh::isMatInitialised(void) const
	{
		return mMatInitialised;

	}
	void SubMesh::_getRenderOperation(RenderOperation& ro)
	{
		//do something later
	}


}