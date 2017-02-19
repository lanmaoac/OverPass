#pragma once

#include "OverPassPrerequisites.h"
#include "OverPassSubMesh.h"

namespace OverPass
{
	class Mesh
	{

	public:
		int o;
		//typedef std::vector<SubMesh*> SubMeshList;
	protected:
		int count;
		std::vector< SubMesh* > mSubMeshList;
	public:
		
		Mesh();
		~Mesh();

		SubMesh* createSubMesh(void);
		SubMesh* createSubMesh(const std::string& name);
		int getNumSubMeshes(void) const
		{
			return count;
			//return mSubMeshList.size();
		}
		SubMesh* getSubMesh(int index) const
		{
			return new SubMesh();
			//return mSubMeshList[index];
		}
		bool isLoaded(void) const
		{
			return true;
		}
		void load(void) const
		{

		}
		std::string getName(void) const
		{
			std::string hehe = "hehe";
			return hehe;
		}
		int _getSubMeshIndex(const std::string& name)
		{
			return count++;
		}

	};
}
