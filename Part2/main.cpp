//
//  main.cpp
//  Part2
//
//  Created by Nazarii Synhaivskyi on 17.12.2022.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    string str;
    getline(cin, str);
    
    unsigned long first_index = str.find(":");
    cout << first_index << endl;
    
    unsigned long second_index = str.find(":", first_index+1);
    cout << second_index << endl;
    
    cout << "Before first   : " << str.substr(0, first_index) << endl;
    cout << "After first    : " << str.substr(first_index+1, str.length()-first_index) << endl;
    cout << "Between 1 and 2: " << str.substr(first_index+1, str.length()-second_index-1) << endl;
    
    return 0;
}
