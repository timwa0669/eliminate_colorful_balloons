//
// Created by ti on 2020/11/9.
//

#pragma once
#define _USE_MATH_DEFINES

#include <easyx.h>
#include <cstdint>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cmath>

namespace Roadmap_direction {
    /*
     *     Naming: ODD or EVEN + Direction UP or DOWN + Direction LEFT or RIGHT
     *     Data structure: {Direction UID, Delta x position, Delta y position}.
     */
    const int ODD_UP_LEFT[2] = {-1, -1};
    const int ODD_UP_RIGHT[2] = {0, -1};
    const int ODD_DOWN_LEFT[2] = {-1, 1};
    const int ODD_DOWN_RIGHT[2] = {0, 1};

    const int EVEN_UP_LEFT[2] = {0, -1};
    const int EVEN_UP_RIGHT[2] = {1, -1};
    const int EVEN_DOWN_LEFT[2] = {0, 1};
    const int EVEN_DOWN_RIGHT[2] = {1, 1};

    enum {
        LINE_UP_RIGHT = 0,
        LINE_DOWN_LEFT,
        LINE_DOWN_RIGHT,
        LINE_UP_LEFT
    };
}

class Game {
public:
    HWND game_window_hwnd;
    int level = 1;

    const int GAME_WINDOW_WIDTH = 540;
    const int GAME_WINDOW_HEIGHT = 800;
    const int GAME_WINDOW_CENTER_X = GAME_WINDOW_WIDTH / 2;
    const int GAME_WINDOW_CENTER_Y = GAME_WINDOW_HEIGHT / 2;
    const uint8_t GAME_WINDOW_FLAGS = EW_DBLCLKS;
    const COLORREF BACKGROUND_COLOR = RGB(0x00, 0x00, 0x00);

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

    int level_map[1][9][5] = {};

    int balloon_color_id = -1;

private:
    IMAGE
            game_window_canvas,
            menubtn, balloon[7], balloon1[7], balloonlines, balloonpanel, balloonsub, bodybg, bomb, line[3], panel[7], star1, star2, status,
            donebtn, exit, nextbtn, playbtn, prev, resetbtn, setting,
            introbg,
            bg[3], sidepanel;

    const int panel_offset = 10;
    int balloonpanel_width = 0;
    int balloonpanel_height = 0;
    double panel_base_x[2] = {};
    double panel_base_y[2] = {};

    void load_assets();

    void spawn_title();

    void spawn_level();

    void inline mouse_click(int x_start, int y_start, int x_end, int y_end);

    void inline mouse_click(int x_start, int y_start, int x_end, int y_end, DWORD time_interval);

    void inline mouse_left_button_press(int x_start, int y_start, int x_end, int y_end);

    void inline mouse_left_button_press(int x_start, int y_start, int x_end, int y_end, DWORD time_interval);

    void level_generator();

    bool inline generate_necessary_balloons(int (&src_position)[2], const int (&delta_position)[2]);

    void put_balloonpanel_image();

    void put_balloon_image(int position_x, int position_y, int color_id);

    void detect_mouse_press_message();

    void put_line_image(int line_direction, int position_x, int position_y);
};
