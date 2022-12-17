//
//  main.cpp
//  Part1
//
//  Created by Nazarii Synhaivskyi on 17.12.2022.
//
#include <iostream>
#include <ostream>
#include <istream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <regex>

using namespace std;


class Number {
protected:
    float number;
public:
    Number(): Number(0) {}
    Number(float number): number(number) {}
    Number(const Number& n): Number(n.get_number()) {}
    
    int64_t get_number() const {return number;}
    void set_number(const float& number) {this->number = number;}
    
    virtual void input(istream& inp = cin) {
        inp >> number;
    }
    
    virtual void print(ostream& out = cout) const {
        out << number;
    }
    
    virtual void add(const Number& other) {
        this->number = this->number + other.get_number();
    }
    
    virtual void multiply(const Number& other) {
        this->number = this->number * other.get_number();
    }
    
    Number operator+() const {return Number(*this);}
    Number operator-() const {return Number(-number);}
    
    friend ostream& operator<<(ostream& out, const Number& n) {
        n.print(out);
        return out;
    }
    
    friend istream& operator>>(istream& inp, Number& n) {
        n.input(inp);
        return inp;
    }
    Number operator+(const Number& other) const {
        Number result(*this);
        result.add(other);
        return result;
    }
    
    friend Number operator+(const Number& self, float other) {
        Number result(self);
        result.add(Number(other));
        return result;
    }
    
    Number operator-(const Number& other) const {
        Number result(*this);
        result.add(-other);
        return result;
    }
    
    Number operator*(const Number& other) const {
        Number result(*this);
        result.multiply(other);
        return result;
    }
    
    Number& operator+=(const Number& other) {add(other); return *this; }
    Number& operator*=(const Number& other) {multiply(other); return *this; }
    
    bool operator<(const Number& other) const {return number < other.number; }
    bool operator<(float x) const {return number < x; }
    bool operator>(const Number& other) const {return number > other.number; }
    bool operator>(float x) const {return number > x; }
    bool operator<=(const Number& other) const {return number <= other.number; }
    bool operator>=(const Number& other) const {return number >= other.number; }
    bool operator==(const Number& other) const {return number == other.number; }
    bool operator!=(const Number& other) const {return number != other.number; }
};

class ComplexNumber : Number {
    float imag_number;
    
    void init(string cn_str){
        std::smatch match;
        
        std::regex re_cn("(^(?=[iI.\\d+-])([+-]?(?:\\d+(?:\\.\\d*)?|\\.\\d+)(?:[eE][+-]?\\d+)?(?![iI.\\d]))?(([+-]?(?:(?:\\d+(?:\\.\\d*)?|\\.\\d+)(?:[eE][+-]?\\d+)?)?)[iI])?$)");
        
        if (regex_search(cn_str, match, re_cn)) {
            string real_part = match[2].str();
            string imag_part = match[4].str();  //can be only +, - or epmty, ex. i, 2+i, -i
            if (real_part == "") {
                number = 0;
            }
            else {
                number = stof(real_part);
            }
            if(imag_part == "") {
                if (real_part == "")
                    imag_number = 1;
                else
                    imag_number = 0;
            }
            else if (imag_part == "+") {
                imag_number = 1;
            } else if (imag_part == "-") {
                imag_number = -1;
            }
            else {
                imag_number = stof(imag_part);
            }
        }
        else {
            cout << "No match for input strign with complex number";
        }
    }
public:
    ComplexNumber(): Number(0) {}
    ComplexNumber(string cn_str) {
        init(cn_str);
    }
    ComplexNumber(float number): Number(number) {}
    ComplexNumber(const Number& n): Number(n) {}
    
    ComplexNumber(float number, float imag): Number(number), imag_number(imag) {}
    ComplexNumber(const ComplexNumber& cn): ComplexNumber(cn.number, cn.imag_number) {}
    
    int64_t get_imag() const {return imag_number;}
    void set_imag(const float& imag) {this->imag_number = imag;}
    
