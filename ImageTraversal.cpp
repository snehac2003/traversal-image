#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
 
  void bfs_add(std::deque<Point> & work_list, const Point & point) {

    // adds a Point for the bfs traversal to visit at some point in the future
      // work_list: the deque storing a list of points to be processed
      // point: the point to be added

    // push at back or front depending on bfs/dfs
      work_list.push_back(point);
  }

  
  void dfs_add(std::deque<Point> & work_list, const Point & point) {

    // adds a Point for the dfs traversal to visit at some point in the future
      // work_list: the deque storing a list of points to be processed
      // point: the point to be added

      work_list.push_back(point); // BACK
  }

  
  void bfs_pop(std::deque<Point> & work_list) {

    // removes the current Point in the bfs traversal
      // work_list: the deque storing a list of points to be processed
    
    work_list.pop_front();
  }

 
  void dfs_pop(std::deque<Point> & work_list) {

    // removes the current Point in the dfs traversal
      // work_list: the deque storing a list of points to be prcessed

      work_list.pop_back(); // BACK
  }

  Point bfs_peek(std::deque<Point> & work_list) {
    //return Point(0, 0);

    // returns the current Point in the bfs traversal
      // work_list: the deque storing a list of points to be processed
      // returns current Point

    return work_list.front();
  }


  Point dfs_peek(std::deque<Point> & work_list) {
    //return Point(0, 0);

    // returns the current Point in the dfs traversal
      // work_list: the deque storing a list of points to be processed
      // returns current Point

    return work_list.back();
  }

  
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) 
    : png_(png), start_(start), tolerance_(tolerance), fns_(fns) {  

    // constructor, initializes a ImageTraversal on given png image, starting at start, with given tolerance
      // png: the image this traversal is going to traverse
      // start: start point of traversal
      // tolerance: if current point is too different (difference > tolerance) with start point, not included in traversal
      // fns: set of functions describing a traversal's operation

  }

  ImageTraversal::Iterator::Iterator(PNG& png, Point& start, double tolerance, TraversalFunctions fns) /*:
    png_(png), start_(start), tolerance_(tolerance), fns_(fns)*/ {
    cur_ = start;
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    fns_ = fns;
    double w = png_.width();
    double h = png_.height();
    bool_vec_.resize(w);
    for (unsigned int i = 0; i < w; i++) {
      bool_vec_[i].resize(h);
      for (unsigned int j = 0; j < h; j++) {
        bool_vec_[i][j] = false;
      }
    }
    fns_.add(work_list_, start_);
  }

  
  ImageTraversal::Iterator ImageTraversal::begin() {
    //return ImageTraversal::Iterator(png_, start_, tolerance_, fns_);
    return ImageTraversal::Iterator(png_, start_, tolerance_, fns_);

    // returns an iterator for the traversal starting at the first point (specified by constructor)
  }

 
  ImageTraversal::Iterator ImageTraversal::end() {
    return ImageTraversal::Iterator();

    // returns an iterator for traversal one past end of traversal
  }

  
  ImageTraversal::Iterator::Iterator()/* : png_(nullptr), start_(0,0), tolerance(0.0), fns_({nullptr, nullptr, nullptr}) */{
    // initialize everything to 0 here
    
  }

 

  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

    bool_vec_[cur_.x][cur_.y] = true;

    //while (!work_list_.empty() && bool_vec_[work_list_.front().x][work_list_.front().y]) { // front
        //work_list_.pop_front(); // front
    //}
    while (!work_list_.empty() && bool_vec_[fns_.peek(work_list_).x][fns_.peek(work_list_).y]) {
      fns_.pop(work_list_);
    }

    std::vector<Point> neighbors = {
        Point(cur_.x + 1, cur_.y),
        Point(cur_.x, cur_.y + 1),
        Point(cur_.x - 1, cur_.y),
        Point(cur_.x, cur_.y - 1)
    };

    for (const Point &neighbor : neighbors) {
      if (neighbor.x >= 0 && neighbor.x < png_.width() && neighbor.y >= 0 && neighbor.y < png_.height()) {
        if (!bool_vec_[neighbor.x][neighbor.y]) {
          double Delta = calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(neighbor.x, neighbor.y));
          if (Delta <= tolerance_) {
            //work_list_.push_back(neighbor);
            fns_.add(work_list_, neighbor);
          }
        }
      }
    }

    if (!work_list_.empty()) {
        //cur_ = work_list_.front(); // front
        cur_ = fns_.peek(work_list_);
    }

    return *this;
  }

 
  Point ImageTraversal::Iterator::operator*() {
    //return Point(0, 0);
    //return work_list_.front();
    return fns_.peek(work_list_);
  }

  
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    //return false;
    return !(work_list_ == other.work_list_);
  }

 
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}
