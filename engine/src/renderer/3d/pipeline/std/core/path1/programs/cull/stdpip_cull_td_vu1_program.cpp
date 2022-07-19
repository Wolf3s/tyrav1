/*
# ______       ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "debug/debug.hpp"
#include "renderer/3d/pipeline/std/core/path1/programs/cull/stdpip_cull_td_vu1_program.hpp"

extern u32 StdpipVU1Cull_TD_CodeStart __attribute__((section(".vudata")));
extern u32 StdpipVU1Cull_TD_CodeEnd __attribute__((section(".vudata")));

namespace Tyra {

StdpipCullTDVU1Program::StdpipCullTDVU1Program()
    : StdpipVU1Program(StdpipCullTextureDirLights, &StdpipVU1Cull_TD_CodeStart,
                       &StdpipVU1Cull_TD_CodeEnd,
                       ((u64)GIF_REG_ST) << 0 | ((u64)GIF_REG_RGBAQ) << 4 |
                           ((u64)GIF_REG_XYZ2) << 8,
                       3, 4) {}

StdpipCullTDVU1Program::~StdpipCullTDVU1Program() {}

std::string StdpipCullTDVU1Program::getStringName() const {
  return std::string("Cull - LTC");
}

void StdpipCullTDVU1Program::addProgramQBufferDataToPacket(
    packet2_t* packet, StdpipQBuffer* qbuffer) const {
  u32 addr = VU1_VERT_DATA_ADDR;

  // Add vertices
  packet2_utils_vu_add_unpack_data(packet, addr, qbuffer->vertices,
                                   qbuffer->size, true);
  addr += qbuffer->size;

  // Add sts
  packet2_utils_vu_add_unpack_data(packet, addr, qbuffer->sts, qbuffer->size,
                                   true);
  addr += qbuffer->size;

  // Add normal
  packet2_utils_vu_add_unpack_data(packet, addr, qbuffer->normals,
                                   qbuffer->size, true);

  // Add colors
  if (qbuffer->bag->color->single == nullptr) {
    addr += qbuffer->size;
    packet2_utils_vu_add_unpack_data(packet, addr, qbuffer->colors,
                                     qbuffer->size, true);
  }
}

}  // namespace Tyra