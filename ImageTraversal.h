#pragma once

#include <iterator>
#include <deque>
#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

using namespace cs225;


namespace Traversals {
  
  typedef void (*add_function) (std::deque<Point> &, const Point &);
  
  
  typedef void (*pop_function) (std::deque<Point> &);

  typedef Point (*peek_function) (std::deque<Point> &);

 
  typedef struct TraversalFunctions {
    add_function add;
    pop_function pop;
    peek_function peek;
  } TraversalFunctions;

  void bfs_add(std::deque<Point> & work_list, const Point & point);
  void dfs_add(std::deque<Point> & work_list, const Point & point);

  void bfs_pop(std::deque<Point> & work_list);
  void dfs_pop(std::deque<Point> & work_list);

  Point bfs_peek(std::deque<Point> & work_list);
  Point dfs_peek(std::deque<Point> & work_list);

  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);

 
  class ImageTraversal {
  public:
    
    class Iterator : std::iterator<std::forward_iterator_tag, Point> {
    public:
      Iterator();
      Iterator(PNG& png, Point& start, double tolerance, TraversalFunctions fns);

      Iterator & operator++();
      Point operator*();
      bool operator!=(const Iterator &other);

      size_t size() const;
      bool empty() const;

     
    private:
      
      std::deque<Point> work_list_;
      PNG png_;
      Point start_;
      Point cur_;
      double tolerance_;
      TraversalFunctions fns_;
      std::vector<std::vector<bool>> bool_vec_;
    };

   
    ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns);

    Iterator begin();

   
    Iterator end();

  private:
    PNG png_;
    Point start_;
    Point cur_;
    double tolerance_;
    TraversalFunctions fns_;
    std::vector<std::vector<bool>> bool_vec_;

  };
}
