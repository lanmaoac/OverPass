#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassMovableObject.h"
#include "OverPassMatrix4.h"
#include "OverPassMesh.h"
#include "OverPassSubEntity.h"
#include "OverPassRenderQueue.h"
namespace OverPass
{
	class Entity :public MovableObject
	{
	public:
		typedef std::set<Entity* > EntitySet;
		typedef std::vector< SubEntity* > SubEntityList;
	protected:
		
		Mesh* mMesh;
		SubEntityList mSubEntityList;
		bool mInitialised;
		Matrix4 mLastParentXform;
		void buildSubEntityList(Mesh* mesh, SubEntityList* sublist);
	public:
		typedef std::map<std::string, MovableObject*> ChildOnjectList;
	protected:
		ChildOnjectList mChildObjectList;
	public:
		Entity();
		Entity(const std::string& name, const std::string& mesh);
		~Entity();
		const Mesh* getMesh(void) const;
		SubEntity* getSubEntity(int index) const;
		SubEntity* getSubEntity(const std::string& name) const;
		int getNumSubEntities(void) const;
		const SubEntityList& getSubEntities()const {
			return mSubEntityList;
		}
		Entity* clone(const std::string& newName) const;
		void setRenderQueueGroup(int queueID);
		void setRenderQueueGroupAndPriority(int queueID,int priority);


		void _updateRenderQueue(RenderQueue* queue);
		bool isInitialised(void) const { return mInitialised; }
		void _initialise(bool forceReinitialise = false);
		/** Tear down the internal structures of this Entity, rendering it uninitialised. */
		void _deinitialise(void);


	};
}