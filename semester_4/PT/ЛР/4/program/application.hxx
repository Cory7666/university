#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::sqrt;

#ifndef LAB5_APPLICATION_HXX
#define LAB5_APPLICATION_HXX

namespace lab5
{
using profit_t = long long;
using penalty_t = long long;
using ivalue_t = long long;
using value_t = long double;

const ivalue_t INTERVAL_COUNT = 5;
const value_t  T_P_VALUE = 2.0;

struct Company
{
    profit_t  profit;
    penalty_t penalty;

    bool operator< (const Company& other) const
    { return profit < other.profit; }
};

struct Interval
{
    ivalue_t start, delta;
    value_t  avg_profit;
    penalty_t avg_penalty;
    ivalue_t freq;
    vector<Company> interval_data;
};

class Application
{
public:
    Application (std::vector<Company> data);
    int exec();
private:

    vector<Company> selectCompaniesInProfitRange (profit_t start, profit_t end);
    value_t getAvgProfit  (const vector<Company>& data);
    value_t getAvgPenalty (const vector<Company>& data);
    value_t getCoV(const vector<Interval>& data, value_t avg_profit, value_t avg_penalty, ivalue_t elements_count);
    value_t getDispersePenalty(const vector<Interval>& data, value_t avg_penalty, ivalue_t elements_count);
    value_t getDisperseProfit(const vector<Interval>& data, value_t avg_profit, ivalue_t elements_count);
    value_t getCorrelation (value_t CoV, value_t asd1, value_t asd2);
    void printResults();

    value_t calculateCLProfitLow (value_t t_p, value_t avg_profit, value_t asd, ivalue_t n, ivalue_t N) const
    {
        return avg_profit - (t_p
            * (asd / sqrt(n))
            * sqrt ( (value_t) (N - n) / (N - 1) ));
    }

    inline value_t calculateCLProfitHigh (value_t t_p, value_t avg_profit, value_t asd, ivalue_t n, ivalue_t N) const
    {
        return avg_profit + t_p * asd / sqrt(n) * sqrt ( ((value_t) N - n) / (N - 1) );
    }

    inline value_t calculateCLPenaltyLow (value_t t_p, value_t avg_penalty, value_t asd, ivalue_t n, ivalue_t N) const
    {
        return avg_penalty - t_p
             * (asd / sqrt(n))
             * sqrt ( (value_t) (N - n) / (N - 1) );
    }

    inline value_t calculateCLPenaltyHigh (value_t t_p, value_t avg_penalty, value_t asd, ivalue_t n, ivalue_t N) const
    {
        return avg_penalty + t_p
             * (asd / sqrt(n))
             * sqrt ( (value_t) (N - n) / (N - 1) );
    }

    inline void sortData()
    { std::sort (data_.begin(), data_.end()); }

    constexpr profit_t getIntervalLength (profit_t x_max, profit_t x_min, profit_t m) const
    { return (x_max - x_min) / m; }

    inline value_t processPercentagePiguPenalty (value_t profit,
                                                 value_t penalty,
                                                 profit_t profit_mod = 1000
    ) const
    { return (penalty) / (profit * profit_mod); }

    inline value_t calculateModelElasticity (value_t a1, value_t avg_profit, value_t avg_penalty)
    { return a1 * avg_profit / avg_penalty; }

    vector<Company> data_;
    vector<Interval> intervals_;
    value_t avg_profit_;
    value_t avg_penalty_;
    value_t CoV_, correlation_;
    value_t disperse_profit_, disperse_penalty_;
    value_t a0_, a1_;
    value_t model_elasticity_;
    value_t X_low_, X_high_, Y_low_, Y_high_, pigu_penalty_low_, pigu_penalty_high_;
};

}

#endif // !LAB5_APPLICATION_HXX
