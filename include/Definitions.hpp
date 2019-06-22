// Copyright (C) 2019 by Ilya Glushchenko
// This code is licensed under the MIT license (MIT)
// (http://opensource.org/licenses/MIT)
#pragma once

#include <Math.hpp>
#include <cstdint>
#include <immintrin.h>

namespace ray
{

	enum class eMemoryOrder : uint8_t 
	{
		NONE = 0,
		XXXX = 1,
		XYZW = 2,
		Count 
	};

	template < typename T >
	struct Vector
	{
		T* data = nullptr;
		uint32_t length = 0;
		uint32_t size = 0;
	};

	using Radii4 = __m128;
	using Color4 = __m128;

	struct Window
	{
		uint32_t width = 512;
		uint32_t height = 512;
		Color4* data = nullptr;
		uint32_t size = 0;
	};

	struct Sampler
	{
		uint32_t samples = 0;
		uint32_t bounces = 0;
	};

	struct Camera
	{
		math::Vector4f viewAt;
		math::Vector4f eyePos;
		math::Vector4f eyeDir;
		math::Vector4f upDir;
		math::Vector4f leftBottom;
		math::Vector4f rightTop;
		float verticalViewAngle;
		float horizontalViewAngle;
	};

	struct Scene
	{
		Vector<Color4> colors;
		Vector<Radii4> radii;
		Vector<math::Vector4x4f> centers;
		uint32_t length;
	};

	struct Ray
	{
		math::Vector4f origin;
		math::Vector4f direction;
	};

	struct Ray4x4f
	{
		union
		{
			math::Vector4x4f m512;
			__m128 origin[4];
			__m128 direction[4];

			struct {
				__m128 origin0;
				__m128 direction0;
				__m128 origin1;
				__m128 direction1;
			} pack;

			struct {
				__m128 xxxx;
				__m128 yyyy;
				__m128 zzzz;
				__m128 wwww;
			} xxxx;

			struct {
				__m128 v0;
				__m128 v1;
				__m128 v2;
				__m128 v3;
			} xyzw;
		};
	};

	template < typename T >
	Vector<T> AllocateVector(uint32_t size)
	{
		return { reinterpret_cast<T*>(malloc(sizeof(T) * size)), size, sizeof(T) * size };
	}

	template < typename T >
	void FreeVector(Vector<T>& vector)
	{
		free(vector.data);
		vector.data = nullptr;
		vector.length = 0;
		vector.size = 0;
	}

	Window AllocateWindow(uint32_t width, uint32_t height)
	{
		Window window;

		window.width = width;
		window.height = height;
		window.size = sizeof(Color4) * window.width * window.height;
		window.data = reinterpret_cast<Color4*>(malloc(window.size));

		return window;
	}

	void FreeWindow(Window& window)
	{
		free(window.data);
		window.data = nullptr;
		window.width = 0;
		window.height = 0;
		window.size = 0;
	}

	void ClearWindow(Window window)
	{
		for (uint32_t i = 0; i < window.width * window.height; ++i)
		{
			window.data[i] = {};
		}
	}

	Scene AllocateScene(uint32_t length)
	{
		Scene scene;

		scene.colors = AllocateVector<Color4>(length);
		scene.radii = AllocateVector<Radii4>(length);
		scene.centers = AllocateVector<math::Vector4x4f>(length);

		for (uint32_t i = 0; i < length; ++i)
		{
			scene.colors.data[i] = {};
			scene.radii.data[i] = {};
			scene.centers.data[i] = {};
		}

		return scene;
	}

	void FreeScene(Scene& scene)
	{
		FreeVector(scene.colors);
		FreeVector(scene.radii);
		FreeVector(scene.centers);
	}

	void InitializeScene(Scene& scene)
	{
		scene.colors.data[0] = { 1.f, 1.f, 1.f, 1.f };
		scene.radii.data[0] = { 0.5f };
		scene.centers.data[0] = { 0, 0, 0, 0 };
	}

	Camera CreateDefaultCamera()
	{
		Camera camera;
		camera.viewAt = { 0, 0, 0 };
		camera.upDir = { 0, 1.f, 0 };
		camera.eyePos = { 0, -10.f, 0, 0 };
		camera.eyeDir = math::xyzw::Normalize(math::xyzw::Sub(camera.viewAt, camera.eyePos));
		camera.horizontalViewAngle = math::PI / 4.f;
		camera.verticalViewAngle = math::PI / 4.f;
		camera.leftBottom = math::xyzw::Normalize({ -1, -1, 1 });
		camera.rightTop = math::xyzw::Normalize({ 1, 1, 1 });
	}

	Sampler CreateDefaultSampler()
	{
		Sampler sampler;
		sampler.bounces = 1;
		sampler.samples = 1;
	}

} // namespace ray
