#include "OverPassNode.h"

namespace OverPass
{
	Node::Node()
		:mParent(0),
		mPosition(Vector3::ZERO),
		mScale(Vector3::UNIT_SCALE),
		mInheritOrientation(true),
		mInheritScale(true)
	{
		mName = "hehe";
		needUpdate();
	}
	Node::Node(const  std::string& name)
		:mParent(0),
		mPosition(Vector3::ZERO),
		mScale(Vector3::UNIT_SCALE),
		mInheritOrientation(true),
		mInheritScale(true)
	{
		mName = name;
		needUpdate();
	}

	Node::~Node()
	{
		removeAllChildren();
		if (mParent)
			mParent->removeChild(this);

	}
	void Node::setParent(Node  *parent)
	{
		bool different = (parent != mParent);
		mParent = parent;

		needUpdate();
	}
	void Node::setPosition(const Vector3& pos)
	{
		mPosition = pos;
		needUpdate();
	}
	void Node::setPosition(float x, float y, float z)
	{
		Vector3 v = Vector3(x, y, z);
		setPosition(v);
	}

	void Node::setScale(const Vector3& inScale)
	{
		mScale = inScale;
		needUpdate();
	}
	void Node::setScale(float x, float y, float z)
	{
		setScale(Vector3(x, y, z));
	}
	void Node::setOrientation(const Quaternion & q)
	{
		mOrientation = q;
		mOrientation.normalise();
		needUpdate();
	}
	void Node::setOrientation(float w, float x, float y, float z)
	{
		setOrientation(Quaternion(w,x,y,z));
	}

	void Node::_update(bool updateChildren, bool parentHasChanged)
	{
		if (parentHasChanged)
		{
			_updateFromParent();
		}
		if (updateChildren)
		{
			if (mNeedChildUpdate || parentHasChanged)
			{
				ChildNodeMap::iterator it, itend;
				itend = mChildren.end();
				for (it = mChildren.begin(); it != itend; ++it)
				{
					Node *child = it->second;
					child->_update(true,true);
				}
			}
			mNeedChildUpdate = false;
		}
	}
	void Node::_updateFromParent(void) const
	{
		updateFromParentImpl();
	}
	void Node::updateFromParentImpl(void) const
	{
		if (mParent)
		{
			const Quaternion& parentOrientation = mParent->_getDerivedOrientation();
			if (mInheritOrientation)
			{
				mDerivedOrientation = parentOrientation * mOrientation;
			}
			else
			{
				mDerivedOrientation = mOrientation;
			}

			const Vector3& parentScale = mParent->_getDerivedScale();
			if (mInheritScale)
			{
				mDerivedScale = parentScale * mScale;
			}
			else
			{
				mDerivedScale = mScale;
			}
			mDerivedPosition = parentOrientation*(parentScale*mPosition);
			mDerivedPosition += mParent->_getDerivedPosition();
		}
		else
		{
			mDerivedOrientation = mOrientation;
			mDerivedPosition = mPosition;
			mDerivedScale = mScale;
		}
		mNeedParentUpdate = false;
	}
	void Node::addChild(Node* child)
	{
		if (child->mParent)
		{
			//HEHE
		}
		child->setParent(this);
	}
	Node* Node::removeChild(int index)
	{
		if (index > mChildren.size())
		{
			ChildNodeMap::iterator i = mChildren.begin();
			while (index--)++i;
			Node* ret = i->second;
			//cancleUpdate(ret);
			mChildren.erase(i);
			ret->setParent(NULL);
			return ret;
		}
		else
		{
			//hehe
		}
		return 0;
	}
	Node* Node::removeChild(const std::string& name)
	{
		ChildNodeMap::iterator i = mChildren.find(name);
		if (i == mChildren.end())
		{
			//HEHE
		}
		Node* ret = i->second;
		mChildren.erase(i);
		ret->setParent(NULL);
		return ret;
	}
	Node* Node::removeChild(Node* child)
	{
		if (child)
		{
			ChildNodeMap::iterator i = mChildren.find(child->getName());
			if (i != mChildren.end() && i->second == child)
			{
				mChildren.erase(i);
				child->setParent(NULL);
			}
		}
		return child;
	}

	void Node::removeAllChildren()
	{
		ChildNodeMap::iterator i, iend;
		iend = mChildren.end();
		for (i = mChildren.begin(); i != mChildren.end(); ++i)
		{
			i->second->setParent(0);
		}
		mChildren.clear();
		mChildrenToUpdate.clear();
	}



	Node* Node::createChild(const Vector3& inTranslate ,
		const Quaternion inRotate )
	{
		Node* newNode = createChildImpl();
		newNode->setPosition(inTranslate);
		newNode->setOrientation(inRotate);
		this->addChild(newNode);
		return newNode;
	}
	Node* Node::createChild(const std::string& name, const Vector3& inTranslate , const Quaternion& inRotate)
	{
		Node* newNode = createChildImpl(name);
		newNode->setPosition(inTranslate);
		newNode->setOrientation(inRotate);
		this->addChild(newNode);
		return newNode;
	}


	void Node::needUpdate(bool forceParentUopate)
	{
		mNeedParentUpdate = true;
		mNeedChildUpdate = true;

	}

	const Quaternion & Node::_getDerivedOrientation(void) const
	{
		if (mNeedParentUpdate)
		{
			_updateFromParent();
		}
		return mDerivedOrientation;
	}
	const Vector3 & Node::_getDerivedScale(void) const
	{
		if (mNeedParentUpdate)
		{
			_updateFromParent();
		}
		return mDerivedScale;
	}
	const Vector3 & Node::_getDerivedPosition(void) const
	{
		if (mNeedParentUpdate)
		{
			_updateFromParent();
		}
		return mDerivedPosition;
	}

}

