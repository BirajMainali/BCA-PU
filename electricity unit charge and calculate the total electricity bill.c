#include<stdio.h>


int CalculateBill(float unit, float rate, float ratio);

int main()
{
    float ServiceChargeRate = 20;
    float Unit;
    printf("Enter the Unit:\t");
    scanf("%f", & Unit);

    if (Unit <= 50)
    {
        CalculateBill(Unit, ServiceChargeRate, 0.50);
    }
    else if (Unit <= 99)
    {
        CalculateBill(Unit, ServiceChargeRate, 0.75);
    }
    else if (Unit < 100)
    {
        CalculateBill(Unit, ServiceChargeRate, 1.20);
    }
    else
    {
        CalculateBill(Unit, ServiceChargeRate, 1.50);
    }
}

int CalculateBill(float unit, float rate, float ratio)
{
    float PaidAmount;
    float serviceCharge;
    float WithRatio;

    WithRatio = (unit * ratio);
    serviceCharge = (WithRatio * rate / 100);
    PaidAmount = WithRatio + serviceCharge;

    printf("_________________________________\n");
    printf("Ratio:\t%f\n", ratio);
    printf("Unit:\t%f\n", unit);
    printf("WithRatio:\t%f\n", WithRatio);
    printf("serviceCharge:\t%f\n", serviceCharge);
    printf("_________________________________\n");
    printf("Paid Amount:\t%f", PaidAmount);

    return 0;
}
