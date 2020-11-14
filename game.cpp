//
// Created by ti on 2020/11/9.
//

#include "game.h"

Game::Game(const int argc, const char **argv) {
    game_window_hwnd = initgraph(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FLAGS);
    setbkcolor(BACKGROUND_COLOR);
    setorigin(0, 0);
    Resize(&this->game_window_canvas, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    SetWorkingImage(&this->game_window_canvas);
    srand(time(nullptr));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            level_map[level - 1][i][j] = -1;
        }
    }
    cleardevice();
    load_assets();
    balloonpanel_width = balloonpanel.getwidth() + panel_offset;
    balloonpanel_height = balloonpanel.getheight() + panel_offset;
    panel_base_x[0] = (double) GAME_WINDOW_CENTER_X - 2.5 * balloonpanel_width;
    panel_base_x[1] = (double) GAME_WINDOW_CENTER_X - 2 * balloonpanel_width;
    panel_base_y[0] = (double) GAME_WINDOW_CENTER_Y - 2.5 * balloonpanel_height;
    panel_base_y[1] = (double) GAME_WINDOW_CENTER_Y - 2 * balloonpanel_height;
    spawn_title();
}

void Game::load_assets() {
    loadimage(&menubtn, _T("./assets/ballonscreen/button/menubtn.png"));
    loadimage(&balloon1[0], _T("./assets/ballonscreen/balloon11.png"));
    loadimage(&balloon1[1], _T("./assets/ballonscreen/balloon12.png"));
    loadimage(&balloon1[2], _T("./assets/ballonscreen/balloon13.png"));
    loadimage(&balloon1[3], _T("./assets/ballonscreen/balloon14.png"));
    loadimage(&balloon1[4], _T("./assets/ballonscreen/balloon15.png"));
    loadimage(&balloon1[5], _T("./assets/ballonscreen/balloon16.png"));
    loadimage(&balloon1[6], _T("./assets/ballonscreen/balloon17.png"));
    loadimage(&balloon[0], _T("./assets/ballonscreen/balloon21.png"));
    loadimage(&balloon[1], _T("./assets/ballonscreen/balloon22.png"));
    loadimage(&balloon[2], _T("./assets/ballonscreen/balloon23.png"));
    loadimage(&balloon[3], _T("./assets/ballonscreen/balloon24.png"));
    loadimage(&balloon[4], _T("./assets/ballonscreen/balloon25.png"));
    loadimage(&balloon[5], _T("./assets/ballonscreen/balloon26.png"));
    loadimage(&balloon[6], _T("./assets/ballonscreen/balloon27.png"));
    loadimage(&balloonlines, _T("./assets/ballonscreen/balloonlines.png"));
    loadimage(&balloonpanel, _T("./assets/ballonscreen/balloonpanel.png"));
    loadimage(&balloonsub, _T("./assets/ballonscreen/balloonsub.png"));
    loadimage(&bodybg, _T("./assets/ballonscreen/bodybg.png"));
    loadimage(&balloonlines, _T("./assets/ballonscreen/balloonlines.png"));
    loadimage(&bomb, _T("./assets/ballonscreen/bomb.png"));
    loadimage(&line[0], _T("./assets/ballonscreen/line.png"));
    rotateimage(&line[1], &line[0], 0.25 * M_PI, BLACK, true, true);
    rotateimage(&line[2], &line[0], 0.75 * M_PI, BLACK, true, true);
    loadimage(&panel[0], _T("./assets/ballonscreen/panel1.png"));
    loadimage(&panel[1], _T("./assets/ballonscreen/panel2.png"));
    loadimage(&panel[2], _T("./assets/ballonscreen/panel3.png"));
    loadimage(&panel[3], _T("./assets/ballonscreen/panel4.png"));
    loadimage(&panel[4], _T("./assets/ballonscreen/panel5.png"));
    loadimage(&panel[5], _T("./assets/ballonscreen/panel6.png"));
    loadimage(&panel[6], _T("./assets/ballonscreen/panel7.png"));
    loadimage(&star1, _T("./assets/ballonscreen/star1.png"));
    loadimage(&star2, _T("./assets/ballonscreen/star2.png"));
    loadimage(&status, _T("./assets/ballonscreen/status.png"));
    loadimage(&donebtn, _T("./assets/buttons/donebtn.png"));
    loadimage(&exit, _T("./assets/buttons/exit.png"));
    loadimage(&nextbtn, _T("./assets/buttons/nextbtn.png"));
    loadimage(&playbtn, _T("./assets/buttons/playbtn.png"));
    loadimage(&prev, _T("./assets/buttons/prev.png"));
    loadimage(&resetbtn, _T("./assets/buttons/resetbtn.png"));
    loadimage(&setting, _T("./assets/buttons/setting.png"));
    loadimage(&introbg, _T("./assets/introbg.png"));
    loadimage(&bg[0], _T("./assets/title/bg.jpg"));
    loadimage(&bg[1], _T("./assets/title/bg.png"));
    loadimage(&bg[2], _T("./assets/title/bg1.png"));
    loadimage(&sidepanel, _T("./assets/title/sidepanel.png"));
}

