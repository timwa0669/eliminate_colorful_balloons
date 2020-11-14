//
// Created by ti on 2020/11/9.
//

#pragma once

#include <easyx.h>
#include <cstdint>
#include <windows.h>
#include <random>
#include <ctime>

const int GAME_WINDOW_WIDTH = 540;
const int GAME_WINDOW_HEIGHT = 800;
const int GAME_WINDOW_CENTER_X = GAME_WINDOW_WIDTH / 2;
const int GAME_WINDOW_CENTER_Y = GAME_WINDOW_HEIGHT / 2;
const uint8_t GAME_WINDOW_FLAGS = EW_DBLCLKS;
const COLORREF BACKGROUND_COLOR = RGB(0x00, 0x00, 0x00);

class Game {
public:
    HWND game_window_hwnd;

    Game(int argc, const char **argv);

    ~Game();

    void put_image(int dstX, int dstY, IMAGE *pSrcImg);

    void put_image(IMAGE *pDstImg, int dstX, int dstY, IMAGE *pSrcImg);

    void put_image(int dstX, int dstY, int dstWidth, int dstHeight, IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight, UINT transparentcolor);

    void put_image(IMAGE *pDstImg, int dstX, int dstY, int dstWidth, int dstHeight, IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight, UINT transparentcolor);

    void put_image(int dstX, int dstY, IMAGE *pSrcImg, UINT transparentcolor);

    void put_image(IMAGE *pDstImg, int dstX, int dstY, IMAGE *pSrcImg, UINT transparentcolor);

    void put_image(int dstX, int dstY, int dstWidth, int dstHeight, IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight);

    void put_image(IMAGE *pDstImg, int dstX, int dstY, int dstWidth, int dstHeight, IMAGE *pSrcImg, int srcX, int srcY, int srcWidth, int srcHeight);

    void update_window();

    void clear_canvas();

    bool level_map_base[1][9][5] = {
            {
                    {false, true, false, true, false},
                    {true, true, true, true, false},
                    {true, true, true, true, true},
                    {true, true, true, true, false},
                    {true, true, true, true, true},
                    {true, true, true, true, false},
                    {true, true, true, true, true},
                    {true, true, true, true, false},
                    {false, true, false, true, false}
            }
    };



private:
    IMAGE
            game_window_canvas,
            menubtn, balloon[7], balloon1[7], balloonlines, balloonpanel, balloonsub, bodybg, bomb, line, panel[7], star, status,
            donebtn, exit, nextbtn, playbtn, prev, resetbtn, setting,
            introbg,
            bg[3], sidepanel;

    void load_assets();

    void spawn_title();

    void spawn_selector();

    void spawn_level(int level);

    void mouse_click(int x_start, int y_start, int x_end, int y_end);

    void mouse_click(int x_start, int y_start, int x_end, int y_end, DWORD time_interval);

    void level_generator(int level, int balloon_color_id);

    std::default_random_engine rand_generator;
};
