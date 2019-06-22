// Copyright (C) 2019 by Ilya Glushchenko
// This code is licensed under the MIT license (MIT)
// (http://opensource.org/licenses/MIT)

#include "Definitions.hpp"
#include "Math.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace ray;

constexpr uint32_t PACK16 = 16;
constexpr uint32_t PACK4 = 4;

inline void RenderBanch16()
{

}

inline void ComputePrimeRays(
	Window window,
	Camera const& camera,
	Vector<Ray4x4f> origins, 
	Vector<Ray4x4f> directinos
)
{
	memset(origins.data, 0, origins.size);
	for (uint32_t i = 0; i < origins.length; ++i)
	{
		origins.data[i].m512 = math::Add4x1(origins.data[i].m512, camera.eyePos);
	}

	math::Vector4f const inc = _mm_set1_ps(1.f);
	math::Vector4f const width = _mm_set1_ps(static_cast<float>(window.width));
	math::Vector4f pixels = { 0.f, 1.f, 2.f, 3.f };
	for (uint32_t y = PACK4 - 1; y < window.height; ++y)
	{
		for (uint32_t x = PACK4 - 1; x < window.width; ++x)
		{
			float dx = camera.leftBottom.m128_f32[0] + camera.rightTop.m128_f32[0] * (x / window.width);
			float dy = camera.leftBottom.m128_f32[1] + camera.rightTop.m128_f32[1] * (y / window.height);
			float dz = camera.leftBottom.m128_f32[2];
		}
	}
}

inline void RenderFrame(
	Window& window, 
	Camera const& camera,
	Scene const& scene, 
	Sampler sampler, 
	Vector<Ray4x4f> origins, 
	Vector<Ray4x4f> direction
)
{
	

}

int main()
{
	Window window = AllocateWindow(400, 400);
	Sampler sampler;
	Camera camera = CreateDefaultCamera();
	Scene scene = AllocateScene(1);

	Vector<Ray4x4f> origins = AllocateVector<Ray4x4f>(window.width * window.height);
	Vector<Ray4x4f> directions = AllocateVector<Ray4x4f>(window.width * window.height);

	ClearWindow(window);
	stbi_write_bmp("image.bmp", window.width, window.height, sizeof(Color4), window.data);



}