void Game::spawn_title() {
    clear_canvas();
    put_image(0, 0, &bg[1]);
    int playbtn_x_start = GAME_WINDOW_WIDTH - sidepanel.getwidth() / 2 - playbtn.getwidth() / 2;
    int playbtn_y_start = 588;
    put_image(GAME_WINDOW_WIDTH - sidepanel.getwidth(), 579, &sidepanel, BLACK);
    put_image(playbtn_x_start, playbtn_y_start, &playbtn, BLACK);
    update_window();
    mouse_click(playbtn_x_start, playbtn_y_start, playbtn_x_start + playbtn.getwidth(), playbtn_y_start + playbtn.getheight());
    spawn_level();
}

Game::~Game() {
    closegraph();
}

void Game::update_window() {
    IMAGE *current_working_image = GetWorkingImage();
    SetWorkingImage();
    putimage(0, 0, &this->game_window_canvas, SRCCOPY);
    SetWorkingImage(current_working_image);
}

void Game::clear_canvas() {
    IMAGE new_img(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    game_window_canvas = new_img;
}

void Game::spawn_level() {
    level_generator();
    IMAGE level_canvas_bk = this->game_window_canvas;
    put_image(GAME_WINDOW_CENTER_X - panel[2].getwidth() / 2,
              GAME_WINDOW_CENTER_Y - panel[2].getheight() / 2,
              &panel[2],
              BLACK);
    update_window();
    mouse_click(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    this->game_window_canvas = level_canvas_bk;
    update_window();
    mouse_click(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    detect_mouse_press_message();
}

void inline Game::mouse_click(const int x_start, const int y_start, const int x_end, const int y_end) {
    for (MOUSEMSG mouse_event = GetMouseMsg(); ;mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONDOWN &&
            mouse_event.x >= x_start &&
            mouse_event.x <= x_end &&
            mouse_event.y >= y_start &&
            mouse_event.y <= y_end) {
            break;
        }
    }
}

void inline Game::mouse_click(const int x_start, const int y_start, const int x_end, const int y_end, const DWORD time_interval) {
    for (MOUSEMSG mouse_event = GetMouseMsg(); ;Sleep(time_interval), mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONDOWN &&
            mouse_event.x >= x_start &&
            mouse_event.x <= x_end &&
            mouse_event.y >= y_start &&
            mouse_event.y <= y_end) {
            break;
        }
    }
}

void Game::level_generator() {
    clear_canvas();
    put_image(0, 0, &bg[0]);
    put_image(0, 0, &bg[2], BLACK);
    balloon_color_id = rand() % 7;
    put_balloonpanel_image();
    int balloonpanel_clickable_width = balloonpanel.getwidth() / 2;
    int balloonpanel_clickable_height = balloonpanel.getheight() / 2;
    int starter_position[2] = {
            rand() % 5,
            rand() % 9
    };
    while (!level_map_base[level - 1][starter_position[1]][starter_position[0]]) {
        starter_position[0] = rand() % 5;
        starter_position[1] = rand() % 9;
    }
    bool position_false[4] = {};
    for (int i = 0, direction = rand() % 4; i < 10; ) {
        if (position_false[0] &&
            position_false[1] &&
            position_false[2] &&
            position_false[3]) {
            position_false[0] = false;
            position_false[1] = false;
            position_false[2] = false;
            position_false[3] = false;
            i = 0;
            starter_position[0] = rand() % 5;
            starter_position[1] = rand() % 9;
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 5; k++) {
                    level_map[level - 1][j][k] = -1;
                }
            }
        }
        using namespace Roadmap_direction;
        if (starter_position[1] % 2 == 0) {
            switch (direction) {
                case 0:
                    if (generate_necessary_balloons(starter_position, ODD_UP_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[0] = true;
                    break;
                case 1:
                    if (generate_necessary_balloons(starter_position, ODD_UP_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[1] = true;
                    break;
                case 2:
                    if (generate_necessary_balloons(starter_position, ODD_DOWN_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[2] = true;
                    break;
                case 3:
                    if (generate_necessary_balloons(starter_position, ODD_DOWN_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[3] = true;
                    break;
                default:
                    break;
            }
        } else {
            switch (direction) {
                case 0:
                    if (generate_necessary_balloons(starter_position, EVEN_UP_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[0] = true;
                    break;
                case 1:
                    if (generate_necessary_balloons(starter_position, EVEN_UP_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[1] = true;
                    break;
                case 2:
                    if (generate_necessary_balloons(starter_position, EVEN_DOWN_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[2] = true;
                    break;
                case 3:
                    if (generate_necessary_balloons(starter_position, EVEN_DOWN_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[3] = true;
                    break;
                default:
                    break;
            }
        }
        direction = rand() % 4;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (level_map_base[level - 1][i][j] &&
                level_map[level - 1][i][j] == -1) {
                put_balloon_image(j, i, rand() % 7);
            }
        }
    }
}

bool inline Game::generate_necessary_balloons(int (&src_position)[2], const int (&delta_position)[2]) {
    int next_position[2] = {
            src_position[0] + delta_position[0],
            src_position[1] + delta_position[1]
    };
    if (next_position[0] < 5 &&
        next_position[0] >= 0 &&
        next_position[1] >= 0 &&
        next_position[1] < 9 &&
        level_map[level - 1][next_position[1]][next_position[0]] == -1 &&
        level_map_base[level - 1][next_position[1]][next_position[0]]) {
        src_position[0] += delta_position[0];
        src_position[1] += delta_position[1];
        level_map[level - 1][next_position[1]][next_position[0]] = balloon_color_id;
        put_balloon_image(src_position[0], src_position[1], balloon_color_id);
        return true;
    }
    return false;
}

void Game::put_balloonpanel_image() {
    for (int i = 0; i < 9; i += 2) {
        for (int j = 0; j < 5; j++) {
            if (level_map_base[level - 1][i][j]) {
                put_image((int) (panel_base_x[0] + j * balloonpanel_width),
                          (int) (panel_base_y[0] + (double) i / 2 * balloonpanel_height),
                          &balloonpanel,
                          BLACK);
            }
        }
    }
    for (int i = 1; i < 9; i += 2) {
        for (int j = 0; j < 5; j++) {
            if (level_map_base[level - 1][i][j]) {
                put_image((int) (panel_base_x[1] + j * balloonpanel_width),
                          (int) (panel_base_y[1] + ((double) (i - 1) / 2) * balloonpanel_height),
                          &balloonpanel,
                          BLACK);
            }
        }
    }
}

void Game::put_balloon_image(const int position_x, const int position_y, const int color_id) {
    if (position_y % 2) {
        put_image((int) (panel_base_x[1] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[color_id].getwidth()) / 2),
                  (int) (panel_base_y[1] + ((double) (position_y + 1) / 2 - 1) * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[color_id].getheight()) / 2 + 5),
                  &balloon1[color_id],
                  BLACK);
    } else {
        put_image((int) (panel_base_x[0] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[color_id].getwidth()) / 2),
                  (int) (panel_base_y[0] + (double) position_y / 2 * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[color_id].getheight()) / 2 + 5),
                  &balloon1[color_id],
                  BLACK);
    }
}

void Game::detect_mouse_press_message() {
}

void inline Game::mouse_left_button_press(const int x_start, const int y_start, const int x_end, const int y_end) {

}

void inline Game::mouse_left_button_press(const int x_start, const int y_start, const int x_end, const int y_end, const DWORD time_interval) {

}

void Game::put_line_image(int line_direction, int position_x, int position_y) {
    switch (line_direction) {
        using namespace Roadmap_direction;
        case LINE_DOWN_LEFT:
            position_x -= 1;
            position_y += 1;
        case LINE_UP_RIGHT:
            if (position_y % 2) {
                put_image((int) (panel_base_x[1] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) (position_y + 1) / 2 - 1) * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 - (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
            } else {
                put_image((int) (panel_base_x[0] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) position_y / 2 * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 - (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
            }
            break;
        case LINE_UP_LEFT:
            position_x -= 1;
            position_y -= 1;
        case LINE_DOWN_RIGHT:
            if (position_y % 2) {
                put_image((int) (panel_base_x[1] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) (position_y + 1) / 2 - 1) * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
            } else {
                put_image((int) (panel_base_x[0] + position_x * balloonpanel_width + (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) position_y / 2 * balloonpanel_height + (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
            }
            break;
        default:
            break;
    }
}