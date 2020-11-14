//
// Created by ti on 2020/11/12.
//

#include "put_image.h"

void Game::put_image(int dstX,
                     int dstY,
                     IMAGE *pSrcImg,
                     UINT transparentcolor) {
    IMAGE *pDstImg = &this->game_window_canvas;
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);
    int w = pSrcImg->getwidth();
    int h = pSrcImg->getheight();

    TransparentBlt(dstDC, dstX, dstY, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void Game::put_image(IMAGE *pDstImg,
                     int dstX,
                     int dstY,
                     IMAGE *pSrcImg,
                     UINT transparentcolor) {
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);
    int w = pSrcImg->getwidth();
    int h = pSrcImg->getheight();

    TransparentBlt(dstDC, dstX, dstY, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void Game::put_image(int dstX,
                     int dstY,
                     int dstWidth,
                     int dstHeight,
                     IMAGE *pSrcImg,
                     int srcX,
                     int srcY,
                     int srcWidth,
                     int srcHeight,
                     UINT transparentcolor) {
    IMAGE *pDstImg = &this->game_window_canvas;
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);

    TransparentBlt(dstDC, dstX, dstY, dstWidth, dstHeight, srcDC, srcX, srcY, srcWidth, srcHeight, transparentcolor);
}

void Game::put_image(IMAGE *pDstImg,
                    int dstX,
                    int dstY,
                    int dstWidth,
                    int dstHeight,
                    IMAGE *pSrcImg,
                    int srcX,
                    int srcY,
                    int srcWidth,
                    int srcHeight,
                    UINT transparentcolor) {
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);

    TransparentBlt(dstDC, dstX, dstY, dstWidth, dstHeight, srcDC, srcX, srcY, srcWidth, srcHeight, transparentcolor);
}

void Game::put_image(int dstX,
                     int dstY,
                     IMAGE *pSrcImg) {
    IMAGE *pDstImg = &this->game_window_canvas;
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);
    int w = pSrcImg->getwidth();
    int h = pSrcImg->getheight();

    StretchBlt(dstDC, dstX, dstY, w, h, srcDC, 0, 0, w, h, SRCCOPY);
}

void Game::put_image(IMAGE *pDstImg,
                     int dstX,
                     int dstY,
                     IMAGE *pSrcImg) {
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);
    int w = pSrcImg->getwidth();
    int h = pSrcImg->getheight();

    StretchBlt(dstDC, dstX, dstY, w, h, srcDC, 0, 0, w, h, SRCCOPY);
}

void Game::put_image(int dstX,
                     int dstY,
                     int dstWidth,
                     int dstHeight,
                     IMAGE *pSrcImg,
                     int srcX,
                     int srcY,
                     int srcWidth,
                     int srcHeight) {
    IMAGE *pDstImg = &this->game_window_canvas;
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);

    StretchBlt(dstDC, dstX, dstY, dstWidth, dstHeight, srcDC, srcX, srcY, srcWidth, srcHeight, SRCCOPY);
}

void Game::put_image(IMAGE *pDstImg,
                     int dstX,
                     int dstY,
                     int dstWidth,
                     int dstHeight,
                     IMAGE *pSrcImg,
                     int srcX,
                     int srcY,
                     int srcWidth,
                     int srcHeight) {
    HDC dstDC = GetImageHDC(pDstImg);
    HDC srcDC = GetImageHDC(pSrcImg);
    int w = pSrcImg->getwidth();
    int h = pSrcImg->getheight();

    StretchBlt(dstDC, dstX, dstY, dstWidth, dstHeight, srcDC, srcX, srcY, srcWidth, srcHeight, SRCCOPY);
}

