#ifndef _XX_H_
#define _XX_H_

#endif

#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassNode.h"
#include "OverPassMovableObject.h"
#include "OverPassRenderQueue.h"

namespace OverPass
{
	class SceneManager;
	class SceneNode :public Node
	{
	public :
		typedef std::map<std::string, MovableObject*> ObjectMap;
	protected:
		ObjectMap mObjectByName;
		SceneManager* mCreator;
		void updateFromParentImpl(void) const;
		Node* createChildImpl();
		Node* createChildImpl(const std::string& name);
		void setParent(Node *parent);
		virtual void setInSceneGraph(bool inScene);
		SceneNode *mAutoTrackTarget;
		Vector3 mAotuTrackOffset;
		Vector3 mAotuTrackDirection;

		bool mIsInSceneGraph;
	public:
		SceneNode(SceneManager* creator);
		SceneNode(SceneManager* creator, const std::string& name);
		~SceneNode();
		SceneNode();
		SceneNode(const std::string& name);

		virtual	void attachObject(MovableObject *obj);
		int numAttachObjects(void) const;

		MovableObject* getAttachedObject(int index);
		MovableObject* getAttachedObject(const std::string& name);

		bool isInSceneGraph(void) const { return mIsInSceneGraph; }
		void _notifyRootNode(void) { mIsInSceneGraph = true; }
		void _update(bool updateChildren, bool isParentHasChanged);

		void _findVisibleObjects(RenderQueue* queue, bool includeChildren = true, bool displayNode = false);
		SceneManager* getCreator(void) const { return mCreator; }

		virtual SceneNode* createChildSceneNode(
			const Vector3& translate = Vector3::ZERO,
			const Quaternion& rotate = Quaternion::IDENTITY);
		virtual SceneNode* createChildSceneNode(
			const std::string& name,
			const Vector3& inTranslate = Vector3::ZERO,
			const Quaternion& inRotate = Quaternion::IDENTITY);
		SceneNode* getParentSceneNode(void) const;

		//void detachObject(MovableObject *mo);
		void detachAllObjects(void){}
		void setVisible(bool visible, bool cascade = true);
		void flipVisibility(bool cascade = true);
		
	};
}
