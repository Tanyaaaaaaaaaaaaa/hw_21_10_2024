#include <iostream>
#include <string>
using namespace std;

class Bankomat
{
private:
    int id;
    int balance100; //Купюры номиналом 100
    int balance200; //Купюры номиналом 200
    int balance500; //Купюры номиналом 500
    int balance1000; //Купюры номиналом 1000
    int minWithdraw; //Минимальная сумма для снятия
    int maxWithdraw; //Максимальная сумма для снятия

public:
    void initialize(int atmId, int minW, int maxW)
    {
        id = atmId;
        minWithdraw = minW;
        maxWithdraw = maxW;
        balance100 = balance200 = balance500 = balance1000 = 0;
    }

    void loadCash(int count100, int count200, int count500, int count1000)
    {
        balance100 += count100;
        balance200 += count200;
        balance500 += count500;
        balance1000 += count1000;
        cout << "The bills have been successfully loaded into the ATM" << endl;
    }

    bool withdraw(int amount)
    {
        if (amount < minWithdraw || amount > maxWithdraw)
        {
            cout << "Error : Amount must be between " << minWithdraw << " and " << maxWithdraw << endl;
            return false;
        }

        int totalBalance = balance100 * 100 + balance200 * 200 + balance500 * 500 + balance1000 * 1000;
        if (amount > totalBalance)
        {
            cout << "Error : There are insufficient funds in the ATM" << endl;
            return false;
        }

        int remaining = amount;
        int take1000 = min(remaining / 1000, balance1000);
        remaining -= take1000 * 1000;
        int take500 = min(remaining / 500, balance500);
        remaining -= take500 * 500;
        int take200 = min(remaining / 200, balance200);
        remaining -= take200 * 200;
        int take100 = min(remaining / 100, balance100);
        remaining -= take100 * 100;

        if (remaining > 0)
        {
            cout << "Error : It is impossible to issue the requested amount in the required denominations" << endl;
            return false;
        }

        balance1000 -= take1000;
        balance500 -= take500;
        balance200 -= take200;
        balance100 -= take100;

        cout << "Successfully withdrawned : " << amount << " $" << endl;
        return true;
    }

    string toString() const
    {
        int totalBalance = balance100 * 100 + balance200 * 200 + balance500 * 500 + balance1000 * 1000;
        return "Remaining amount at ATM : " + to_string(totalBalance) + " $";
    }
};

int main()
{
    Bankomat atm;
    atm.initialize(12345, 500, 20000);
    atm.loadCash(10, 10, 5, 2); //Загрузка 10 купюр по 100 , 10 по 200 , 5 по 500 и 2 по 1000
    cout << atm.toString() << endl;
    atm.withdraw(1500); //Снятие 1500 $
    cout << atm.toString() << endl;
    atm.withdraw(3000); //Снятие 3000 $
    cout << atm.toString() << endl;
    return 0;
}