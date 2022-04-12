/*
A set of given positive integers is given.
Arrange these numbers in as few intervals as possible so that a and b can be in one interval [a, b] if a, b, and all natural numbers between a and b are also in this interval.

Example:
The numbers are 4, 3, 8, 4, 5, 1, 9
The intervals are [1], [3, 5], [8, 9]

Write a C ++ program that reads integers from the keyboard, and
• If the integer is greater than 0, puts it in the set of previously scanned numbers and prints the intervals.
• If the integer is less than 0, take its absolute value. If this was in the set of previously scanned numbers, take it out of there. Prints the intervals.
• If the scanned number is 0, the program exits.
*/

#include "stdlib.h"
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

//data for random test
// std::vector<unsigned int> data = {4, 3, 8, 4, 5, 1, 9, 11, 10, 14, 12, 15, 13, 12};
const int spread  = 200; // spreading of input values
const int min = 200; //minimum numer of input values


//add new [num, num] interval
void addNewInterval(int num, std::multimap<int, int> & intervals){
    intervals.insert(std::make_pair(num, 0));
    intervals.insert(std::make_pair(num, 1));
}

//concetanate of the [x0, it0->first] and the [it1->first, x1] intervals. The result is the [x0, x1] interval
void concatenationIntervals(std::multimap<int, int>::iterator it0, std::multimap<int, int>::iterator it1, std::multimap<int, int> & intervals){
    intervals.erase(it0);
    intervals.erase(it1);
}

//modification of an interval
//if border == 0: modification of the left side of the interval
//if border == 1: modification of the right side of the interval
void modInterval(std::multimap<int, int>::iterator it0, int num, int border, std::multimap<int, int> & intervals){
    intervals.insert(std::make_pair(num, border));
    intervals.erase(it0);
}

//creation of a new interval with value num
void addNewElement(int num, std::multimap<int, int> & intervals){
    if (intervals.size() == 0){
        addNewInterval(num, intervals);
        return;
    }
    auto it = intervals.find(num);
    if (it == intervals.end()){

        std::multimap<int, int>::iterator  it0 = intervals.lower_bound(num);
        std::multimap<int, int>::iterator it1 = intervals.lower_bound(num);

        if (it0 == intervals.begin()){
            if (it0->first - num == 1){
               modInterval(it0, num, 0, intervals);
            }
            else {
               addNewInterval(num, intervals);
            }
        }
        else if (it0 == intervals.end()){
            it0--;
            if (num - it0->first == 1){
                modInterval(it0, num, 1, intervals);
            }
            else {
                addNewInterval(num, intervals);
            }
        }
        else {
            if (it0->second == 0){
               it0--;
               if ((num - it0->first == 1)||(it1->first - num == 1)){
                   if ((num - it0->first == 1)&&(it1->first - num == 1)){
                      concatenationIntervals(it0, it1, intervals);
                   }
                   else if (num - it0->first == 1){
                       modInterval(it0, num, 1, intervals);
                   }
                   else {
                       modInterval(it1, num, 0, intervals);
                   }
               }
               else {
                   addNewInterval(num, intervals);
               }
            }
        }
    }
}

void printResult(std::multimap<int, int> & intervals){
    std::multimap<int, int>::iterator  it = intervals.begin();
    while (it != intervals.end()){
        std::cout << "["<< it->first << ", ";
        it++;
        if (it != intervals.end()) std::cout << it->first << "]" << std::endl;
        it++;
    }
}

//test functions

//result checking
//1. the values are 0,1 .... 0,1. It means the left side and right side of the interval
//2. the distance of the values of the interval sides greater then 1
void check(std::multimap<int, int> & intervals){
    std::multimap<int, int>::iterator  it = intervals.begin();
    int prev = 1, prevKey = -1;
    while (it != intervals.end()){
        if (prev == it->second){
           std::cout << "error0 "<< it->first << std::endl;
        }
        if (it->second == 1){
           prevKey = it->first;
        }
        if ((prevKey >= 0)&&(it->second == 0)&&(it->first - prevKey < 2)){
            std::cout << "error1 "<< it->first << " " << prevKey << std::endl;
        }
        prev = it->second;
        it++;
    };

}

//randomized test

void test(std::multimap<int, int> & intervals){
    srand((unsigned)time(0));
    int num = -1, i = 0;
    std::vector<unsigned int> data;
    while (num != 0){
        if (i < min) num = (rand()%spread) + 1;
        else num = (rand()%spread);
        i++;
        if (num != 0) {
            data.push_back(num);
            addNewElement(num, intervals);
        }
    }
    check(intervals);
    printResult(intervals);
}

int main(){
    //result multimap
    std::multimap<int, int> intervals;

    //randomized test
    //test(intervals);


    int num = -1;
    intervals.clear();
    while (num != 0) {
      std::cin >> num;
      if (num != 0) addNewElement(num, intervals);
    }
    printResult(intervals);
    return 0;
}
