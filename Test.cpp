
#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ariel;
using namespace std;

// static vector<string> units = {"m"};
ifstream units_file{"units.txt"};


TEST_CASE("Adding operators check"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits x{4, "km"};
    NumberWithUnits y{35, "m"};
    // NumberWithUnits c{2, "sec"};
    CHECK_EQ(x+y , NumberWithUnits{4.035, "km"});
    CHECK_EQ(y+x , NumberWithUnits{4035, "m"});
    // CHECK_THROWS(x+c);
    // CHECK_THROWS(c+x);
}

TEST_CASE("+ and - = operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{7, "km"};
    NumberWithUnits y{2000, "m"};
    CHECK((x+=y) == NumberWithUnits{9, "km"});
    CHECK(x == NumberWithUnits{9, "km"});
    CHECK((y+=x) == NumberWithUnits{11000, "m"});
    CHECK(y == NumberWithUnits{11000, "m"});
    CHECK((x-=y) == NumberWithUnits{-2, "km"});
    CHECK(x == NumberWithUnits{-2, "km"});
    CHECK((y-=x) == NumberWithUnits{13000, "m"});
    CHECK(y == NumberWithUnits{13000, "m"});
}

TEST_CASE("increase/dacrease operators check"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{105, "cm"};
    CHECK(x++ == NumberWithUnits{105, "cm"});
    CHECK(x == NumberWithUnits{106, "cm"});
    CHECK(++x == NumberWithUnits{107, "cm"});
    CHECK(x == NumberWithUnits{107, "cm"});
    CHECK(x-- == NumberWithUnits{107, "cm"});
    CHECK(x == NumberWithUnits{106, "cm"});
    CHECK(--x == NumberWithUnits{105, "cm"});
    CHECK(x == NumberWithUnits{105, "cm"});
}

TEST_CASE("Multiplication operators: y*x, x*y, x*=y, y*=x"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{5, "km"};
    CHECK((x*0.5) == NumberWithUnits{2.5, "km"});
    CHECK((3*x) == NumberWithUnits{15, "km"});
    CHECK((x*=2.5) == NumberWithUnits{12.5, "km"});
    CHECK(x == NumberWithUnits{12.5, "km"});
}

TEST_CASE("Operators: >, >=, <, <=, ==, != "){
    NumberWithUnits::read_units(units_file);

    CHECK_LT(NumberWithUnits{3.5, "km"}  , NumberWithUnits{5000, "m"});
    CHECK_GT(NumberWithUnits{7000, "m"}, NumberWithUnits{6.7, "km"});
    CHECK_NE(NumberWithUnits{10, "km"}  , NumberWithUnits{9999, "m"});
    CHECK_NE(NumberWithUnits{9999, "m"}, NumberWithUnits{10, "km"});
    CHECK_LT(NumberWithUnits{199, "cm"} , NumberWithUnits{1000, "m"});
    CHECK_GT(NumberWithUnits{1000, "m"}, NumberWithUnits{199, "cm"});
    CHECK_NE(NumberWithUnits{770, "cm"} , NumberWithUnits{2040, "m"});
    CHECK_NE(NumberWithUnits{2021, "m"}, NumberWithUnits{21, "cm"});
    CHECK_EQ(NumberWithUnits{1500, "cm"}, NumberWithUnits{15, "m"});
    CHECK_EQ(NumberWithUnits{7.5, "m"}, NumberWithUnits{750, "cm"});

}
TEST_CASE("Throw exception check"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits n1{2, "km"};
    NumberWithUnits n2{2500, "sec"};
    CHECK_THROWS(  n1+n2);
}