#include "memberhandler.h"


MemberHandler::MemberHandler()
{
    int size = 0; //the number of elements stored
    int capacity = 5;
    memberArr = new Member[capacity];
}

MemberHandler::~MemberHandler()
{
    delete[] memberArr;
}


void MemberHandler::addData(int membershipNumber, double totalAmountSpent)
{
    bool found = false;

    if(isEmpty())
    {
        memberArr[size].membershipNumber = membershipNumber;
        memberArr[size].totalAmountSpent = totalAmountSpent;
    }
    else
    {
        // searching
        // if there is a same memebrship number then update the totalAmountSpent
        // if there is not any match make sure the array is not full and then add a member to the array

        for(int i=0;i<size;i++)
        {
            if (memberArr[i].membershipNumber == membershipNumber)
            {
                memberArr[i].totalAmountSpent += totalAmountSpent;
                found = !found;
                break;
            }
        }

        if(!found)
        {
            if(isFull())
            {
                resize();
            }

            memberArr[size].membershipNumber = membershipNumber;
            memberArr[size].totalAmountSpent = totalAmountSpent;
        }


    }


    size++;

}



int MemberHandler::getSize()const
{
    return size;
}


bool MemberHandler::isEmpty()
{
    return size == 0 ? true : false;
}


bool MemberHandler::isFull()
{
    return size > capacity ? true : false;

}



void MemberHandler::resize()
{
    Member* temp_arr = new Member[capacity + 5];
    for (int i = 0; i < capacity; i++)
        temp_arr[i] = memberArr[i];

    delete[] memberArr;
    capacity += 5;
    memberArr = new Member[capacity];
    for (int i = 0; i < capacity; i++)
        memberArr[i] = temp_arr[i];
    //arr = temp_arr;
    delete[] temp_arr;
}



void MemberHandler::getData(int membershipNumber, double& totalAmountSpent, double& rebate)
{
     bool found = false;

    for(int i=0;i<size;i++)
    {
        if (memberArr[i].membershipNumber == membershipNumber)
        {
            totalAmountSpent =round(memberArr[i].totalAmountSpent);
            rebate = round((memberArr[i].totalAmountSpent * REBATE_AMOUNT) / 100);

            found = !found;
            break;
        }
    }

    if(!found)
    {
        // member did not buy anything yet!
        totalAmountSpent = 0;
        rebate = 0;
    }
}


double MemberHandler:: round(double var)
{
    // 37.66666 * 100 =3766.66
    // 3766.66 + .5 =3767.16    for rounding off value
    // then type cast to int so value is 3767
    // then divided by 100 so the value converted into 37.67
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}



