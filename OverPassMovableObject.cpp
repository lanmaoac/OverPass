#include "OverPassMovableObject.h"
#include "OverPassSceneNode.h"
#include "OverPassMatrix4.h"
namespace OverPass
{
	MovableObject::MovableObject()
		//:mManager(0)
		: mParentNode(0)
		, mVisible(true)
		, mRenderQueueID(0)
		, mRenderQueuePriority(100)
		, mRenderQueueIDSet(false)
		, mRenderQueuePrioritySet(false)
	{

	}
	MovableObject::MovableObject(const std::string& name)
		:mName(name)
		//, mManager(0)
		, mParentNode(0)
		, mVisible(true)
		, mRenderQueueID(0)
		, mRenderQueuePriority(100)
		, mRenderQueueIDSet(false)
		, mRenderQueuePrioritySet(false)
	{
	}
	MovableObject::~MovableObject()
	{
		if (mParentNode)
		{
			//detachAllObject
			//static_cast<SceneNode*>(mParentNode)->detachObject(this);
		}
	}
	
	void MovableObject::_notifyAttached(Node* parent)
	{
		mParentNode = parent;
	}
	Node* MovableObject::getParent(void) const
	{
		return mParentNode;
	}
	SceneNode* MovableObject::getParentSceneNode(void) const
	{
		return static_cast<SceneNode*>(mParentNode);
	}

	bool MovableObject::_isAttached(void) const
	{
		return mParentNode != 0;
	}
	bool MovableObject::isInScene(void) const
	{
		if (mParentNode)
		{
			SceneNode* sn = static_cast<SceneNode*>(mParentNode);
			return sn->isInSceneGraph();
		}
		else
		{
			return false;
		}
	}

	void MovableObject::setVisible(bool visible)
	{
		mVisible = visible;
	}
	void MovableObject::setRenderQueueGroup(int queueID)
	{
		mRenderQueueID = queueID;
		mRenderQueueIDSet = true;
	}
	void MovableObject::setRenderQueueGroupAndPriority(int queueID, int priority)
	{
		setRenderQueueGroup(queueID);
		mRenderQueuePriority = priority;
		mRenderQueuePrioritySet = true;
	}
	const Matrix4& MovableObject::_getParentNodeFullTransform() const
	{
		if (mParentNode)
		{
			return mParentNode->_getFullTransform();
		}
		return Matrix4::IDENTITY;
	}
	bool MovableObject::isAttached(void) const
	{
		return (mParentNode != 0);

	}
}