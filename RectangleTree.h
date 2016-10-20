#ifndef __RECTANGLE_TREE_H
#define __RECTANGLE_TREE_H

#include "IntervalTree.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

template <class T, typename K = std::size_t>
class Rectangle {
public:
    typedef Rectangle<T,K>* P;
    typedef Interval<P,K> IntervalP;

    IntervalP x, y;
    T value;

    Rectangle(K x_start, K x_stop, K y_start, K y_stop, const T& v)
        : x(x_start, x_stop, this), y(y_start, y_stop, this), value(v)
    { }
};

template <class T, typename K>
std::ostream& operator<<(std::ostream& out, const Rectangle<T,K>& r) {
    out << "Rectangle(" << r.x.start << ", " << r.x.stop << ", " << r.y.start << ", " << r.y.stop << "): " << r.value;
    return out;
}

template <class T, typename K = std::size_t>
class RectangleTree {
public:
    typedef IntervalTree<Rectangle<T,K>*,K> intervalTree;
    typedef std::vector<Interval<Rectangle<T,K>*,K> > intervalVector;
    typedef std::vector<Rectangle<T,K> > rectangleVector;

    static intervalVector extractXIntervals(const rectangleVector& rectangles) {
        intervalVector intervals;
        for(typename rectangleVector::const_iterator i = rectangles.begin(); i != rectangles.end(); ++i)
            intervals.push_back(Interval<Rectangle<T,K>*,K>(i->x.start, i->x.stop, i->x.value));
        return intervals;
    }

    static intervalVector extractYIntervals(const rectangleVector& rectangles) {
        intervalVector intervals;
        for(typename rectangleVector::const_iterator i = rectangles.begin(); i != rectangles.end(); ++i)
            intervals.push_back(Interval<Rectangle<T,K>*,K>(i->y.start, i->y.stop, i->y.value));
        return intervals;
    }

    intervalVector xi, yi;
    intervalTree itx, ity;

    RectangleTree(const rectangleVector& rectangles)
        : xi(extractXIntervals(rectangles)),
            yi(extractYIntervals(rectangles)),
            itx(xi), ity(yi)
    { }

    static std::vector<Rectangle<T,K>*> getSortedRectangleVector(const intervalVector& v) {
        std::vector<Rectangle<T,K>*> r;
        for(typename intervalVector::const_iterator i = v.begin(); i != v.end(); ++i) {
            r.push_back(i->value);
        }
        sort(r.begin(), r.end());
        return r;
    }

    rectangleVector findOverlapping(K x_start, K x_stop, K y_start, K y_stop) const {
        rectangleVector rv;
        findOverlapping(x_start, x_stop, y_start, y_stop, rv);
        return rv;
    }

    void findOverlapping(K x_start, K x_stop, K y_start, K y_stop, rectangleVector& overlapping) const {
        std::vector<Rectangle<T,K>*> rx = getSortedRectangleVector(itx.findOverlapping(x_start, x_stop));
        std::vector<Rectangle<T,K>*> ry = getSortedRectangleVector(ity.findOverlapping(y_start, y_stop));
        std::vector<Rectangle<T,K>*> r;
        set_intersection(rx.begin(), rx.end(), ry.begin(), ry.end(), back_inserter(r));
        for(typename std::vector<Rectangle<T,K>*>::const_iterator i = r.begin(); i != r.end(); ++i) {
            overlapping.push_back(**i);
        }
    }

    rectangleVector findContained(K x_start, K x_stop, K y_start, K y_stop) const {
        rectangleVector rv;
        findContained(x_start, x_stop, y_start, y_stop, rv);
        return rv;
    }

    void findContained(K x_start, K x_stop, K y_start, K y_stop, rectangleVector& overlapping) const {
        std::vector<Rectangle<T,K>*> rx = getSortedRectangleVector(itx.findContained(x_start, x_stop));
        std::vector<Rectangle<T,K>*> ry = getSortedRectangleVector(ity.findContained(y_start, y_stop));
        std::vector<Rectangle<T,K>*> r;
        set_intersection(rx.begin(), rx.end(), ry.begin(), ry.end(), back_inserter(r));
        for(typename std::vector<Rectangle<T,K>*>::const_iterator i = r.begin(); i != r.end(); ++i) {
            overlapping.push_back(**i);
        }
    }
};

#endif // __RECTANGLE_TREE_H

