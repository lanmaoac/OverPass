#include "OverPassSceneNode.h"
namespace OverPass
{
	SceneNode::SceneNode(SceneManager* creator)
		:Node()
		,mCreator(creator)
		,mIsInSceneGraph(false)
	{
		needUpdate();
	}
	SceneNode::SceneNode(SceneManager* creator, const std::string& name)
		:Node(name)
		, mCreator(creator)
		, mIsInSceneGraph(false)
	{
		needUpdate();
	}
	SceneNode::~SceneNode()
	{
		ObjectMap::iterator itr;
		for (itr = mObjectByName.begin(); itr != mObjectByName.end(); ++itr)
		{
			MovableObject* ret = itr->second;
			ret->_notifyAttached((SceneNode *)0);
		}
		mObjectByName.clear();
	}
	void SceneNode::_update(bool updateChildren, bool parentHasChanged)
	{
		Node::_update(updateChildren, parentHasChanged);
	}
	void SceneNode::setParent(Node* parent)
	{
		Node::setParent(parent);
		if (parent)
		{
			SceneNode* sceneParent = static_cast<SceneNode*>(parent);
			setInSceneGraph(sceneParent->isInSceneGraph());
		}
		else
		{
			setInSceneGraph(false);
		}
	}
	void SceneNode::setInSceneGraph(bool inGraph)
	{
		if (inGraph != mIsInSceneGraph)
		{
			mIsInSceneGraph = inGraph;
			ChildNodeMap::iterator child;
			for (child = mObjectByName.begin(); child != mObjectByName.end(); child++)
			{
				SceneNode* sceneChild = static_cast<SceneNode>(child->second);
				sceneChild->setInSceneGraph(inGraph);
			}
		}
	}
	void SceneNode::attachObject(MovableObject* obj)
	{
		if (obj->isAttached())
		{
			//hehe
		}
		obj->_notifyAttached(this);
		std::pair<ObjectMap::iterator, bool> insresult =
			mObjectByName.insert(ObjectMap::value_type(numAttachObjects->getName(),obj));
		void(insresult);
		needUpdate();
	}
	int SceneNode::numAttachObjects()
	{
		return mObjectByName.size();
	}
	MovableObject* SceneNode::getAttachedObject(int index)
	{
		if (index < mObjectByName.size())
		{
			ObjectMap::iterator i = mObjectByName.begin();
			while (index--) ++i;
			return i->second;
		}
		else
		{
			//hehe
		}
	}
	MovableObject* SceneNode:: getAttachedObject(const std::string& name)
	{
		ObjectMap::iterator	 i = mObjectsByName.find(name);
		if (i == mObjectByName.end())
		{
			//hhe
		}
		return i->second;
	}
	void SceneNode::_findVisibleObjects(RenderQueue* queue, bool includeChildren, bool displayNodes)
	{
		ObjectMap::iterator iobj;
		ObjectMap::iterator iobjend = mObjectByName.end();
		for (iobj = mObjectByName.begin(); i != iobjend; i++)
		{
			MovableObject* mo = iobj->second;
			queue->processVisibleObject(mo);
		}
		if (includeChildren)
		{
			ChildNodeMap::iterator  child, childend;
			mChildren = mObjectByName.end();
			for (child = mChildren.begin(); child != childend;++child)
			{
				SceneNode* sceneChild = static_cast<SceneNode*>(child->second);
				sceneChild->_findVisibleObjects(queue,includeChildren,displayNodes);
			}
		}
		if (displayNodes)
		{
			//debug
			//queue->addRenderable(getDebugRenderable())
		}

	}

	void SceneNode::updateFromParentImpl(void) const
	{
		Node::updateFromParentImpl();
		ObjectMap::iterator i;
		for (i = mObjectByName.begin(); i != mObjectByName.end(); i++)
		{
			MovableObject* obj = i->second;
			obj->_notifyMoved();
		}
	}

	Node* SceneNode::createChildImpl(void)
	{
		return mCreator->createSceneNode();
	}
	Node* SceneNode::createChildImpl(std::string& name)
	{
		return mCreator->createSceneNode(name);
	}

	SceneNode* SceneNode::createChildSceneNode(const Vector3& inTranslate, const Quaternion& inRotate)
	{
		return static_cast<SceneNode*>(this->createChild(inTranslate, inRotate));
	}
	SceneNode* SceneNode::createChildSceneNode(const std::string& name,
		const Vector3& inTranslate,
		const Quaternion& inRotate)
	{
		return static_cast<SceneNode*>(this->createChild(name, inTranslate, inRotate));
	}
	SceneNode* SceneNode::getParentSceneNode(void) const 
	{
		return  static_cast<SceneNode*>(getParent());
	}
	void SceneNode::setVisible(bool visible, bool cascade)
	{
		ObjectMap::iterator i, iend;
		iend = mObjectByName.end();
		for (i = mObjectByName.begin(); i != iend; i++)
		{
			i->second->setVisible();
		}
		if (cascade)
		{
			ChildNodeMap::iterator oi, oend;
			oend = mChildren.end();
			for (oi = mChildren.begin(); oi != oend; oi++)
			{
				static_cast<SceneNode*>(i->second)->setVisible(visible, cascade);
			}
		}
	}
	void SceneNode::flipVisibility(bool cascade)
	{
		ObjectMap::iterator oi, oiend;
		oiend = mObjectsByName.end();
		for (oi = mObjectsByName.begin(); oi != oiend; ++oi)
		{
			oi->second->setVisible(!oi->second->getVisible());
		}

		if (cascade)
		{
			ChildNodeMap::iterator i, iend;
			iend = mChildren.end();
			for (i = mChildren.begin(); i != iend; ++i)
			{
				static_cast<SceneNode*>(i->second)->flipVisibility(cascade);
			}
		}
	}


}