#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassMatrix4.h"
#include "OverPassRenderable.h"
#include "OverPassSubMesh.h"
//#include "OverPassEntity.h"
namespace OverPass
{
	class SubEntity :public Renderable
	{
		friend class Entity;
		friend class SceneManager;
	protected:
		SubEntity(Entity* parent, SubMesh* sunMeshBasis);
		virtual ~SubEntity();
		Entity *mParentEntity;
		//MaterialPtr mMaterialPtr;

		SubMesh* mSubMesh;
		bool mVisible;

		int mRenderQueueID;
		bool mRenderQueueIDSet;
		int mRenderQueuePriority;
		bool mRenderQueuePrioritySet;

		//meshLod
		//materialLod

	public:
		virtual void setVisible(bool visible);
		virtual bool isVisible(void) const;
		virtual void setRenderQueueGroup(int queueID);
		virtual void setRenderQueueGroupAndPriority(int queueID, int priority);
		virtual int getRenderQueueGroup(void) const;
		virtual int getRenderQueuePriority(void) const;
		virtual bool isRenderQueueGroupSet(void) const;
		virtual bool isRenderQueuePrioritySet(void) const;

		SubMesh* getSubMesh(void);
		Entity* getParent(void) const { return mParentEntity; }
		void getRenderOperation(RenderOperation& op);
		void getWorldTransforms(Matrix4* xform) const;
	};


}
