/**
* @file main.cpp
* @brief Converts local timezone to UTC to see how far behind people are
* @author Ryan LaVigne
* @assignment Lecture 10.1
* @date 11/2/2020
* @credit boost.org
*/

  #include "boost/date_time/posix_time/posix_time.hpp"
  #include "boost/date_time/local_time_adjustor.hpp"
  #include "boost/date_time/c_local_time_adjustor.hpp"
  #include <iostream>

  int main() 
  {
    using namespace std;
    using namespace boost::posix_time;
    using namespace boost::gregorian;

    typedef boost::date_time::c_local_adjustor<ptime> local_adj;
    ptime t10(date(2021,Jan,1), hours(7)); 
    ptime t11 = local_adj::utc_to_local(t10);
    cout << "UTC <--> Zone base on TZ setting" << endl;
    cout << to_simple_string(t11) << " in your TZ is " << to_simple_string(t10) << " UTC time " << endl;
    time_duration td = t11 - t10;
    cout << "A difference of: " << to_simple_string(td) << endl;

    //eastern timezone is utc-5
    typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;

    ptime t1(date(2020,Dec,31), hours(19)); //5 hours b/f midnight Vermont time

    cout << "\nUTC <--> Vermont while DST is NOT active (5 hours)" << endl;

    ptime t2 =  us_eastern::local_to_utc(t1);
    cout << to_simple_string(t1) << " in Vermont is " << to_simple_string(t2) << " UTC time "<< endl;

    ptime t3 = us_eastern::utc_to_local(t2);//back should be the same
    cout << to_simple_string(t2) << " UTC is " << to_simple_string(t3) << " Vermont time " << "\n\n";

    ptime t4(date(2021,May,31), hours(20)); //4 hours b/f midnight NY time
    cout << "UTC <--> Vermont while DST is active (4 hours)" << endl;
    ptime t5 = us_eastern::local_to_utc(t4);
    cout << to_simple_string(t4) << " in Vermont is " << to_simple_string(t5) << " UTC time " << endl;

    ptime t6 = us_eastern::utc_to_local(t5);
    cout << to_simple_string(t5) << " UTC is " << to_simple_string(t6) << " Vermont time " << "\n" << endl;

    //California timezone is utc-8 with no dst
    typedef boost::date_time::local_adjustor<ptime, -8, no_dst> us_california;

    ptime t7(date(2020,May,31), hours(16)); 
    cout << "UTC <--> California (8 hours)" << endl;
    ptime t8 = us_california::local_to_utc(t7);
    cout << to_simple_string(t7) << " in California is " << to_simple_string(t8) << " UTC time " << endl;

    //Norway Is utc+5 hours with no dst
    typedef boost::date_time::local_adjustor<ptime, +1, no_dst> norway;

    cout << endl;
    ptime tnor1(date(2020,Jun,1), hours(1));
    cout << "UTC <--> Norway (+1 hours)" << endl;
    ptime tnor2 = norway::local_to_utc(tnor1);
    cout << to_simple_string(tnor1) << " in Norway it is " << to_simple_string(tnor2) << " UTC time " << endl;

    //Compare time zones Norway vs California
    cout << endl;
    cout << "Norway <--> California (+9 hours)" << endl;
    cout << "Norway Time: " << to_simple_string(tnor1) << " VS California Time: " << to_simple_string(t7) << endl; 

    

    return 0;
  }