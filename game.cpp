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
    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 5; k++) {
            level_map[level - 1][j][k].reset();
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
    mouse_click(playbtn_x_start, playbtn_y_start, playbtn_x_start + playbtn.getwidth(),
                playbtn_y_start + playbtn.getheight());
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
/*

    put_line_image(Roadmap_direction::LINE_UP_LEFT, 2, 3);
    put_line_image(Roadmap_direction::LINE_DOWN_LEFT, 2, 3);
    put_line_image(Roadmap_direction::LINE_UP_RIGHT, 2, 3);
    put_line_image(Roadmap_direction::LINE_DOWN_RIGHT, 2, 3);

    put_line_image(Roadmap_direction::LINE_UP_LEFT, 4, 6);
    put_line_image(Roadmap_direction::LINE_DOWN_LEFT, 4, 6);
    put_line_image(Roadmap_direction::LINE_UP_RIGHT, 4, 6);
    put_line_image(Roadmap_direction::LINE_DOWN_RIGHT, 4, 6);
    update_window();
    mouse_click(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
*/
    mouse_left_button_press_event();
}

void inline Game::mouse_click(const int x_start, const int y_start, const int x_end, const int y_end) {
    MOUSEMSG mouse_event = GetMouseMsg();
    for (;; mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONDOWN &&
            mouse_event.x >= x_start &&
            mouse_event.x <= x_end &&
            mouse_event.y >= y_start &&
            mouse_event.y <= y_end) {
            break;
        }
    }
    for (;; mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONUP &&
            mouse_event.x >= x_start &&
            mouse_event.x <= x_end &&
            mouse_event.y >= y_start &&
            mouse_event.y <= y_end) {
            break;
        }
    }
}

