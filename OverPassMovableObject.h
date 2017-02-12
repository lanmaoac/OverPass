#pragma once
#ifndef __MovableObject_H__
#define __MovableObject_H__

// Precompiler options
#include "OverPassPrerequisites.h"
#include "OverPassNode.h"
#include "OverpassSceneNode.h"
namespace OverPass
{
	class MovableObject
	{
	protected:

		std::string mName;
		SceneManager* mManager;
		Node* mParentNode;
		bool mVisible;
		int mRenderQueueID;
		int mRenderQueuePriority;
		bool mRenderQueueIDSet;
		bool mRenderQueuePrioritySet;

	public:

		MovableObject();
		MovableObject(const std::string& name);
		virtual void _notifyMamager(SceneManager* man) { mManager = man; }
		virtual SceneManager* _getManager(void) const { return mManager; }

		virtual const std::string& getName(void) const { return mName; }
		virtual Node* getParent(void)const;
		virtual SceneNode* getParentSceneNode(void) const;

		virtual void _notifyAttached(Node* parent);
		virtual bool _isAttached(void) const;
		virtual bool isInScene(void) const;
		virtual void _notifyMoved(void);

		virtual void _updateRenderQueue(RenderQueue* queue) = 0;
		virtual void setVisible(bool visible);
		virtual void setRenderQueueGroup(int queueID);
		virtual void setRenderQueueGroupAndPriority(int queueID, int priority);
		virtual const Matrix4& _getParentNodeFullTransform(void) const;





	};
}