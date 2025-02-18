/*
 * Copyright (C) 2023, Inria
 * GRAPHDECO research group, https://team.inria.fr/graphdeco
 * All rights reserved.
 *
 * This software is free for non-commercial, research and evaluation use 
 * under the terms of the LICENSE.md file.
 *
 * For inquiries contact  george.drettakis@inria.fr
 */

#ifndef CUDA_RASTERIZER_FORWARD_H_INCLUDED
#define CUDA_RASTERIZER_FORWARD_H_INCLUDED

#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define GLM_FORCE_CUDA
#include <glm/glm.hpp>

namespace FORWARD
{
	// Perform initial steps for each Gaussian prior to rasterization.
	void preprocess(int P, int D, int M,
		float* aabb,
		const float* orig_points,
		const glm::vec3* scales,
		const float scale_modifier,
		const float sigma,
		const glm::vec4* rotations,
		const float* opacities,
		const float* shs,
		bool* clamped,
		const float* colors_precomp,
		const float* view2gaussian_precomp,
		const float* viewmatrix,
		const float* projmatrix,
		const glm::vec3* cam_pos,
		const int W, int H,
		const float focal_x, float focal_y,
		const float principal_x, float principal_y,
		const float kernel_size,
		int* radii,
		float2* rects,
		float2* points_xy_image,
		float* depths,
		float* view2gaussians,
		float* colors,
		float4* rscales_opacity,
		int3* scales_sign,
		const dim3 grid,
		uint32_t* tiles_touched,
		bool prefiltered);

	// Main rasterization method.
	void render(
		const int P,
		const dim3 grid, dim3 block,
		const uint2* ranges,
		const uint32_t* point_list,
		int W, int H,
		const float focal_x, const float focal_y,
		const float principal_x, const float principal_y,
		const float sigma,
		const float* features,
		const float* view2gaussian,
		const float* viewmatrix,
		const float3* means3D,
		const float3* scales,
		const float* depths,
		const float4* rscales_opacity,
		const int3* scales_sign,
		float* final_T,
		uint32_t* n_contrib,
		const float* bg_color,
		float* out_color,
		int* n_touched);

	void duplicate(
		int P,
		int W, int H,
		const float focal_x, const float focal_y,
		const float principal_x, const float principal_y,
		const float sigma,
		const float2 *means2D,
		const float* depths,
		const float4* rscales_opacity,
		const float3* scales,
		const int3* scales_sign,
		const float* view2gaussians,
		const uint32_t* offsets,
		const int* radii,
		const float2* rects,
		uint64_t* gaussian_keys_unsorted,
		uint32_t* gaussian_values_unsorted,
		dim3 grid);

}
#endif