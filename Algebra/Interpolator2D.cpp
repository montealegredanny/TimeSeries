#include "Interpolator2D.h"

namespace SearchUtil
{
    long binarySearch(const double val, const std::vector<double>& nums, long start, long end)
    {
        // if the vector is small just do a simple linear search 
        if ((end - start) < 5L)
        {
            long currIdx = start; 
            while (currIdx < end)
            {
                if ((nums[currIdx] < val) && (val <= nums[currIdx + 1L]))
                {
                    return currIdx;
                }
                currIdx += 1L;
            }
            return -1; // in case we cannot find the number
        }
        
        long midIdx = (long)((end - start) / 2) + start; 
        if (nums[midIdx] >= val)
        {
            return SearchUtil::binarySearch(val, nums, start, midIdx);
        }
        else
        {
            return SearchUtil::binarySearch(val, nums, midIdx, end);
        }
    }
}

typedef std::pair<double, double> point;
double Interpolator2D::operator()(double x, double y) const
{
    // first we find the neighbors to apply the interpolation to 
    long xIdx = Interpolator2D::findNeighbors(x, m_xVec);
    long yIdx = Interpolator2D::findNeighbors(y, m_yVec);

    double xDown = m_xVec[xIdx];
    double xUp = m_xVec[xIdx + 1L];
    double yDown = m_yVec[yIdx];
    double yUp = m_yVec[yIdx + 1L];

    double f_UL = m_grid.at(point(xDown, yUp));
    double f_UR = m_grid.at(point(xUp, yUp));
    double f_DL = m_grid.at(point(xDown, yDown));
    double f_DR = m_grid.at(point(xUp, yDown));

    Matrix Q{ {{f_DL, f_UL}, {f_DR, f_UR}} };
    Matrix rVec{ {yUp - y, y - yDown} };
    Matrix lVec{ {xUp - x, x - xDown} }; 
    auto result = lVec.transpose() *( Q * rVec); 
    return result.get(0,0) / ( (xUp - xDown) * ( yUp - yDown));
}

long Interpolator2D::findNeighbors(double val, const std::vector<double>& arr) const
{
    assert(val > arr[0]  && "Value cannot be interpolated");
    assert(val <= arr.back() && "Value cannot be interpolated");
    return SearchUtil::binarySearch(val, arr, 0, arr.size() - 1); 
}
