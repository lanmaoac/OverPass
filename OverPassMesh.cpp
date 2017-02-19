#include "OverPassMesh.h"
#include "OverPassSubMesh.h"
namespace OverPass
{
	SubMesh* Mesh::createSubMesh(void)
	{
		return new SubMesh();
	}
	SubMesh* Mesh::createSubMesh(const std::string& name)
	{
		return new SubMesh();
	}
}