#include "OverPassEntity.h"

#include "OverPassSubEntity.h"
#include "OverPassSceneNode.h"
#include "OverPassSceneManager.h"

namespace OverPass
{
	Entity::Entity()
		:mInitialised(false)
	{
	}
	Entity::Entity(const std::string& name, const std::string& mesh) :
		MovableObject(name)
	{
		_initialise();
	}
	void Entity::_initialise(bool forceReinitialise)
	{
		if(forceReinitialise)
		_deinitialise();
		if (mInitialised)
			return;
		mMesh->load();
		if (!mMesh->isLoaded())
			return;
		buildSubEntityList(mMesh, &mSubEntityList);
		// Update of bounds of the parent SceneNode, if Entity already attached
		// this can happen if Mesh is loaded in background or after reinitialisation
		if (mParentNode)
		{
			getParentSceneNode()->needUpdate();
		}

		mInitialised = true;

	}

	void Entity::_deinitialise(void)
	{
		if (!mInitialised)
			return;
		SubEntityList::iterator li, liend;
		liend = mSubEntityList.end();
		for (li = mSubEntityList.begin(); li != liend; ++li)
		{
			//delete *li
		}
		mSubEntityList.clear();
	}
	Entity::~Entity()
	{
		_deinitialise();
	}
	const Mesh* Entity::getMesh(void) const
	{
		return mMesh;
	}
	SubEntity* Entity::getSubEntity(int index) const
	{
		if (index > mSubEntityList.size())
		{
			//hehe
		}
		else
		{
			return mSubEntityList[index];
		}
	}
	SubEntity *Entity::getSubEntity(const std::string& name) const
	{
		int index = mMesh->_getSubMeshIndex(name);
		return getSubEntity(index);
	}
	int Entity::getNumSubEntities(void) const
	{
		return static_cast<int>(mSubEntityList.size());
	}
	
	Entity* Entity::clone(const std::string& newName) const
	{  
		
		if (!mManager)
		{
			//hehe
		}
		Entity *newEnt = mManager->createEntity(newName, getMesh()->getName());
		if (mInitialised)
		{
			//setMaterial
		}
		return newEnt;
	}
	
	void Entity::_updateRenderQueue(RenderQueue* queue)
	{
		if (!mInitialised)
			return;
	//mesh lod
		SubEntityList::iterator i, iend;
		iend = mSubEntityList.end();
		for (i = mSubEntityList.begin(); i != iend; ++i)
		{
			if ((*i)->isVisible())
			{
				if ((*i)->isRenderQueuePrioritySet())
				{
					queue->addRenderable(*i, (*i)->getRenderQueueGroup(), (*i)->getRenderQueuePriority());
				}
				else if ((*i)->isRenderQueueGroupSet())
				{
					queue->addRenderable(*i, (*i)->getRenderQueueGroup());
				}
				else if (mRenderQueuePrioritySet)
				{
					queue->addRenderable(*i, mRenderQueueID, mRenderQueuePriority);
				}
				else if (mRenderQueueIDSet)
				{
					queue->addRenderable(*i, mRenderQueueID);
				}
				else
				{
					queue->addRenderable(*i);
				}
			}
		}

	}

	void Entity::buildSubEntityList(Mesh* mesh, SubEntityList * sunlist)
	{
		int i, numSubMeshes;
		numSubMeshes = 1;
		//numSubMeshes = mesh->getNumSubMeshes();
		for (i = 0; i < numSubMeshes; i++)
		{
			SubMesh* subMesh = mesh->getSubMesh(i);
			SubEntity* subEnt = new SubEntity(this, subMesh);
			sunlist->push_back(subEnt);
		}

	}

	void Entity::setRenderQueueGroup(int queueID)
	{
		MovableObject::setRenderQueueGroup(queueID);

		//meshLOD
	}
	void Entity::setRenderQueueGroupAndPriority(int queueID, int priority)
	{
		MovableObject::setRenderQueueGroupAndPriority(queueID, priority);
	}




}