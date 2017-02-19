#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassRenderable.h"

namespace OverPass
{
	class QueueRenderableCollection
	{
	public:
		enum PrganisationMode
		{
			/// Group by pass
			OM_PASS_GROUP = 1,
			/// Sort descending camera distance
			OM_SORT_DESCENDING = 2,
			/** Sort ascending camera distance
			Note value overlaps with descending since both use same sort
			*/
			OM_SORT_ASCENDING = 6

		};
		typedef std::vector< Renderable* >  RenderableList;
	public:
		RenderableList mRenderableList;
		QueueRenderableCollection();
		~QueueRenderableCollection();
		void clear(void);
		void addRenderable(Renderable* rend);
		//sort(const Camera* cam);
		RenderableList getRenderableListForTest(void)
		{
			return mRenderableList;
		}

		//void merge(const const QueueRenderableCollection& rhs);

	};

	class RenderPriorityGroup
	{
	protected:
		RenderQueueGroup* mParent;
		QueueRenderableCollection mSolidBasic;
		QueueRenderableCollection mTransparentsUnsorted;
		QueueRenderableCollection mTransparents;
		void addSolidRenderable(Renderable* rend);
		void addUnsortedTransparentRenderable(Renderable* rend);
		void addTransparentRenderable(Renderable* rend);
	public:
		RenderPriorityGroup(RenderQueueGroup* parent);
		RenderPriorityGroup() {};
		~RenderPriorityGroup() {};
		 QueueRenderableCollection getSolidBasic(void) const
		{
			return mSolidBasic;
		}
		 QueueRenderableCollection getTransparentsUnsorted(void) const
		{
			return mTransparentsUnsorted;
		}
		 QueueRenderableCollection getTransparents(void) const
		{
			return mTransparents;
		}
		void addRenderable(Renderable* pRend);
		//void sort(const Camera* cam);
		void clear(void);
		void sort(void);
		//void merge(const RenderPriorityGroup* rhs);

	};


	class RenderQueueGroup
	{
	public:
		typedef std::map<int, RenderPriorityGroup*, std::less<int> > PriorityMap;
	protected:
		RenderQueue* mParent;
		PriorityMap mPriorityGroup;
	public:
		
		RenderQueueGroup(RenderQueue* parent)	
		{
			mParent = parent;
			RenderPriorityGroup* pPriorityGroup = new RenderPriorityGroup(this);
			mPriorityGroup.insert(PriorityMap::value_type(0, pPriorityGroup));
		}
		
		RenderQueueGroup()
		{
			//mParent = parent;
			RenderPriorityGroup* pPriorityGroup = new RenderPriorityGroup();
			mPriorityGroup.insert(PriorityMap::value_type(0, pPriorityGroup));
		}
		~RenderQueueGroup()
		{
			PriorityMap::iterator i;
			for (i = mPriorityGroup.begin(); i != mPriorityGroup.end(); ++i)
			{
				//delete i->sceond;
				//do something
			}
		}
		void addRenderable(Renderable* pRend, int priority=0)
		{
			PriorityMap::iterator i = mPriorityGroup.find(priority);
			RenderPriorityGroup* pPriorityGroup;
			if (i == mPriorityGroup.end())
			{
				//use new do something after
				pPriorityGroup = new RenderPriorityGroup();
				mPriorityGroup.insert(PriorityMap::value_type(priority, pPriorityGroup));
			}
			else
			{
				pPriorityGroup = i->second;
			}
			pPriorityGroup->addRenderable(pRend);
		}
		void clear(bool destroy = false)
		{
			PriorityMap::iterator i, iend;
			iend = mPriorityGroup.end();
			for (i = mPriorityGroup.begin(); i != iend; i++)
			{
				if (destroy)
				{
					//deletei->second;
				}
				else
					i->second->clear();
			}
			if (destroy)
				mPriorityGroup.clear();
		}
		RenderPriorityGroup* getPriorityGroupForTest(void)
		{
			return mPriorityGroup[0];
		}

	};
}