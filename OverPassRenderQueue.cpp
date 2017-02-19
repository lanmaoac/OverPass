#include "OverPassRenderQueue.h"

#include "OverPassMovableObject.h"
namespace OverPass
{
	RenderQueue::RenderQueue()
	{
		
		mGroups.insert(
			RenderQueueGroupMap::value_type(
				0,
				new RenderQueueGroup(this)
				)
			);
		
		//RenderQueueGroup *tmp=  new RenderQueueGroup(this);
		//mGroups[0] = tmp;
		mDefaultQueueGroup = OVERPASS_RENDER_QUEUE_MAIN;
		mDefaultRenderablePriority = OVERPASS_RENDERABLE_DEFAULT_PRIORITY;
	}
	RenderQueue::~RenderQueue()
	{
		RenderQueueGroupMap::iterator i, iend;
		i = mGroups.begin();
		iend = mGroups.end();
		for (; i != iend; ++i)
		{
			//delete i->second;
		}
		mGroups.clear();
	}
	void RenderQueue::addRenderable(Renderable* pRend, int groupID, int priority)
	{
		RenderQueueGroup* pGroup = getQueueGroup(groupID);
		//something about material tech

		pGroup->addRenderable(pRend);
	}
	void Renderable::clear(bool destroyPassMaps)
	{
	}
	void RenderQueue::addRenderable(Renderable* pRend, int groupID)
	{
		addRenderable(pRend, groupID, mDefaultRenderablePriority);
	}
	void RenderQueue::addRenderable(Renderable* pRend)
	{
		addRenderable(pRend, mDefaultQueueGroup, mDefaultRenderablePriority);
	}
	//-----------------------------------------------------------------------
	int RenderQueue::getDefaultQueueGroup(void) const
	{
		return mDefaultQueueGroup;
	}
	//-----------------------------------------------------------------------
	void RenderQueue::setDefaultQueueGroup(int grp)
	{
		mDefaultQueueGroup = grp;
	}
	//-----------------------------------------------------------------------
	int RenderQueue::getDefaultRenderablePriority(void) const
	{
		return mDefaultRenderablePriority;
	}
	//-----------------------------------------------------------------------
	void RenderQueue::setDefaultRenderablePriority(int priority)
	{
		mDefaultRenderablePriority = priority;
	}
	void RenderQueue::merge(const RenderQueue* rhs)
	{
		//do something 
	}
	void RenderQueue::processVisibleObject(MovableObject* mo)
	{
		if (mo->isVisible())
		{
			mo->_updateRenderQueue(this);
		}
	}
}