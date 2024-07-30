#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;


FloodFilledImage::FloodFilledImage(const PNG & png) : png_(png) {

}


void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  traversal_vec_.push_back(&traversal);
  color_picker_vec_.push_back(&colorPicker);
}


Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  PNG temp_image = png_;
  unsigned int size_traversal = traversal_vec_.size();
  for (unsigned int i = 0; i < size_traversal; i++) {
    unsigned image_num = 0;
    for (auto it = traversal_vec_[i]->begin(); it != traversal_vec_[i]->end(); ++it) {
      if (image_num % frameInterval == 0) {
        animation.addFrame(temp_image);
      }
      HSLAPixel & current = temp_image.getPixel((*it).x, (*it).y);
      current = color_picker_vec_[i]->getColor((*it).x, (*it).y);
      

      image_num++;
    }
  }
  animation.addFrame(temp_image);
  return animation;
}
