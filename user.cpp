#include "user.h"

User::User()
{

}

int User::getEmpId() const {
    return empID;
}

void User::setEmpId(int empId) {
    empID = empId;
}

double User::getBasePay() const {
    return basePay;
}

void User::setBasePay(double basePay) {
    User::basePay = basePay;
}

double User::getAllowance() const {
    return allowance;
}

void User::setAllowance(double allowance) {
    User::allowance = allowance;
}

double User::getSubsidy() const {
    return subsidy;
}

void User::setSubsidy(double subsidy) {
    User::subsidy = subsidy;
}

double User::getPosteSub() const {
    return PosteSub;
}

void User::setPosteSub(double posteSub) {
    PosteSub = posteSub;
}

double User::getDeserve() const {
    return deserve;
}

void User::setDeserve(double deserve) {
    User::deserve = deserve;
}

double User::getTax() const {
    return tax;
}

void User::setTax(double tax) {
    User::tax = tax;
}

double User::getPunishment() const {
    return punishment;
}

void User::setPunishment(double punishment) {
    User::punishment = punishment;
}

double User::getRealGet() const {
    return realGet;
}

void User::setRealGet(double realGet) {
    User::realGet = realGet;
}

double User::countDeserve(){
   return basePay+allowance+subsidy+PosteSub;
}

double User::couTax(){
    if(basePay<1100) return 0;
    else if(basePay<1600) return (basePay-1100)*0.05;
    else if(basePay<2600) return (basePay-1600)*0.10+25;
    else if(basePay<3600) return (basePay-2600)*0.15+125;
    else if(basePay<5600) return  275;
    else return (basePay-5600)*0.20 +275;
}

double User::CountRealGet(){
    return deserve-punishment-tax;
}
