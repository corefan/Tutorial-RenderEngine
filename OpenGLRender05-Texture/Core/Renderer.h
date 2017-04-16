#pragma once

#include "XCore.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderOp.h"

namespace X {

	class IRenderer : public Singleton<IRenderer>
	{
	public:
		IRenderer();
		virtual ~IRenderer();

		virtual IRenderBuffer::Ptr
			CreateBuffer(int size) = 0;
		virtual Shader::Ptr
			LoadShader(const String & source) = 0;
		virtual Texture::Ptr
			LoadTexture(const String & source) = 0;
		virtual Texture::Ptr
			CreateTexture(const String & name, int format, int w, int h, int mipmaps) = 0;
		void
			_destroyTexture(Texture * p);

		virtual void
			Resize(int width, int height) = 0;
		
		virtual void
			Clear(const Float4 & color, float depth = 1.0f) = 0;

		void
			SetWorldMatrix(const Mat4 & m);
		void
			SetViewMatrix(const Mat4 & m);
		void
			SetProjMatrix(const Mat4 & m);
		void
			SetCamera(const Float3 & pos, const Float3 & dir);
		void
			SetLight(Light * l);
		void
			SetMaterial(const Material & m);
		void
			SetRenderState(const RenderState & rstate);
		void
			SetShader(Shader::Ptr shader);
		void
			SetSamplerTexture(int i, Texture::Ptr texture);

		const Mat4 &
			GetWorldMatrix() { return mWorldMatrix; }
		const Mat4 &
			GetViewMatrix() { return mViewMatrix; }
		const Mat4 &
			GetProjMatrix() { return mProjMatrix; }
		const Float4 &
			GetCameraPos() { return mCameraPos; }
		const Float4 &
			GetCameraDir() { return mCameraDir; }
		Light *
			GetLight() { return mLight;  }
		const Material &
			GetMaterial() { return mMaterial; }
		const RenderState &
			GetRenderState() { return mRenderState; }
		Texture *
			GetSamplerTexture(int i) { return mSamplerTextures[i];  }
		
		virtual void
			Begin();
		virtual void
			End();
		virtual void
			Render(RenderOp * rop) = 0;
		virtual void
			Present() = 0;

	protected:
		std::map<String, Texture *> mTextureMap;

		Mat4 mWorldMatrix;
		Mat4 mViewMatrix;
		Mat4 mProjMatrix;
		Float4 mCameraPos;
		Float4 mCameraDir;
		Light * mLight;
		Material mMaterial;
		RenderState mRenderState;
		Shader::Ptr mShader;
		std::array<Texture*, 16> mSamplerTextures;
	};

}