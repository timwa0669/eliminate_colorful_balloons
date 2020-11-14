//
// Created by ti on 2020/10/8.
//

#include "main.h"

int main(int argc, const char **argv) {
    Game *game = new Game(argc, argv);
    delete game;
    return 0;
}
