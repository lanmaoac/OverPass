#pragma once
#include "OverPassPrerequisites.h"

#include "OverPassQuaternion.h"
#include "OverPassVector3.h"
#include "OverPassRenderSystem.h"
#include "OverPassRenderQueue.h"
#include "OverPassEntity.h"
#include "OverPassMovableObject.h"
#include "OverPassRenderable.h"
#include "OverPassRenderQueueSortingGrouping.h"
#include "OverPassSceneNode.h"

namespace OverPass
{
	struct ViewPoint
	{
		Vector3 position;
		Quaternion orientation;
	};
	class SceneManager
	{
	protected:
		virtual SceneNode* createSceneNodeImpl(void);
		virtual SceneNode* createSceneNodeImpl(const std::string& name);
		std::string mName;
		RenderQueue* mRenderQueue;
		RenderSystem* mDestRenderSystem;

		typedef std::map<std::string, SceneNode*> SceneNodeList;
		SceneNodeList mSceneNodes;

		SceneNode* mSceneRoot;
		
		Entity* mSkyPlaneEntity;
		SceneNode* mSkyPlaneNode;
		bool mSkyPlaneEnabled;

		typedef std::map<std::string, MovableObject*> MovableObjectMap;
		
	public:
		virtual void initRenderQueue(void);
		virtual void renderVisibleObjectsDefaultSequence(void);
		virtual void prepareRenderQueue(void);

		
		virtual void renderSingleObject(Renderable* rend);
	public:
		struct  RenderContext
		{
			RenderQueue* renderQueue;
			//Viewport* viewport;
			//Camera* camera;
			//CompositorChain* activeChain;
			//RenderSystem::RenderSystemContext* rsContext;
		};
		//virtual RenderContext* _pauseRendering() {}
		virtual void _resumeRendering(RenderContext* context) {};
		SceneManager(const std::string& instanceName);
		virtual ~SceneManager();


		virtual SceneNode* createSceneNode(void);
		virtual SceneNode* createSceneNode(const std::string& name);
		virtual SceneNode* getRootSceneNode(void);

		virtual bool hasSceneNode(const std::string& name) const { return true; }
		virtual Entity* createEntity(const std::string& entityName, const std::string& meshName);
		//virtual Entity* createEntity(const std::string& entityName);
		//virtual Entity* createEntity(const std::string& entityName, const Mesh* pMesh);


		enum PrefabType {
			PT_PLANE,
			PT_CUBE,
			PT_SPHERE
		};
		virtual Entity* createEntity(const std::string& entityName, PrefabType ptype);

		//virtual Entity* getEntity(const std::string name) const;
		//virtual bool hasEntity(const std::string name) const;

		virtual void clearScene(void);
		virtual void _findVisibleObjects();

		virtual void _renderVisibleObjects(void);
		virtual void _renderScene(void);
		virtual void _renderQueueGroupObjects(RenderQueueGroup* group);
		virtual void renderBasicGroupObjects(RenderQueueGroup* pGroup);
		virtual void renderObjects( QueueRenderableCollection objs);
		virtual void _issueRenderOp(Renderable* rend);
		
		virtual void _setDestinationRenderSystem(RenderSystem* sys);
		//RenderSystem* getDestinationRenderSystem();

		virtual RenderQueue* getRenderQueue(void);
		virtual SceneNode* getSceneNode(const std::string& name) const;
		virtual void _updateSceneGraph();

	};

}