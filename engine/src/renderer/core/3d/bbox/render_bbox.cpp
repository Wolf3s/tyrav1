/*
# ______       ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2020, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include <string>
#include <sstream>
#include "renderer/core/3d/bbox/render_bbox.hpp"

namespace Tyra {

RenderBBox::RenderBBox(CoreBBox** t_bboxes, const u32& count)
    : CoreBBox(t_bboxes, count) {}

RenderBBox::RenderBBox(const std::vector<CoreBBox>& t_bboxes,
                       const u32& startIndex, const u32& stopIndex)
    : CoreBBox(t_bboxes, startIndex, stopIndex) {}

RenderBBox::RenderBBox(Vec4* t_vertices, u32* faces, u32 count)
    : CoreBBox(t_vertices, faces, count) {}

RenderBBox::RenderBBox(Vec4* t_vertices, u32 count)
    : CoreBBox(t_vertices, count) {}

RenderBBox::RenderBBox(Vec4* t_vertices) : CoreBBox(t_vertices) {}

/**
 * @brief Frustum checker for renderer.
 * Background: We want to really put as low as possible polys to clipper.
 * So we are doing magic trick. If BBox is partially inside frustum (clipper),
 * we are adding some margins, and checking again if it really needs clipping,
 * because "Cull" renderer can handle easy clip cases and its faster.
 */
CoreBBoxFrustum RenderBBox::clipIsInFrustum(const Plane* frustumPlanes,
                                            const M4x4& model) const {
  auto result = isInFrustum(frustumPlanes, model);

  if (result != PARTIALLY_IN_FRUSTUM) {
    return result;
  }

  // Oh no, it probably needs clipping

  float margins[6];  // This probably needs more calibration

  margins[0] = -15.0F;  // Top
  margins[1] = -10.0F;  // BOTTOM
  margins[2] = -25.0F;  // LEFT
  margins[3] = -25.0F;  // RIGHT
  margins[4] = -10.0F;  // NEAR
  margins[5] = -10.0F;  // FAR

  return isInFrustum(frustumPlanes, model, margins);  // Let's check it again
}

}  // namespace Tyra