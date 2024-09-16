#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

<<<<<<< HEAD
  Image base_pic;
  base_pic.readFromFile("myImage.png");
  StickerSheet sheet(base_pic, 3);
  Image sticker1;
  sticker1.readFromFile("sticker1.png");
  sheet.addSticker(sticker1, 25, 25);
  Image sticker2;
  sticker2.readFromFile("sticker2.png");
  sheet.addSticker(sticker2, 50, 50);
  Image sticker3;
  sticker3.readFromFile("sticker3.png");
  sheet.addSticker(sticker3, 100, 100);
  
=======

>>>>>>> 01e1676ef79b133cf10cc2db35926cb3fc3dea4d
  return 0;
}
