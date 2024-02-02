#ifndef MEMBERHANDLER_H
#define MEMBERHANDLER_H

#include "consts.h"


class MemberHandler
{
private:

    int size=0; //the number of elements stored
    int capacity=5;

    struct Member
    {
        int membershipNumber;
        double totalAmountSpent;
    };

    Member* memberArr;

public:

    MemberHandler();
    ~MemberHandler();
    void addData(int membershipNumber, double totalAmountSpent);
    int getSize() const;
    bool isEmpty();
    bool isFull();
    void resize();
    void getData(int membershipNumber, double& totalAmountSpent, double& rebate);
    double round(double var);
};

#endif // MEMBERHANDLER_H
