// Copyright (C) 2019 by Ilya Glushchenko
// This code is licensed under the MIT license (MIT)
// (http://opensource.org/licenses/MIT)
#pragma once

#include "Definitions.hpp"
#include "Math.hpp"

namespace cd
{

	void SphereRayIntersection(
		ray::Vector<ray::Ray4x4f> origins, 
		ray::Vector<ray::Ray4x4f> direction, 
		ray::Scene scene
	)
	{
		for (uint32_t j = 0; j < origins.size; ++j)
		{
			for (uint32_t i = 0; i < scene.centers.size; ++i)
			{
				math::Vector4x4f m4x4 = math::Sub4(origins.data[j+0].m512, scene.centers.data[i]);
				math::Vector4x4f m4x4 = math::Sub4(origins.data[j+1].m512, scene.centers.data[i]);
				math::Vector4x4f m4x4 = math::Sub4(origins.data[j+2].m512, scene.centers.data[i]);
				math::Vector4x4f m4x4 = math::Sub4(origins.data[j+3].m512, scene.centers.data[i]);

			}
		}
	}

} // namespace cd
