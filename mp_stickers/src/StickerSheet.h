/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
<<<<<<< HEAD
#include "Image.h"
#include <vector>
using namespace std;
class StickerSheet : public Image
{
    public:
        StickerSheet(const Image &picture, unsigned max);
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, int x, int y);
        int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
        bool translate(unsigned index, int x, int y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        int layers() const;
        Image render() const;
        void clear();
        ~StickerSheet();
        void temp();
    private:
        Image base_pic;
        std::vector<Image*> stickers_;
        std::vector<int> x_coord;
        std::vector<int> y_coord;
        std::vector<bool> sticker_curr;
        unsigned max_stickers;
};
=======

>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
