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
    rand_generator.seed(time(nullptr));
    cleardevice();
    load_assets();
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
    loadimage(&line, _T("./assets/ballonscreen/line.png"));
    loadimage(&panel[0], _T("./assets/ballonscreen/panel1.png"));
    loadimage(&panel[1], _T("./assets/ballonscreen/panel2.png"));
    loadimage(&panel[2], _T("./assets/ballonscreen/panel3.png"));
    loadimage(&panel[3], _T("./assets/ballonscreen/panel4.png"));
    loadimage(&panel[4], _T("./assets/ballonscreen/panel5.png"));
    loadimage(&panel[5], _T("./assets/ballonscreen/panel6.png"));
    loadimage(&panel[6], _T("./assets/ballonscreen/panel7.png"));
    loadimage(&star, _T("./assets/ballonscreen/star.png"));
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
    spawn_level(1);
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

void Game::spawn_level(const int level) {
    clear_canvas();
    put_image(0, 0, &bg[0]);
    put_image(0, 0, &bg[2], BLACK);
    std::uniform_int_distribution<int> balloon_rand_distribution(0, 6);
    int balloon_color_id = balloon_rand_distribution(rand_generator);
    level_generator(level, balloon_color_id);
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
}

void Game::spawn_selector() {

}

void Game::mouse_click(const int x_start, const int y_start, const int x_end, const int y_end) {
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

void Game::mouse_click(int x_start, int y_start, int x_end, int y_end, DWORD time_interval) {
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

void Game::level_generator(const int level, const int balloon_color_id) {
    //Generate balloon panel.
    int panel_offset = 10;
    int balloonpanel_width = balloonpanel.getwidth() + panel_offset;
    int balloonpanel_height = balloonpanel.getheight() + panel_offset;
    double panel_base_x[2] = {(double) GAME_WINDOW_CENTER_X - 2.5 * balloonpanel_width, (double) GAME_WINDOW_CENTER_X - 2 * balloonpanel_width};
    double panel_base_y[2] = {(double) GAME_WINDOW_CENTER_Y - 2.5 * balloonpanel_height, (double) GAME_WINDOW_CENTER_Y - 2 * balloonpanel_height};
    for (int i = 1; i <= 9; i += 2) {
        for (int j = 1; j <= 5; j++) {
            if (level_map_base[level - 1][i - 1][j - 1]) {
                put_image((int) (panel_base_x[0] + (j - 1) * balloonpanel_width),
                          (int) (panel_base_y[0] + (double) (i - 1) / 2 * balloonpanel_height),
                          &balloonpanel,
                          BLACK);
                put_image((int) (panel_base_x[0] + (j - 1) * balloonpanel_width + (double) (90 - 60) / 2),
                          (int) (panel_base_y[0] + (double) (i - 1) / 2 * balloonpanel_height + (double) (90 - 75) / 2),
                          &balloon[balloon_color_id],
                          BLACK);
            }
        }
    }
    for (int i = 2; i <= 9; i += 2) {
        for (int j = 1; j <= 5; j++) {
            if (level_map_base[level - 1][i - 1][j - 1]) {
                put_image((int) (panel_base_x[1] + (j - 1) * balloonpanel_width),
                          (int) (panel_base_y[1] + ((double) i / 2 - 1) * balloonpanel_height),
                          &balloonpanel,
                          BLACK);
                put_image((int) (panel_base_x[1] + (j - 1) * balloonpanel_width + (double) (90 - 60) / 2),
                          (int) (panel_base_y[1] + ((double) i / 2 - 1) * balloonpanel_height + (double) (90 - 75) / 2),
                          &balloon[balloon_color_id],
                          BLACK);
            }
        }
    }
    int balloonpanel_clickable_width = balloonpanel.getwidth() / 2;
    int balloonpanel_clickable_height = balloonpanel.getheight() / 2;
}