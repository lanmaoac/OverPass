#pragma once

#ifndef __RenderSystem_H_
#define __RenderSystem_H_

#include "OverPassPrerequisites.h"
#include "OverPassRenderOperation.h"
#include "OverPassMatrix4.h"

namespace OverPass
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
		virtual void _setWorldMatrix(const Matrix4 &m) {}
		virtual void _setViewMatrix(const Matrix4 &m) {}
		virtual void _setProjectionMatrix(const Matrix4 &m) {}
		virtual void _setWorldMatrix(Vector3 pos){}

		virtual void _beginFrame(void) = 0;
		virtual void _endFrame(void) = 0;
		virtual void _render(const RenderOperation& op);
		virtual void _beginGeometryCount(void){}
		virtual void shutdown(void){}
	};
}
#endif