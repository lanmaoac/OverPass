#include "OverPassSceneManager.h"
#include "OverPassEntity.h"
#include "OverPassNode.h"
#include "OverPassSubEntity.h"
#include "OverPassSceneNode.h"
#include "OverPassRenderQueue.h"
#include "OverPassRenderQueueSortingGrouping.h"
#include "OverPassRenderOperation.h"
namespace OverPass
{
	SceneManager::SceneManager(const std::string& name) :
		mName(name),
		mRenderQueue(0),
		mSceneRoot(0),
		mSkyPlaneEntity(0),
		mSkyPlaneNode(0),
		mSkyPlaneEnabled(false)
	{
		//do something 
		//set rendersystem
	}

	SceneManager::~SceneManager()
	{
		clearScene();
		//delete mSceneRoot;
		//delete mRenderQueue;
	}
	RenderQueue* SceneManager::getRenderQueue(void)
	{
		if (!mRenderQueue)
			initRenderQueue();
		return mRenderQueue;
	}
	void SceneManager::initRenderQueue(void)
	{
		mRenderQueue = new RenderQueue();
	}

	Entity* SceneManager::createEntity(const std::string& entityName, PrefabType pType)
	{
		std::string tmp1 = "Prefab_Plane";
		std::string tmp2 = "Prefab_Cube";
		std::string tmp3 = "Prefab_Sphere";
		switch (pType)
		{
		case PT_PLANE:
			
			return createEntity(entityName,tmp1 );
		case PT_CUBE:
		
			return createEntity(entityName, tmp2);
		case PT_SPHERE:
			
			return createEntity(entityName, tmp3);
			break;
		}
	}
	Entity* SceneManager::createEntity(const std::string& entityName, const std::string& meshName)
	{
   
		return new Entity(entityName, meshName);
	}

	void SceneManager::clearScene(void)
	{
		getRootSceneNode()->removeAllChildren();
		getRootSceneNode()->detachAllObjects();
		mSceneNodes.clear();

		if (mRenderQueue)
			mRenderQueue->clear(true);
	}

	SceneNode* SceneManager::createSceneNodeImpl(void)
	{
		return new SceneNode(this);
	}
	SceneNode* SceneManager::createSceneNodeImpl(const std::string& name)
	{
		return new SceneNode(this, name);
	}

	SceneNode* SceneManager::createSceneNode(void)
	{
		SceneNode* sn = createSceneNodeImpl();
		mSceneNodes[sn->getName()] = sn;
		return sn;
	}
	SceneNode* SceneManager::createSceneNode(const std::string& name)
	{
		if (mSceneNodes.find(name) != mSceneNodes.end())
		{
			//hehe
		}
		SceneNode* sn = createSceneNodeImpl(name);
		mSceneNodes[name] = sn;
		return sn;
	}

	SceneNode* SceneManager::getRootSceneNode(void)
	{
		if (!mSceneRoot)
		{
			std::string rootName = "OverPassSceneRoot";
				mSceneRoot = createSceneNodeImpl(rootName);
				mSceneRoot->_notifyRootNode();
		}
		return mSceneRoot;
	}


	SceneNode* SceneManager::getSceneNode(const std::string& name) const
	{
		SceneNodeList::const_iterator i = mSceneNodes.find(name);
		if (i == mSceneNodes.end())
		{
			//hehe
		}
		return i->second;
	}
	void SceneManager::prepareRenderQueue(void)
	{
		RenderQueue *q = getRenderQueue();
		q->clear();
	}

	void SceneManager::_renderScene()
	{
		//mutex 场景管理
		{
			//更新场景 计算transform
			{
				_updateSceneGraph();
			}
			//prepare render queue for receiving new objects
			{
				prepareRenderQueue();
			}
			//找到 所有可见物体
			{
				_findVisibleObjects();
			}
		}
		mDestRenderSystem->_beginGeometryCount();
		mDestRenderSystem->_beginFrame();
		//mDestRenderSystem->_setProjectionMatrix();
		//render Content
		{
			_renderVisibleObjects();
		}
		mDestRenderSystem->_endFrame();
	}

	void SceneManager::_setDestinationRenderSystem(RenderSystem* sys)
	{
		mDestRenderSystem = sys;
	}


	void SceneManager::_updateSceneGraph()
	{
		getRootSceneNode()->_update(true, false);
	}
	void SceneManager::_findVisibleObjects()
	{
		getRootSceneNode()->_findVisibleObjects(getRenderQueue());
	}

	void SceneManager::_renderVisibleObjects(void)
	{
		//先用默认的实现
		//do something later
		renderVisibleObjectsDefaultSequence();
	}

	void SceneManager::renderVisibleObjectsDefaultSequence(void)
	{

		RenderQueueGroup* group = getRenderQueue()->getRenderQueueGroupForTest();
		_renderQueueGroupObjects(group);
	}

	void SceneManager::_renderQueueGroupObjects(RenderQueueGroup* pGroup)
	{
		//do something later
		//like shadow light texture
		renderBasicGroupObjects(pGroup);

	}
	void SceneManager::renderBasicGroupObjects(RenderQueueGroup* pGroup)
	{
		//basic  render loop
		//iterate through priority
		RenderPriorityGroup* pPriorityGroup = pGroup->getPriorityGroupForTest();
		pPriorityGroup->sort();

		renderObjects(pPriorityGroup->getSolidBasic());
		renderObjects(pPriorityGroup->getTransparentsUnsorted());
		renderObjects(pPriorityGroup->getTransparents());
	}
	void SceneManager::renderObjects( QueueRenderableCollection objs)
	{
		QueueRenderableCollection::RenderableList renderList = objs.getRenderableListForTest();
		QueueRenderableCollection::RenderableList::iterator i, iend;
		iend = renderList.end();
		for ( i = renderList.begin(); i != iend; i++)
		{
			Renderable* rend= *i;
			renderSingleObject(rend);
		}
	}

	void SceneManager::renderSingleObject(Renderable* ren)
	{
		_issueRenderOp(ren);
	}

	void SceneManager::_issueRenderOp(Renderable* rend)
	{
		RenderOperation ro ;
		rend->getRenderOperation(ro);
		mDestRenderSystem->_render(ro);
	}


}