    void input(istream& inp = cin) {
        string cn_str;
        inp >> cn_str;
        init(cn_str);
    }
    void print(ostream& out = cout) const {
        string real_part = "";
        string imag_part = "";  //can be only +, - or epmty, ex. i, 2+i, -i
        if (number == 0) {
            out << "";
        }
        else {
            out << number;
        }
        
        if(imag_number == 0) {
            out << "";
        }
        else if (imag_number == 1) {
            if (number != 0)
                out << "+";
            out << "i";
        } else if (imag_number == -1) {
            out << "-i";
        }
        else {
            if (imag_number > 0 && number != 0)
                out << "+";
            out << imag_number << "i";
        }
    }
    
    friend ostream& operator<<(ostream& out, const ComplexNumber& cn) {
        cn.print(out);
        return out;
    }
    
    friend istream& operator>>(istream& inp, ComplexNumber& cn) {
        cn.input(inp);
        return inp;
    }
    
    
    void add(const ComplexNumber& other) {
        this->number = this->number + other.get_number();
        this->imag_number = this->imag_number + other.get_imag();
    }
    
    void multiply(const ComplexNumber& other) {
        this->number = this->number * other.get_number()-this->imag_number * other.get_imag();
        this->imag_number = this->imag_number * other.get_number()+this->number * other.get_imag();
    }
    
    ComplexNumber operator+() const {return ComplexNumber(*this);}
    ComplexNumber operator-() const {return ComplexNumber(-number, -imag_number);}
    
    friend ComplexNumber operator+(const ComplexNumber& self, float other) {
        ComplexNumber result(self);
        result.add(ComplexNumber(other));
        return result;
    }
    
    ComplexNumber operator+(const ComplexNumber& other) const {
        ComplexNumber result(*this);
        result.add(other);
        return result;
    }
    
    ComplexNumber operator-(ComplexNumber& other) const {
        ComplexNumber result(*this);
        result.add(-other);
        return result;
    }
    
    ComplexNumber operator*(const ComplexNumber& other) const {
        ComplexNumber result(*this);
        result.multiply(other);
        return result;
    }
    
    ComplexNumber& operator+=(const ComplexNumber& other) {add(other); return *this; }
    ComplexNumber& operator*=(const ComplexNumber& other) {multiply(other); return *this; }
    
    bool operator < (const ComplexNumber& other) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) < sqrt(pow(other.number,2)+ pow(other.imag_number,2));
    }
    bool operator < (float x) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) < sqrt(pow(x,2));
    }
    bool operator>(const ComplexNumber& other) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) > sqrt(pow(other.number,2)+ pow(other.imag_number,2));
    }
    bool operator>(float x) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) > sqrt(pow(x,2));
    }
    bool operator<=(const ComplexNumber& other) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) <= sqrt(pow(other.number,2)+ pow(other.imag_number,2));
    }
    bool operator>=(const ComplexNumber& other) const {
        return sqrt(pow(number,2)+ pow(imag_number,2)) >= sqrt(pow(other.number,2)+ pow(other.imag_number,2));
    }
    bool operator==(const ComplexNumber& other) const {
        return number != other.number && imag_number != other.imag_number;
    }
    bool operator!=(const ComplexNumber& other) const {
        return number != other.number || imag_number != other.imag_number;
    }
};

int main() {
    ComplexNumber cn1;
    ComplexNumber cn2;
    
    cout << "Input Number1: ";
    cin >> cn1;
    
    cout << "Input Number2: ";
    cin >> cn2;
    
    cout << "cn1 + cn2   = " << cn1 + cn1 << endl;
    cout << "cn1 - cn2   = " << cn1 - cn2 << endl;
    cout << "cn1 * cn2   = " << cn1 * cn2 << endl;
    cout << "cn1 >= cn2  = " << (cn1>=cn2) << endl;
    cout << "cn1 <= cn2  = " << (cn1<=cn2) << endl;
    
    cout << endl;
    
    
    return 0;
}
