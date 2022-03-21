#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <string_view>

class SpiralOut
{
public:
    SpiralOut(int start_i,
              int start_j,
              int max) : i_(start_i),
                         j_(start_j),
                         max_(max),
                         steps_(1),
                         t_(0), s_(0), count_(0),
                         d_i(1), d_j(0) {}

    bool next(int &out_i, int &out_j)
    {
        if (count_ > max_ - 1)
        {
            return false;
        }

        i_ += d_i;
        j_ += d_j;

        out_i = i_;
        out_j = j_;

        count_ += 1;

        s_++;
        if (s_ > steps_ - 1)
        {
            std::swap(d_i, d_j);
            d_j *= -1;
            t_++;
            if (t_ > 1)
            {
                steps_++;
                t_ = 0;
            }

            s_ = 0;
        }

        return true;
    }

private:
    int i_, j_, max_, steps_, t_, s_, count_, d_i, d_j;
};

class DiagonalIterateGrid
{
public:
    DiagonalIterateGrid(int side) : side_(side), d1_(0), i_(0), j_(0), d2_(1), j2_(1) { ; }

    bool next(int &out_i, int &out_j)
    {
        if (d1_ < side_)
        {
            out_i = d1_ - j_;
            out_j = j_;

            if (j_ < d1_)
            {
                j_++;
            }
            else
            {
                j_ = 0;
                d1_++;
            }
            return true;
        }

        if (d2_ < side_)
        {
            out_i = side_ + d2_ - j2_ - 1;
            out_j = j2_;

            if (j2_ < side_ - 1)
            {
                j2_++;
            }
            else
            {
                d2_++;
                j2_ = d2_;
            }
            return true;
        }
        return false;
    }

private:
    int side_;
    int d1_;
    int d2_;
    int i_, j_;
    int j2_;
};

#endif // __ALGORITHM_H__