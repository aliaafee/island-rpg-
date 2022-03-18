#ifndef __VALUEGRID_H__
#define __VALUEGRID_H__

#include <vector>

template <typename CellType>
class ValueGrid
{
public:
    ValueGrid(const int &cols, const int &rows) : cols_(cols), rows_(rows)
    {
        grid_.resize(cols_ * rows_);
    }

    int index(const int &i, const int &j) const
    {
        return i + cols_ * j;
    }

    int validIndex(const int &i, const int &j) const
    {
        if (i < 0)
            return false;
        if (i > cols_ - 1)
            return false;
        if (j < 0)
            return false;
        if (j > rows_ - 1)
            return false;
        return true;
    }

    void clear(const CellType &value)
    {
        std::fill(grid_.begin(), grid_.end(), 1);
    }

    void set(const int &i, const int &j, const CellType &value)
    {
        if (!validIndex(i, j))
            return;

        int ind = index(i, j);

        grid_[index(i, j)] = value;
    }

    void fill(const int &start_i, const int &start_j,
              const int &end_i, const int &end_j,
              const CellType &value)
    {
        for (int i = start_i; i < end_i; i++)
        {
            for (int j = start_j; j < end_j; j++)
            {
                set(i, j, value);
            }
        }
    }

    const CellType &value(const int &i, const int &j) const
    {
        return grid_[index(i, j)];
    }

    const int &rows() const { return rows_; }
    const int &cols() const { return cols_; }

private:
    int cols_, rows_;
    std::vector<CellType> grid_;
};

inline std::ostream &operator<<(std::ostream &os, const ValueGrid<int> &v)
{
    for (int j = 0; j < v.rows(); j++)
    {
        std::cout << " ";
        for (int i = 0; i < v.cols(); i++)
        {
            switch (v.value(i, j))
            {
            case 1:
                std::cout << ".";
                break;
            case 0:
                std::cout << "#";
                break;
            case 90:
                std::cout << "S";
                break;
            case 99:
                std::cout << "E";
                break;
            case 80:
                std::cout << "X";
                break;
            default:
                std::cout << "?";
                break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    return os;
}

#endif // __VALUEGRID_H__