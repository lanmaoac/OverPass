#include "OverPassSubEntity.h"
#include "OverPassEntity.h"

namespace OverPass
{
	SubEntity::SubEntity(Entity* parent,SubMesh* subMeshBasis)
		:Renderable()
		, mParentEntity(parent)
		,mSubMesh(subMeshBasis)
	{
		mVisible = true;
		mRenderQueueID = 0;
		mRenderQueueIDSet = false;
		mRenderQueuePriority = false;
	}

	SubEntity::~SubEntity()
	{
		//delect something
	}
	SubMesh* SubEntity::getSubMesh(void)
	{
		return mSubMesh;
	}
	void SubEntity::getWorldTransforms(Matrix4* xform) const
	{
		*xform = mParentEntity->_getParentNodeFullTransform();
	}
	void SubEntity::setVisible(bool visible)
	{
		mVisible = visible;
	}
	bool SubEntity::isVisible(void) const
	{
		return mVisible;
	}
	//-----------------------------------------------------------------------
	void SubEntity::setRenderQueueGroup(int queueID)
	{
		mRenderQueueIDSet = true;
		mRenderQueueID = queueID;
	}
	//-----------------------------------------------------------------------
	void SubEntity::setRenderQueueGroupAndPriority(int queueID, int priority)
	{
		setRenderQueueGroup(queueID);
		mRenderQueuePrioritySet = true;
		mRenderQueuePriority = priority;
	}
	//-----------------------------------------------------------------------
	int SubEntity::getRenderQueueGroup(void) const
	{
		return mRenderQueueID;
	}
	//-----------------------------------------------------------------------
	int SubEntity::getRenderQueuePriority(void) const
	{
		return mRenderQueuePriority;
	}
	//-----------------------------------------------------------------------
	bool SubEntity::isRenderQueueGroupSet(void) const
	{
		return mRenderQueueIDSet;
	}
	//-----------------------------------------------------------------------
	bool SubEntity::isRenderQueuePrioritySet(void) const
	{
		return mRenderQueuePrioritySet;
	}
	//-----------------------------------------------------------------------

	void SubEntity::getRenderOperation(RenderOperation& op)
	{
		
	}
	//----------
}