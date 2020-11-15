//
// Created by ti on 2020/11/15.
//

#include "balloon.h"
#include "game.h"

void Balloon::reset() {
    this->balloon_color_id = -1;
    this->map_x = 0;
    this->map_y = 0;
    this->gw_x = 0;
    this->gw_y = 0;
}