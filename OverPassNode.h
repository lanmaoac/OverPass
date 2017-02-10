#ifndef _Node_H__
#define _Node_H__
#include "OverPassPrerequisites.h"
#include "OverPassQuaternion.h"
#include "OverPassVector3.h"
namespace OverPass
{
	class Node
	{
	public:
		typedef std::map<std::string, Node*> ChildNodeMap;
	protected:

		Node* mParent;
		
		ChildNodeMap mChildren;

		typedef std::set<Node*> ChildUpdateSet;
		ChildUpdateSet mChildrenToUpdate;

		std::string mName;

		Quaternion mOrientation;
		Vector3 mPosition;
		Vector3 mScale;

		bool mNeedChildUpdate;
		mutable bool mNeedParentUpdate;
		bool mInheritOrientation;
		bool mInheritScale;


		virtual void setParent(Node *parent);
		mutable Quaternion mDerivedOrientation;
		mutable Vector3 mDerivedPosition;
		mutable Vector3 mDerivedScale;

		void _updateFromParent(void) const;

		virtual Node* createChildImpl(void) = 0;
		virtual Node* createChildImpl(const std::string& name) = 0;

	public :
		Node();
		Node(const std::string& name);
		
		virtual ~Node();

		const std::string& getName(void) const { return mName; }
		Node* getParent(void) const { return mParent; }

		
		void setOrientation(const Quaternion& q);
		//real or float
		void setOrientation(float w,float x,float y,float z);
		const Quaternion& getOrientation() const { return mOrientation; }

		void setPosition(const Vector3& pos);
		//real or float 
		void setPosition(float x,float y,float z);
		const Vector3 & getPosition(void) const { return mPosition; }


		void setScale(const Vector3& scale);
		//real or floaat 
		void setScale(float x,float y,float z);
		const Vector3& getScale(void) const { return mScale; }


		
		void setInheritOrientation(bool inherit);
		bool getInheritOrientation() const { return mInheritOrientation; }

		void setInheritScale(bool inherit);
		bool getInheritScale()const { return mInheritScale; }


		virtual Node* createChild(
			const Vector3& inTranslate = Vector3::ZERO,
			const Quaternion inRotate = Quaternion::IDENTITY);

		virtual Node* createChild(const std::string& name, const Vector3& inTranslate = Vector3::ZERO, const Quaternion& inRotate = Quaternion::IDENTITY);

		void addChild(Node* child);

		Node* getChild(unsigned short index)  const;
		Node* getChild(const std::string& name) const;
		virtual Node* removeChild(int i);
		virtual Node* removeChild(const std::string& name);
		virtual Node* removeChild(Node* child);
		virtual void removeAllChildren(void);

		virtual void _update(bool updateChildren, bool parentHasChanged);
		virtual void needUpdate(bool forceParentUpdate = false);
	
						   
		const Quaternion & _getDerivedOrientation(void) const;
		const Vector3 & _getDerivedPosition(void) const;
		const Vector3 & _getDerivedScale(void) const;
		virtual void updateFromParentImpl(void) const;

	};
}
#endif // _Node_H_
