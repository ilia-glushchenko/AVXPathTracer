// Copyright (C) 2019 by Ilya Glushchenko
// This code is licensed under the MIT license (MIT)
// (http://opensource.org/licenses/MIT)
#pragma once

#include <immintrin.h>

namespace math
{
	using Vector4x4f = __m512;
	using Vector4f = __m128;
}

namespace
{

	inline __forceinline math::Vector4x4f Dot16fromMuls(
		__m512 aMulB0, __m512 aMulB1, __m512 aMulB2, __m512 aMulB3
	)
	{
		__m128 xxxx0 = _mm512_castps512_ps128(aMulB0);
		__m128 yyyy0 = _mm512_extractf32x4_ps(aMulB0, 1);
		__m128 zzzz0 = _mm512_extractf32x4_ps(aMulB0, 2);
		__m128 wwww0 = _mm512_extractf32x4_ps(aMulB0, 3);

		__m128 xxxx1 = _mm512_castps512_ps128(aMulB1);
		__m128 yyyy1 = _mm512_extractf32x4_ps(aMulB1, 1);
		__m128 zzzz1 = _mm512_extractf32x4_ps(aMulB1, 2);
		__m128 wwww1 = _mm512_extractf32x4_ps(aMulB1, 3);

		__m128 xxxx2 = _mm512_castps512_ps128(aMulB2);
		__m128 yyyy2 = _mm512_extractf32x4_ps(aMulB2, 1);
		__m128 zzzz2 = _mm512_extractf32x4_ps(aMulB2, 2);
		__m128 wwww2 = _mm512_extractf32x4_ps(aMulB2, 3);

		__m128 xxxx3 = _mm512_castps512_ps128(aMulB3);
		__m128 yyyy3 = _mm512_extractf32x4_ps(aMulB3, 1);
		__m128 zzzz3 = _mm512_extractf32x4_ps(aMulB3, 2);
		__m128 wwww3 = _mm512_extractf32x4_ps(aMulB3, 3);

		__m512 x16 = _mm512_castps128_ps512(xxxx0);
		x16 = _mm512_insertf32x4(x16, xxxx1, 1);
		x16 = _mm512_insertf32x4(x16, xxxx2, 2);
		x16 = _mm512_insertf32x4(x16, xxxx3, 3);

		__m512 y16 = _mm512_castps128_ps512(yyyy0);
		y16 = _mm512_insertf32x4(y16, yyyy1, 1);
		y16 = _mm512_insertf32x4(y16, yyyy2, 2);
		y16 = _mm512_insertf32x4(y16, yyyy3, 3);

		__m512 z16 = _mm512_castps128_ps512(zzzz0);
		z16 = _mm512_insertf32x4(z16, zzzz1, 1);
		z16 = _mm512_insertf32x4(z16, zzzz2, 2);
		z16 = _mm512_insertf32x4(z16, zzzz3, 3);

		__m512 w16 = _mm512_castps128_ps512(wwww0);
		w16 = _mm512_insertf32x4(w16, wwww1, 1);
		w16 = _mm512_insertf32x4(w16, wwww2, 2);
		w16 = _mm512_insertf32x4(w16, wwww3, 3);

		__m512 dot_product = _mm512_add_ps(x16, y16);
		dot_product = _mm512_add_ps(dot_product, z16);
		dot_product = _mm512_add_ps(dot_product, w16);

		return dot_product;
	}
}

namespace math
{
	constexpr float PI = 3.14159265f;

	inline float Dot(Vector4f a, Vector4f b)
	{
		a = _mm_mul_ps(a, b);
		return a.m128_f32[0] + a.m128_f32[1] + a.m128_f32[2] + a.m128_f32[3];
	}

	inline Vector4x4f Dot16x1(
		Vector4x4f v0_0, Vector4x4f v0_1,
		Vector4x4f v0_2, Vector4x4f v0_3,
		Vector4f v_1
	)
	{
		__m512 b = _mm512_castps128_ps512(v_1);

		__m512 aMulB0 = _mm512_mul_ps(v0_0, b);
		__m512 aMulB1 = _mm512_mul_ps(v0_1, b);
		__m512 aMulB2 = _mm512_mul_ps(v0_2, b);
		__m512 aMulB3 = _mm512_mul_ps(v0_3, b);

		return ::Dot16fromMuls(aMulB0, aMulB1, aMulB2, aMulB3);
	}

