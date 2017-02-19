#include "OverPassRenderQueueSortingGrouping.h"

namespace OverPass
{
	
	RenderPriorityGroup::RenderPriorityGroup(RenderQueueGroup* parent)
	{
		mParent = parent;
		 mSolidBasic = QueueRenderableCollection();
		 mTransparentsUnsorted= QueueRenderableCollection();
		 mTransparents= QueueRenderableCollection();
	}
	

	void RenderPriorityGroup::addRenderable(Renderable* rend)
	{
		addSolidRenderable(rend);
	}
	void RenderPriorityGroup::addSolidRenderable(Renderable* rend)
	{
		QueueRenderableCollection* collection;
		collection = &mSolidBasic;
		collection->addRenderable(rend);
	}
	void RenderPriorityGroup::addTransparentRenderable(Renderable* rend)
	{
		mTransparentsUnsorted.addRenderable(rend);
	}
	void RenderPriorityGroup::addUnsortedTransparentRenderable(Renderable* rend)
	{
		mTransparents.addRenderable(rend);
	}
	void RenderPriorityGroup::clear(void)
	{
		mSolidBasic.clear();
		mTransparentsUnsorted.clear();
		mTransparents.clear();
	}
	void RenderPriorityGroup::sort()
	{
		//do something here later
	}


	QueueRenderableCollection::QueueRenderableCollection(void)
	{

	}
	QueueRenderableCollection::~QueueRenderableCollection(void)
	{

	}
	void QueueRenderableCollection::clear(void)
	{

	}
	void QueueRenderableCollection::addRenderable(Renderable* rend)
	{
		mRenderableList.push_back(rend);
	}


	
}