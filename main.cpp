#include <iostream>
#include "SkipList.h"

void test01()
{
    SkipList s(6);
    cout << "\nInitialized SkipList " << endl;
    cout << s << endl;
    for (int i = 0; i < 11; i++)
    {
        //cout << "testing test1 for loop " << i << endl;
        int number = rand() % 100;
        s.Add(number);
        cout << "\nAfter adding " << number  << endl;
        cout << s << endl;
    }
    cout<< "done";
}


void test02()
{
    SkipList s(2);
    //cout << "\nInitialized SkipList --" << endl;
    cout << s << endl;
    for (int i = 0; i < 11;i++)
    {
        int number = rand() % 100;
        s.Add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;

    }

}


void test03()
{
    SkipList s(3);
   // cout << "\nInitialized SkipList --" << endl;
    cout << s << endl;
    for (int i = 0; i < 11; i++)
    {
        int number = rand() % 22;
        s.Add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
    for (int i = 0; i < 11; i++)
    {
        int number = rand() % 22;
        if (s.Contains(number) )
        {
           s.Remove(number);
           cout << "After removing " << number  << endl;
           cout << s << endl;
        }
    }
}


void test04()
{
    SkipList s(4);
    //cout << "\nInitialized SkipList --" << endl;
    cout << s << endl;
    for (int i = 0; i < 22; i++)
    {
        int number = rand() % 100;
        s.Add(number);
        cout << "After adding " << number <<  endl;
        cout << s << endl;
    }
}


void test05()
{
    SkipList s(5);
    //cout << "\nInitialized SkipList --" << endl;
    cout << s << endl;
    for (int i = 0; i < 22; i++)
    {
        int number = rand() % 100;
        s.Add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
}


int main()
{
    srand(time(0));

    test01();
    test02();
    test03();
    test04();
    test05();

    return 0;
}