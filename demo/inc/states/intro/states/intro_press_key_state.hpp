/*
# ______       ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#pragma once

#include "state/state.hpp"
#include "../intro_state_type.hpp"
#include "renderer/core/2d/sprite/sprite.hpp"
#include "time/timer.hpp"

using Tyra::Sprite;
using Tyra::Texture;
using Tyra::Timer;
using Tyra::Vec2;

namespace Demo {

class IntroPressKeyState : public State<IntroStateType> {
 public:
  IntroPressKeyState(Engine* t_engine);
  ~IntroPressKeyState();

  const IntroStateType& getState() const { return state; }

  const bool& wantFinish() const { return _wantFinish; };

  void onStart();

  void update();

  /** @return Next game state */
  IntroStateType onFinish();

 private:
  void updateMap();

  IntroStateType state;
  bool _wantFinish;
  bool initialized;

  const static u8 mapRows = 3;
  const static u8 mapCols = 3;

  Vec2 mapPosition;
  u8 mapDirection;

  Texture* mapTextures[mapRows][mapCols];
  Sprite* mapSprites[mapRows][mapCols];
};

}  // namespace Demo