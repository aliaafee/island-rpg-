#ifndef __SPIRALOUT_H__
#define __SPIRALOUT_H__

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
#endif // __SPIRALOUT_H__