	inline Vector4x4f Dot16x16(
		Vector4x4f v0_0, Vector4x4f v0_1, 
		Vector4x4f v1_0, Vector4x4f v1_1,
		Vector4x4f v2_0, Vector4x4f v2_1,
		Vector4x4f v3_0, Vector4x4f v3_1
	)
	{
		__m512 aMulB0 = _mm512_mul_ps(v0_0, v0_1);
		__m512 aMulB1 = _mm512_mul_ps(v1_0, v1_1);
		__m512 aMulB2 = _mm512_mul_ps(v2_0, v2_1);
		__m512 aMulB3 = _mm512_mul_ps(v3_0, v3_1);
	
		return ::Dot16fromMuls(aMulB0, aMulB1, aMulB2, aMulB3);
	}

	inline Vector4f Cross(Vector4f a, Vector4f b)
	{
		__m128 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 c = _mm_sub_ps(_mm_mul_ps(a, b_yzx), _mm_mul_ps(a_yzx, b));
		return _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
	}

	inline Vector4x4f Cross4(Vector4x4f a, Vector4x4f b)
	{
		__m512 a_yzx = _mm512_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
		__m512 b_yzx = _mm512_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
		__m512 c = _mm512_sub_ps(_mm512_mul_ps(a, b_yzx), _mm512_mul_ps(a_yzx, b));

		return _mm512_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
	}

	inline Vector4f Normalize(Vector4f v)
	{
		return _mm_div_ps(v, _mm_set1_ps(Length(v)));
	}

	inline Vector4x4f Normalize4(Vector4x4f v)
	{
		__m512 vSq = _mm512_mul_ps(v, v);

		__m128 a = _mm512_castps512_ps128(vSq);
		__m128 b = _mm512_extractf32x4_ps(vSq, 1);
		__m128 c = _mm512_extractf32x4_ps(vSq, 2);
		__m128 d = _mm512_extractf32x4_ps(vSq, 3);

		__m128 lengths = _mm_sqrt_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(a, b), c), d));

		a = _mm_div_ps(_mm512_castps512_ps128(v), lengths);
		b = _mm_div_ps(_mm512_extractf32x4_ps(v, 1), lengths);
		c = _mm_div_ps(_mm512_extractf32x4_ps(v, 2), lengths);
		d = _mm_div_ps(_mm512_extractf32x4_ps(v, 3), lengths);

		v = _mm512_castps128_ps512(a);
		_mm512_insertf32x4(v, b, 1);
		_mm512_insertf32x4(v, c, 2);
		_mm512_insertf32x4(v, d, 3);

		return v;
	}

	inline void Normalize16Restricted(
		Vector4x4f& __restrict v0, Vector4x4f& __restrict v1,
		Vector4x4f& __restrict v2, Vector4x4f& __restrict v3
	)
	{
		Vector4x4f lenghts = _mm512_rsqrt14_ps(Dot16x16(v0, v0, v1, v1, v2, v2, v3, v3));

		__m128 l0 = _mm512_extractf32x4_ps(lenghts, 0);
		__m128 l1 = _mm512_extractf32x4_ps(lenghts, 1);
		__m128 l2 = _mm512_extractf32x4_ps(lenghts, 2);
		__m128 l3 = _mm512_extractf32x4_ps(lenghts, 3);

		__m512 l = _mm512_castps128_ps512(l0);
		l = _mm512_insertf32x4(l, l0, 1);
		l = _mm512_insertf32x4(l, l0, 2);
		l = _mm512_insertf32x4(l, l0, 3);
		v0 = _mm512_div_ps(v0, l);

		l = _mm512_castps128_ps512(l1);
		l = _mm512_insertf32x4(l, l1, 1);
		l = _mm512_insertf32x4(l, l1, 2);
		l = _mm512_insertf32x4(l, l1, 3);
		v1 = _mm512_div_ps(v1, l);

		l = _mm512_castps128_ps512(l2);
		l = _mm512_insertf32x4(l, l2, 1);
		l = _mm512_insertf32x4(l, l2, 2);
		l = _mm512_insertf32x4(l, l2, 3);
		v2 = _mm512_div_ps(v2, l);

		l = _mm512_castps128_ps512(l3);
		l = _mm512_insertf32x4(l, l3, 1);
		l = _mm512_insertf32x4(l, l3, 2);
		l = _mm512_insertf32x4(l, l3, 3);
		v3 = _mm512_div_ps(v3, l);
	}

	inline float Length(Vector4f v)
	{
		v = _mm_mul_ps(v, v);
		return sqrt(v.m128_f32[0] + v.m128_f32[1] + v.m128_f32[2] + v.m128_f32[3]);
	}

	inline Vector4f Sub(Vector4f a, Vector4f b)
	{
		return _mm_sub_ps(a, b);
	}

	inline Vector4f Add(Vector4f a, Vector4f b)
	{
		return _mm_add_ps(a, b);
	}

} // namespace math
