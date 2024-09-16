#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h" //diff folder
#include "cs225/HSLAPixel.h" //diff folder
#include <vector>
#include <iostream>
using namespace std;
StickerSheet::StickerSheet(const Image& picture, unsigned max) //checked
{
    //base_pic = picture;
    base_pic = picture;
    max_stickers = max;
    for(unsigned i = 0; i < max_stickers; i++)
    {
        stickers_.pop_back();
        x_coord.pop_back();
        y_coord.pop_back();
    }
}

StickerSheet::StickerSheet(const StickerSheet &other)
{
    for(unsigned i = 0; i < max_stickers; i++)
    {
        stickers_.pop_back();
        x_coord.pop_back();
        y_coord.pop_back();
    }
    for(unsigned i = 0; i < other.stickers_.size(); i++)
    {
      stickers_.push_back(other.stickers_[i]);
      x_coord.push_back(other.x_coord[i]);
      y_coord.push_back(other.y_coord[i]);
    }
    base_pic = other.base_pic;
    max_stickers = other.max_stickers;
}

int StickerSheet::addSticker(Image &sticker, int x, int y)
{
        if(max_stickers > stickers_.size())
        {
            stickers_.push_back(&sticker);
            x_coord.push_back(x);
            y_coord.push_back(y);
            return (int)(stickers_.size() - 1);
        }
    max_stickers++;
    stickers_.push_back(&sticker);
    x_coord.push_back(x);
    y_coord.push_back(y);
    return (int)(stickers_.size() - 1);
}

void StickerSheet::changeMaxStickers(unsigned max)
{
  if (stickers_.size() != max_stickers) 
  {
    if (stickers_.size() > max_stickers) 
    {
        int del = stickers_.size() - max_stickers;
        for (int i = 0; i < del; i++) 
        {
            stickers_.pop_back();
            x_coord.pop_back();
            y_coord.pop_back();
        }
    }
    max_stickers = max;
  }
}

Image* StickerSheet::getSticker(unsigned index)
{
  if(index >= stickers_.size() || stickers_[index] == nullptr)
  {
    return nullptr;
  }
  return stickers_[index]; 
}

int StickerSheet::layers() const
{
  return max_stickers;
}

void StickerSheet::clear() 
{
  for (unsigned i = 0; i < stickers_.size(); i++) 
  {
    if(stickers_[i] != NULL)
    {
        delete stickers_[i];
    }
  }
  stickers_.clear();
  x_coord.clear();
  y_coord.clear();
  sticker_curr.clear();
  max_stickers = 0;
}


StickerSheet::~StickerSheet() 
{
  for(unsigned i = 0; i < stickers_.size(); i++)
  {
    stickers_.pop_back();
    x_coord.pop_back();
    y_coord.pop_back();
  }
  stickers_.clear();
  x_coord.clear();
  y_coord.clear();
  sticker_curr.clear();
  max_stickers = 0;
  //base_pic = nullptr;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
  if (this != &other)
  {
    clear();
    max_stickers = other.max_stickers;
    base_pic = other.base_pic;
    stickers_.resize(max_stickers);
    x_coord.resize(max_stickers);
    y_coord.resize(max_stickers);
    for (unsigned i = 0; i < max_stickers; i++)
    {
      stickers_[i] = other.stickers_[i] == nullptr ? nullptr : new Image(*other.stickers_[i]);
      x_coord[i] = other.x_coord[i];
      y_coord[i] = other.y_coord[i];
    }
  }
  return *this;
}

void StickerSheet::removeSticker(unsigned index)
{
  if(index < (stickers_.size()) && index >= 0)
  {
    stickers_.erase(stickers_.begin() + index);
    x_coord.erase(x_coord.begin() + index);
    y_coord.erase(y_coord.begin() + index);
  }
}

Image StickerSheet::render() const 
{
    unsigned width = base_pic.width();
    unsigned height = base_pic.height();
    for (unsigned i = 0; i < max_stickers; i++) 
    {
      if (stickers_[i] != nullptr) 
      {
        int x = x_coord[i];
        int y = y_coord[i];
        unsigned sticker_width = stickers_[i]->width();
        unsigned sticker_height = stickers_[i]->height();
        if (x + sticker_width > width) 
        {
          width = x + sticker_width;
        

        }
        if (y + sticker_height > height) 
        {
          height = y + sticker_height;
        }
      }
    }
    Image rendered;
    rendered.resize(width, height);
    for (unsigned int x = 0; x < base_pic.width(); ++x) 
    {
      for (unsigned int y = 0; y < base_pic.height(); ++y) 
      {
        HSLAPixel & pixel = rendered.getPixel(x, y);
        pixel = base_pic.getPixel(x, y);
      }
    }
    for (unsigned i = 0; i < max_stickers; i++) 
    {
      if (stickers_[i] != nullptr)
      {
        for (unsigned int x = 0; x < stickers_[i]->width(); ++x)
        {
          for (unsigned int y = 0; y < stickers_[i]->height(); ++y)
          {
            if (stickers_[i]->getPixel(x, y).a != 0)
            {
              cs225::HSLAPixel &pixel = rendered.getPixel(x + x_coord[i], y + y_coord[i]);
              pixel = stickers_[i]->getPixel(x, y);
            }
          }
        }
      }
    }
    return rendered;
}


int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y)
{
  if(layer >= stickers_.size())
  {
    return -1;
  }
  stickers_[layer] = new Image(sticker);
  x_coord[layer] = x;
  y_coord[layer] = y;
  return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y)
{
  if (index >= stickers_.size() || stickers_[index] == nullptr)
  {
    return false;
  }
  x_coord[index] = x;
  y_coord[index] = y;
  return true;
}