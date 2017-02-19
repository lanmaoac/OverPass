#pragma once
#include "OverPassPrerequisites.h"
#include "OverPassMatrix4.h"
#include "OverPassRenderOperation.h"
#include "OverPassRenderSystem.h"


namespace OverPass
{
	class Renderable
	{
	public:
			Renderable():mUseIdentitProjection(false),mUseIdentiyView(false){}
			virtual ~Renderable(){}
			//virtual const MaterialPtr& getMaterial(void) consrt=0;
			//virtual Technique* getTechnique(void) const{return getMaatertial()->getBestTechnique(0,this);}
			//±‡“Î¥ÌŒÛ do something later
		
			virtual bool preRender(SceneManager* sm, RenderSystem* sys)
			{
				(void)sm;
				(void)sys;
				return true;
			}
			virtual void postRender(SceneManager* sm, RenderSystem* sys)
			{
				(void)sm;
				(void)sys;
			}
			
			virtual void getWorldTransforms(Matrix4* xform) const = 0;
			virtual int getNumWorldTransforms(void) const { return 1; }
			void setUseIndentityProjecton(bool useIdentityProjection)
			{
				mUseIdentitProjection = useIdentityProjection;
			}
			bool getUseIdentityProjection(void) const { return mUseIdentitProjection; }
			void setUseIdentityView(bool useIdentityView)
			{
				mUseIdentiyView = useIdentityView;
			}

			bool getUseIdentityView(void) const { return mUseIdentiyView; }
			virtual void getRenderOperation(RenderOperation& op) = 0;
			void clear(bool destroyPassMaps=false);
	protected:

		//typedef std::map<int, Vector4> CusomParameterMap;
		bool mUseIdentitProjection;
		bool mUseIdentiyView;
			//virtual float getSquaredViewDepth(const Camera* cam) const =0;

	};
}