#ifndef USER_H
#define USER_H


class User
{
private:
    int empID;
    double basePay;
    double allowance;
    double subsidy;
    double PosteSub;
    double deserve;
    double tax;
    double punishment;
    double realGet;
public:
    User();

    int getEmpId() const;

    void setEmpId(int empId);

    double getBasePay() const;

    void setBasePay(double basePay);

    double getAllowance() const;

    void setAllowance(double allowance);

    double getSubsidy() const;

    void setSubsidy(double subsidy);

    double getPosteSub() const;

    void setPosteSub(double posteSub);

    double getDeserve() const;

    void setDeserve(double deserve);

    double getTax() const;

    void setTax(double tax);

    double getPunishment() const;

    void setPunishment(double punishment);

    double getRealGet() const;

    void setRealGet(double realGet);

    double countDeserve();

    double couTax();

    double CountRealGet();
};

#endif // USER_H
