#include<bits/stdc++.h>
using namespace std;
#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

string divisor_binary;

long long divisor_decimal;

vector<long long int> v;

string decimal_to_binary(long long int decimal)
{
    string s;

    while(decimal>0)
    {
        s.push_back(decimal%2+48);
        decimal/=2;
    }

    reverse(s.begin(),s.end());

    return s;
}

long long int binary_to_decimal(string binary)
{
    long long int sum=0,count=0;

    for(int i=binary.size()-1;i>=0;i--)
    {
        if(binary[i]=='1')
        {
            sum=sum+pow(2,count);
        }
        count++;
    }
    return sum;
}

long long error_generator(long long int t)
{
    long long int temp,r,p;

    temp=t;

    r=rand()%4;

    if(r==2)
    {
        p=rand()%20;

        temp=t^(1<<p);
    }
    return temp;
}

int digit_count(long long int decimal)
{
    string s;

    s=decimal_to_binary(decimal);

    return s.size();
}

long long int add_extra_bit(long long int decimal,int xtra_bit)
{
    return decimal<<xtra_bit;
}

void add_remainder(long long int decimal)
{
    long long divisor,dividend,main;

    dividend=add_extra_bit(decimal,digit_count(divisor_decimal)-1);
    main=dividend;
    divisor=add_extra_bit(divisor_decimal,digit_count(dividend)-digit_count(divisor_decimal));


    cout<<decimal_to_binary(dividend)<<endl<<decimal_to_binary(divisor)<<endl;

    while(1)
    {
        long long temp =dividend^divisor;

        cout<<"Dividend : "<<decimal_to_binary(dividend)<<endl<<"Divisor : "<<decimal_to_binary(divisor)<<endl<<"Remeinder : "<<decimal_to_binary(temp)<<endl;


        if(digit_count(temp)<digit_count(divisor_decimal))
        {
            int x=main^temp;

            cout<<"remiander :"<<decimal_to_binary(temp)<<endl;

            cout<<"Final : "<<decimal_to_binary(x);
            break;
        }

        divisor=add_extra_bit(divisor_decimal,digit_count(temp)-digit_count(divisor_decimal));
        dividend=temp;



    }

    //cout<<temp<<endl<<" "<<decimal_to_binary(temp);


}

int main()
{
    string dividend,divisor;

    cin>>dividend>>divisor;

    divisor_binary=divisor;

    divisor_decimal=binary_to_decimal(divisor);

    add_remainder(binary_to_decimal(dividend));



}
