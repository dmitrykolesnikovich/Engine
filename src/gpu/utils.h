#pragma once

#include "gpu/dll.h"
#include "gpu/types.h"

namespace GPU
{
	/**
	 * Format info.
	 */
	struct GPU_DLL FormatInfo
	{
		/// Block width.
		i32 blockW_ = 0;
		/// Block height.
		i32 blockH_ = 0;
		/// Number of bits in block.
		i32 blockBits_ = 0;
		/// Number of bits for red channel.
		i32 rBits_ = 0;
		/// Number of bits for green channel.
		i32 gBits_ = 0;
		/// Number of bits for blue channel.
		i32 bBits_ = 0;
		/// Number of bits for alpha channel.
		i32 aBits_ = 0;
		/// Number of bits for depth.
		i32 dBits_ = 0;
		/// Number of bits for stencil.
		i32 sBits_ = 0;
		/// Number of padding bits.
		i32 xBits_ = 0;
		/// Number of exponent bits.
		i32 eBits_ = 0;
	};

	/**
	 * Get format info.
	 * @pre format != INVALID.
	 */
	GPU_DLL FormatInfo GetFormatInfo(Format format);


	/**
	 * Texture layout info.
	 */
	struct GPU_DLL TextureLayoutInfo
	{
		i32 pitch_ = 0;
		i32 slicePitch_ = 0;
	};

	/**
	 * Get texture layout info.
	 * @pre format != INVALID.
	 * @pre @a width >= 1.
	 * @pre @a height >= 1.
	 */
	GPU_DLL TextureLayoutInfo GetTextureLayoutInfo(Format format, i32 width, i32 height);

	/**
	 * Get texture size.
	 * @pre @a width >= 1.
	 * @pre @a height >= 1.
	 * @pre @a depth >= 1.
	 * @pre @a levels >= 1.
	 * @pre @a elements >= 1.
	 */
	GPU_DLL i64 GetTextureSize(Format format, i32 width, i32 height, i32 depth, i32 levels, i32 elements);

} // namespace GPU
