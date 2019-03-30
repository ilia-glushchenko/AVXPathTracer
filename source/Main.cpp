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
