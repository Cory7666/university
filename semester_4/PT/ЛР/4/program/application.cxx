#include "application.hxx"

using namespace lab5;

Application::Application (std::vector<Company> data)
    : data_ (data)
{ }

int Application::exec()
{
    sortData();
    avg_profit_  = getAvgProfit  (data_);
    avg_penalty_ = getAvgPenalty (data_);
    
    profit_t length = getIntervalLength (data_[data_.size() - 1].profit, data_[0].profit, INTERVAL_COUNT);
    for (int i = 0; i < INTERVAL_COUNT; i++)
    {
        int interval_start = data_[0].profit + i * length;
        Interval interval;
        interval.start = interval_start;
        interval.delta = length;
        interval.interval_data = selectCompaniesInProfitRange (interval_start, length);
        interval.avg_penalty = getAvgPenalty (interval.interval_data);
        interval.avg_profit  = getAvgProfit (interval.interval_data);
        interval.freq = interval.interval_data.size();
        intervals_.push_back (interval);
    }

    CoV_ = getCoV (intervals_, avg_profit_, avg_penalty_, data_.size());
    disperse_profit_ = getDisperseProfit (intervals_, avg_profit_, data_.size());
    a1_ = CoV_ / disperse_profit_;
    a0_ = avg_penalty_ - a1_ * avg_profit_;

    disperse_penalty_= getDispersePenalty (intervals_, avg_penalty_, data_.size());
    correlation_ = getCorrelation (CoV_, std::sqrt(disperse_profit_), std::sqrt(disperse_penalty_));

    X_low_  = calculateCLProfitLow   (T_P_VALUE, avg_profit_,  sqrt(disperse_profit_),  data_.size(), 1000);
    X_high_ = calculateCLProfitHigh  (T_P_VALUE, avg_profit_,  sqrt(disperse_profit_),  data_.size(), 1000);
    Y_low_  = calculateCLPenaltyLow  (T_P_VALUE, avg_penalty_, sqrt(disperse_penalty_), data_.size(), 1000);
    Y_high_ = calculateCLPenaltyHigh (T_P_VALUE, avg_penalty_, sqrt(disperse_penalty_), data_.size(), 1000);
    pigu_penalty_low_  = processPercentagePiguPenalty (X_low_, Y_low_);
    pigu_penalty_high_ = processPercentagePiguPenalty (X_high_, Y_high_);

    printResults();

    return 0;
}

vector<Company> Application::selectCompaniesInProfitRange (profit_t start, profit_t delta)
{
    vector<Company> ret;
    for (auto company : data_)
    {
        if (( start <= company.profit ) && ( company.profit < (start + delta) ))
        ret.push_back (company);
    }

    if (start + delta == data_[data_.size() - 1].profit)
        ret.push_back (data_[data_.size() - 1]);

    return ret;
}

value_t Application::getAvgProfit (const vector<Company>& data)
{
    value_t sum = 0;
    for (auto company : data)
        sum += company.profit;

    return sum / data.size();
}

value_t Application::getAvgPenalty (const vector<Company>& data)
{
    value_t sum = 0;
    for (auto company : data)
        sum += company.penalty;

    return sum / data.size();
}

value_t Application::getCoV(const vector<Interval>& data, value_t avg_profit, value_t avg_penalty, ivalue_t elements_count)
{
    value_t sum = 0.0;

    for (auto k : data)
    {
        sum += (k.avg_penalty - avg_penalty) * (k.avg_profit - avg_profit) * k.freq;
    }

    return sum / elements_count;
}

value_t Application::getDisperseProfit(const vector<Interval>& data, value_t avg_profit, ivalue_t elements_count)
{
    value_t sum = 0.0;

    for (auto k : data)
    {
        sum += std::pow (k.avg_profit - avg_profit, 2) * k.freq;
    }

    return sum / elements_count;
}

value_t Application::getDispersePenalty(const vector<Interval>& data, value_t avg_penalty, ivalue_t elements_count)
{
    value_t sum = 0.0;

    for (auto k : data)
    {
        sum += std::pow ( (k.avg_penalty - avg_penalty), 2 ) * k.freq;
    }

    return sum / elements_count;
}

value_t Application::getCorrelation (value_t CoV, value_t asd1, value_t asd2)
{
    return CoV / (asd1 * asd2);
}

void Application::printResults()
{
    cout << "Характеристики интервалов:" << endl;
    cout << "Интервал | Частота | Ср. оборот | Ср. штраф | Штраф, %" << endl;
    for (auto interval : intervals_)
    {
        cout << interval.start << "..." << (interval.start + interval.delta) << "\t\t"
             << interval.freq << "\t"
             << interval.avg_profit << "\t"
             << interval.avg_penalty << "\t"
             << processPercentagePiguPenalty (interval.avg_profit, interval.avg_penalty) * 100 << "%" << endl;
    }

    cout << endl
         << "Средние значения:" << endl
         << " *  Экономического оборота: " << avg_profit_ << endl
         << " *  Штрафа Пигу: " << avg_penalty_ << endl
         << " *  Штрафа Пигу, %: " << processPercentagePiguPenalty (avg_profit_, avg_penalty_) * 100 << endl;
    
    cout << endl
         << "Дисперсия по profit: " << disperse_profit_ << endl
         << "  СКО: " << sqrt(disperse_profit_) << endl
         << "Дисперсия по штрафу: " << disperse_penalty_ << endl
         << "  СКО: " << sqrt (disperse_penalty_) << endl;
    
    cout << endl
         << "Ковариация: " << CoV_ << endl
         << "Корреляция: " << correlation_ << endl;


    cout << endl
         << "Пределы изменения экономического оборота: " << X_low_ << " <= X <= " << X_high_ << endl;
    cout << "Пределы изменения размера штрама Пигу: " << Y_low_ << " <= Y <= " << Y_high_ << endl;
    cout << "Пределы изменения \"процентного\" штрафа Пигу, %: " << pigu_penalty_low_ * 100 << " <= ШП <= " << pigu_penalty_high_ * 100 << endl;
}
