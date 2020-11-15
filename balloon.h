//
// Created by ti on 2020/11/15.
//

#pragma once

class Balloon {
public:
    int balloon_color_id = -1;
    int map_x = 0;
    int map_y = 0;
    int gw_x = 0;
    int gw_y = 0;
    bool is_linked = false;

    void reset();
};
