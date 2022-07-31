/*
# ______       ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "states/game/player/player.hpp"

namespace Demo {

Player::Player(Engine* engine)
    : position(0.0F),
      weapon(&engine->renderer.core.texture.repository),
      camera(&engine->pad) {
  staticPairs.push_back(new RendererStaticPair{weapon.mesh, weapon.options});
  pad = &engine->pad;
  position = Vec4(3.0F, 3.0F, 0.0F);
  camera.lookAt = Vec4(0.0F, 0.0F, -30.0F);
  speed = 0.5F;
}

Player::~Player() {
  for (auto pair : staticPairs) {
    delete pair;
  }
  for (auto pair : dynamicPairs) {
    delete pair;
  }
}

void Player::update() {
  handlePlayerPosition();
  camera.update(position);
  weapon.update();
}

void Player::handlePlayerPosition() {
  const auto& leftJoy = pad->getLeftJoyPad();

  auto normalizedCamera = Vec4(camera.unitCircle);
  normalizedCamera.normalize();
  normalizedCamera *= speed;

  Vec4 nextPosition(position);

  if (leftJoy.v <= 100) {
    nextPosition.x += normalizedCamera.x;
    nextPosition.z += normalizedCamera.z;
  } else if (leftJoy.v >= 200) {
    nextPosition.x += -normalizedCamera.x;
    nextPosition.z += -normalizedCamera.z;
  }
  if (leftJoy.h <= 100) {
    nextPosition.x += normalizedCamera.z;
    nextPosition.z += -normalizedCamera.x;
  } else if (leftJoy.h >= 200) {
    nextPosition.x += -normalizedCamera.z;
    nextPosition.z += normalizedCamera.x;
  }

  position = nextPosition;

  camera.position = position;
}

}  // namespace Demo