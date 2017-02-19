#include "OverPassSceneNode.h"
#include "OverPassSceneManager.h"
#include "OverPassQuaternion.h"
#include "OverPassSceneManager.h"
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
			for (child = mChildren.begin(); child != mChildren.end(); child++)
			{
				SceneNode* sceneChild = static_cast<SceneNode*>(child->second);
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
			mObjectByName.insert(ObjectMap::value_type(obj->getName(),obj));
		//void(insresult);
		needUpdate();
		printf("has attacked;\n");
	}
	int SceneNode::numAttachObjects(void) const
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
	MovableObject* SceneNode::getAttachedObject(const std::string& name)
	{
		ObjectMap::iterator	 i = mObjectByName.find(name);
		if (i == mObjectByName.end())
		{
			//hehe
		}
		return i->second;
	}
	void SceneNode::_findVisibleObjects(RenderQueue* queue, bool includeChildren, bool displayNodes)
	{

		printf("sceneNodeFinfVisible\n");
		ObjectMap::iterator iobj;
		ObjectMap::iterator iobjend = mObjectByName.end();
		bool hehe=mObjectByName.begin() == iobjend;
		if (hehe)
			printf("size is empty\n");
		else
			printf("size not empty\n");
		for (iobj = mObjectByName.begin(); iobj != iobjend; iobj++)
		{
			MovableObject* mo = iobj->second;
			printf("MovableObjectsHasBeenFound\n");
			queue->processVisibleObject(mo);
		}
		if (includeChildren)
		{
			ChildNodeMap::iterator  child, childend;
			childend = mChildren.end();
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
		ObjectMap::const_iterator i;
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
	Node* SceneNode::createChildImpl(const std::string& name)
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
			i->second->setVisible(visible);
		}
		if (cascade)
		{
			ChildNodeMap::iterator oi, oend;
			oend = mChildren.end();
			for (oi = mChildren.begin(); oi != oend; oi++)
			{
				static_cast<SceneNode*>(oi->second)->setVisible(visible, cascade);
			}
		}
	}
	void SceneNode::flipVisibility(bool cascade)
	{
		ObjectMap::iterator oi, oiend;
		oiend = mObjectByName.end();
		for (oi = mObjectByName.begin(); oi != oiend; ++oi)
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