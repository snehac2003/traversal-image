#pragma once

#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;

class FloodFilledImage {
public:
  FloodFilledImage(const PNG & png);
  void addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker);
  Animation animate(unsigned frameInterval) const;

private:
  PNG png_;
  vector<ColorPicker*> color_picker_vec_;
  vector<Traversals::ImageTraversal*> traversal_vec_;


};
