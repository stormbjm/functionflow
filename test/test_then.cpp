/***********************************************
The MIT License (MIT)

Copyright (c) 2012 Athrun Arthur <athrunarthur@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*************************************************/
#include "ff.h"
#include <string>
#include <iostream>
using namespace ff;
using namespace std;

//This is used to test "then function", just make sure this can be compiled!

int main(int argc, char *argv[])
{
    ff::para<void> v1, v2;
    ff::para<int> i1, i2;
    ff::para<double> d1, d2;
    ff::para<std::string> s1, s2;
    v1([]() {
        std::cout<<"v1"<<std::endl;
    });
    v2([]() {
        std::cout<<"v2"<<std::endl;
    });

    i1([]()->int {return 1;});
    i2([]()->int {return 2;});

    d1([]()->double {return 1.0;});
    d2([]()->double {return 2.0;});

    s1([]()->std::string {return "s1";});
    s2([]()->std::string {return "s2";});

    (i1 && d1).then([](int i, double d) {
        std::cout<<i<<d<<std::endl;
    });
    (i1 || d1).then([](int index, std::tuple<int, double> res) {
        if(index == 0)
            std::cout<<std::get<0>(res)<<std::endl;
        else if(index == 1)
            std::cout<<std::get<1>(res)<<std::endl;
    });

    (v1 && i1).then([](double d) {
        std::cout<<d<<std::endl;
    });
    (v2 || i2).then([](bool b, double d) {
        std::cout<<d<<std::endl;
    });

	(i1 || d1 || s1).then([](int index, std::tuple<std::tuple<int, std::tuple<int, double> >, std::string> res){});
	(i1 || (d1 || s1)).then([](int index, std::tuple<int, std::tuple<int, std::tuple<double, std::string> > > res){});
	(v1 || d1 || s1).then([](int index, std::tuple<std::tuple<bool,double> , std::string> res){});
	
	(v1 && d1 || s1).then([](int index, std::tuple<double, std::string> res){});
	(i1 && d1 || s1).then([](int index, std::tuple<std::tuple<int, double>, std::string >res){});
	
	(v1 && d1 && s1).then([](double r1, std::string r2){});
	(i1 && d1 && s1).then([](std::tuple<int, double> r1, std::string r2){});
	(i1 && v1 && s1).then([](int r1, std::string r2){});
	
    ((i1 && d1) || (d2 && s2)).then([](int index, std::tuple<std::tuple<int, double>, std::tuple<double, std::string> > res) {});
    ((i1 && d1) && (d2 && s2)).then([](std::tuple<int, double> r1, std::tuple<double, std::string> r2) {});
    ((i1 || d1) && (d2 || s2)).then([](std::tuple<int, std::tuple<int, double> > r1, std::tuple<int, std::tuple<double, std::string> > r2) {});
	;

    return 0;
}