void inline
Game::mouse_click(const int x_start, const int y_start, const int x_end, const int y_end, const DWORD time_interval) {
    MOUSEMSG mouse_event = GetMouseMsg();
    for (;; Sleep(time_interval), mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONDOWN &&
            mouse_event.x >= x_start &&
            mouse_event.x <= x_end &&
            mouse_event.y >= y_start &&
            mouse_event.y <= y_end) {
            break;
        }
    }
    for (;; Sleep(time_interval), mouse_event = GetMouseMsg()) {
        if (mouse_event.uMsg == WM_LBUTTONUP &&
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
    int starter_position[2] = {
            rand() % 5,
            rand() % 9
    };
    while (!level_map_base[level - 1][starter_position[1]][starter_position[0]]) {
        starter_position[0] = rand() % 5;
        starter_position[1] = rand() % 9;
    }
    bool position_false[4] = {};
    for (int i = 0, direction = rand() % 4; i < generated_essential_balloon_count[level - 1];) {
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
                    level_map[level - 1][j][k].reset();
                }
            }
        }
        using namespace Roadmap_direction;
        if (starter_position[1] % 2 == 0) {
            switch (direction) {
                case 0:
                    if (generate_essential_balloons(starter_position, ODD_UP_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[0] = true;
                    break;
                case 1:
                    if (generate_essential_balloons(starter_position, ODD_UP_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[1] = true;
                    break;
                case 2:
                    if (generate_essential_balloons(starter_position, ODD_DOWN_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[2] = true;
                    break;
                case 3:
                    if (generate_essential_balloons(starter_position, ODD_DOWN_RIGHT)) {
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
                    if (generate_essential_balloons(starter_position, EVEN_UP_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[0] = true;
                    break;
                case 1:
                    if (generate_essential_balloons(starter_position, EVEN_UP_RIGHT)) {
                        i++;
                        continue;
                    }
                    position_false[1] = true;
                    break;
                case 2:
                    if (generate_essential_balloons(starter_position, EVEN_DOWN_LEFT)) {
                        i++;
                        continue;
                    }
                    position_false[2] = true;
                    break;
                case 3:
                    if (generate_essential_balloons(starter_position, EVEN_DOWN_RIGHT)) {
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
                level_map[level - 1][i][j].balloon_color_id == -1) {
                level_map[level - 1][i][j].balloon_color_id = rand() % 7;
                level_map[level - 1][i][j].map_x = j;
                level_map[level - 1][i][j].map_y = i;
                map_position_to_game_window_position(level_map[level - 1][i][j]);
                put_image(level_map[level - 1][i][j].gw_x,
                          level_map[level - 1][i][j].gw_y,
                          &balloon1[level_map[level - 1][i][j].balloon_color_id],
                          BLACK);
            }
        }
    }
}

bool inline Game::generate_essential_balloons(int (&src_position)[2], const int (&delta_position)[2]) {
    int next_position[2] = {
            src_position[0] + delta_position[0],
            src_position[1] + delta_position[1]
    };
    if (next_position[0] < 5 &&
        next_position[0] >= 0 &&
        next_position[1] >= 0 &&
        next_position[1] < 9 &&
        level_map[level - 1][next_position[1]][next_position[0]].balloon_color_id == -1 &&
        level_map_base[level - 1][next_position[1]][next_position[0]]) {
        src_position[0] += delta_position[0];
        src_position[1] += delta_position[1];
        level_map[level - 1][next_position[1]][next_position[0]].balloon_color_id = balloon_color_id;
        level_map[level - 1][next_position[1]][next_position[0]].map_x = src_position[0];
        level_map[level - 1][next_position[1]][next_position[0]].map_y = src_position[1];
        map_position_to_game_window_position(level_map[level - 1][next_position[1]][next_position[0]]);
        put_image(level_map[level - 1][next_position[1]][next_position[0]].gw_x,
                  level_map[level - 1][next_position[1]][next_position[0]].gw_y,
                  &balloon1[balloon_color_id],
                  BLACK);
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

void Game::mouse_left_button_press_event() {
    //FlushMouseMsgBuffer();
    MOUSEMSG mouse_event = GetMouseMsg();
    Balloon tmp, last_tmp;
    bool selected_other_balls = false;
    for (int stage = 0, linked_count = 0; linked_count == 0 || stage != 0;) {
        stage_0:
        for (mouse_event = GetMouseMsg(); stage == 0; mouse_event = GetMouseMsg()) {
            if (linked_count > 0) {
                goto stopped_mouse_event;
            }
            if (mouse_event.uMsg == WM_LBUTTONDOWN && mouse_event.mkLButton) {
                stage++;
                goto stage_1;
            }
        }
        stage_1:
        for (mouse_event = GetMouseMsg(); stage == 1; mouse_event = GetMouseMsg()) {
            for (uint8_t i = 0; i < 9; i++) {
                for (uint8_t j = 0; j < 5; j++) {
                    tmp.map_x = j;
                    tmp.map_y = i;
                    map_position_to_game_window_position(tmp);
                    if ((float) mouse_event.x >= (float) tmp.gw_x + (float) balloonpanel_width / 4 &&
                        (float) mouse_event.x <= (float) tmp.gw_x + (float) balloonpanel_width / 4 * 3 &&
                        (float) mouse_event.y >= (float) tmp.gw_y + (float) balloonpanel_height / 4 &&
                        (float) mouse_event.y <= (float) tmp.gw_y + (float) balloonpanel_height / 4 * 3 &&
                        level_map_base[level - 1][tmp.map_y][tmp.map_x]) {
                        stage++;
                        last_tmp = tmp;
                        if (level_map[level - 1][tmp.map_y][tmp.map_x].balloon_color_id == balloon_color_id) {
                            correct_linked_balloon_count++;
                        } else {
                            selected_other_balls = true;
                        }
                        goto stage_2;
                    }
                }
            }
            if (mouse_event.uMsg == WM_LBUTTONUP || !mouse_event.mkLButton) {
                stage = 0;
                goto stage_0;
            }
        }
        stage_2:
        for (mouse_event = GetMouseMsg(); stage == 2; mouse_event = GetMouseMsg()) {
            if (mouse_event.uMsg == WM_LBUTTONUP || !mouse_event.mkLButton) {
                stage = 0;
                goto stage_0;
            }
            for (uint8_t i = 0; i < 9; i++) {
                for (uint8_t j = 0; j < 5; j++) {
                    tmp.map_x = j;
                    tmp.map_y = i;
                    map_position_to_game_window_position(tmp);
                    if ((float) mouse_event.x >= (float) tmp.gw_x + (float) balloonpanel_width / 4 &&
                        (float) mouse_event.x <= (float) tmp.gw_x + (float) balloonpanel_width / 4 * 3 &&
                        (float) mouse_event.y >= (float) tmp.gw_y + (float) balloonpanel_height / 4 &&
                        (float) mouse_event.y <= (float) tmp.gw_y + (float) balloonpanel_height / 4 * 3 &&
                        level_map_base[level - 1][tmp.map_y][tmp.map_x] &&
                        !level_map[level - 1][tmp.map_y][tmp.map_x].is_linked) {
                        int tmp_direction[2] = {tmp.map_x - last_tmp.map_x, tmp.map_y - last_tmp.map_y};
                        int roadmap_direction = get_roadmap_direction(tmp_direction, last_tmp.map_y);
                        if (roadmap_direction == -1) {
                            goto stage_2;
                        }
                        put_line_image(get_line_direction(roadmap_direction), last_tmp.map_x, last_tmp.map_y);
                        linked_count++;
                        level_map[level - 1][tmp.map_y][tmp.map_x].is_linked = true;
                        level_map[level - 1][last_tmp.map_y][last_tmp.map_x].is_linked = true;
                        if (level_map[level - 1][tmp.map_y][tmp.map_x].balloon_color_id == balloon_color_id) {
                            correct_linked_balloon_count++;
                        } else {
                            selected_other_balls = true;
                        }
                        update_window();
                        last_tmp = tmp;
                    }
                    //break;
                }
            }
        }
    }
    stopped_mouse_event:
    if (correct_linked_balloon_count >= target_balloon_linked_count[level - 1] && !selected_other_balls) {
        win_process();
    } else {
        fail_process();
    }

}

int Game::get_line_direction(int roadmap_direction) {
    switch (roadmap_direction) {
        using namespace Roadmap_direction;
        case 0:
        case 4:
            return LINE_UP_LEFT;
        case 1:
        case 5:
            return LINE_UP_RIGHT;
        case 2:
        case 6:
            return LINE_DOWN_LEFT;
        case 3:
        case 7:
            return LINE_DOWN_RIGHT;
        default:
            return -1;
    }
}

int Game::get_roadmap_direction(const int (&delta_position)[2], const int position_y) {
    if (position_y % 2) {
        switch (delta_position[1]) {
            case -1:
                switch (delta_position[0]) {
                    case 0:
                        return 4;
                    case 1:
                        return 5;
                    default:
                        break;
                }
                break;
            case 1:
                switch (delta_position[0]) {
                    case 0:
                        return 6;
                    case 1:
                        return 7;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    } else {
        switch (delta_position[1]) {
            case -1:
                switch (delta_position[0]) {
                    case -1:
                        return 0;
                    case 0:
                        return 1;
                    default:
                        break;
                }
                break;
            case 1:
                switch (delta_position[0]) {
                    case -1:
                        return 2;
                    case 0:
                        return 3;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}

void Game::put_line_image(int line_direction, int position_x, int position_y) {
    if (position_y % 2) {
        switch (line_direction) {
            using namespace Roadmap_direction;
            case LINE_DOWN_LEFT:
                put_image((int) (panel_base_x[1] + (position_x - 0.5) * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) (position_y + 2) / 2 - 1) * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 -
                                 (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
                break;
            case LINE_UP_RIGHT:
                put_image((int) (panel_base_x[1] + position_x * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) (position_y + 1) / 2 - 1) * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 -
                                 (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
                break;
            case LINE_UP_LEFT:
                put_image((int) (panel_base_x[1] + (position_x - 0.5) * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) position_y / 2 - 1) * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
                break;
            case LINE_DOWN_RIGHT:
                put_image((int) (panel_base_x[1] + position_x * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[1] + ((double) (position_y + 1) / 2 - 1) * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
                break;
            default:
                break;
        }
    } else {
        switch (line_direction) {
            using namespace Roadmap_direction;
            case LINE_DOWN_LEFT:
                put_image((int) (panel_base_x[0] + (position_x - 0.5) * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) (position_y + 1) / 2 * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 -
                                 (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
                break;
            case LINE_UP_RIGHT:
                put_image((int) (panel_base_x[0] + position_x * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) position_y / 2 * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10 -
                                 (double) line[1].getheight() / 2),
                          &line[1],
                          BLACK);
                break;
            case LINE_UP_LEFT:
                put_image((int) (panel_base_x[0] + (position_x - 0.5) * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) (position_y - 1) / 2 * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
                break;
            case LINE_DOWN_RIGHT:
                put_image((int) (panel_base_x[0] + position_x * balloonpanel_width +
                                 (double) (balloonpanel.getwidth() - balloon1[0].getwidth()) / 2 + 5),
                          (int) (panel_base_y[0] + (double) position_y / 2 * balloonpanel_height +
                                 (double) (balloonpanel.getheight() - balloon1[0].getheight()) / 2 + 10),
                          &line[2],
                          BLACK);
                break;
            default:
                break;
        }
    }
}

void Game::map_position_to_game_window_position(Balloon &target_balloon) {
    if (target_balloon.map_y % 2) {
        target_balloon.gw_x = (int) (panel_base_x[1] + target_balloon.map_x * balloonpanel_width +
                                     (double) (balloonpanel.getwidth() -
                                               balloon1[target_balloon.balloon_color_id].getwidth()) / 2);
        target_balloon.gw_y = (int) (panel_base_y[1] +
                                     ((double) (target_balloon.map_y + 1) / 2 - 1) * balloonpanel_height +
                                     (double) (balloonpanel.getheight() -
                                               balloon1[target_balloon.balloon_color_id].getheight()) / 2 + 5);
    } else {
        target_balloon.gw_x = (int) (panel_base_x[0] + target_balloon.map_x * balloonpanel_width +
                                     (double) (balloonpanel.getwidth() -
                                               balloon1[target_balloon.balloon_color_id].getwidth()) / 2);
        target_balloon.gw_y = (int) (panel_base_y[0] + (double) target_balloon.map_y / 2 * balloonpanel_height +
                                     (double) (balloonpanel.getheight() -
                                               balloon1[target_balloon.balloon_color_id].getheight()) / 2 + 5);
    }
}

void Game::win_process() {
    put_image(GAME_WINDOW_CENTER_X - panel[1].getwidth() / 2,
              GAME_WINDOW_CENTER_Y - panel[1].getheight() / 2,
              &panel[1],
              BLACK);
    update_window();
    mouse_click(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
}

void Game::fail_process() {
    put_image(GAME_WINDOW_CENTER_X - panel[0].getwidth() / 2,
              GAME_WINDOW_CENTER_Y - panel[0].getheight() / 2,
              &panel[0],
              BLACK);
    update_window();
    mouse_click(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
}