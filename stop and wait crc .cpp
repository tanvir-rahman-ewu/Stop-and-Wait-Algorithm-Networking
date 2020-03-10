#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

string divisor_binary="11000000000000101";

long long divisor_decimal=98309;

long long cfc,bit_no,Remainder;

vector<long long int> v,temp;

///decimal to binary conversion

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

/// binary to decimal conversion

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

/// Frame Generating Randomly

void frame_generating_randomly(int frame)
{
    for(int i=0;i<frame;i++)
    {
        string s;

        for(int i=0;i<40;i++)
        {
            s.push_back(rand()%2 + 48);
        }
        if(s[0]=='0')
        {
            s[0]='1';
        }
        v.push_back(binary_to_decimal(s));
    }
}

///error generator randomly

long long error_generator(long long int t)
{
    long long int temp,r,p;

    temp=t;

    r=rand()%2;

    if(r==0)
    {
        p=rand()%20;

        temp=t^(1<<p);
    }
    return temp;
}

///counting digit of a binary number

int digit_count(long long int decimal)
{
    string s;

    s=decimal_to_binary(decimal);

    return s.size();
}

///adding extra bit

long long int add_extra_bit(long long int decimal,int xtra_bit)
{
    return decimal<<xtra_bit;
}

/// remainder generating

long long int add_remainder(long long int decimal)
{
    long long divisor,dividend,main;

    dividend=add_extra_bit(decimal,16);

    main=dividend;

    divisor=add_extra_bit(divisor_decimal,digit_count(dividend)-digit_count(divisor_decimal));

    while(1)
    {
        long long temp =dividend^divisor;

        if(digit_count(temp)<digit_count(divisor_decimal))
        {
            long long int x=main^temp;

            cfc=temp;

            return x;
        }

        divisor=add_extra_bit(divisor_decimal,digit_count(temp)-digit_count(divisor_decimal));

        dividend=temp;
    }
}

/// Show Error Bit

void show_error_bit(long long int a,long long int b)
{
    string s1,s2;

    s1=decimal_to_binary(a);
    s2=decimal_to_binary(b);

    cout<<"The resulting checksum is : "<<decimal_to_binary(cfc)<<endl<<endl;

    if(s1!=s2)
    {
        cout<<"Sent Frame     : ";

        for(int  i=0;i<s1.size();i++)
        {
            if(s1[i]!=s2[i])
            {
                cout<<"[ "<<s1[i]<<" ]";
                bit_no=s1.size()-i;
            }
            else
            {
                cout<<s1[i];
            }
        }

        cout<<endl<<endl<<"Received Frame : ";

        for(int  i=0;i<s1.size();i++)
        {
            if(s1[i]!=s2[i])
            {
                cout<<"[ "<<s2[i]<<" ]";
            }
            else
            {
                cout<<s2[i];
            }
        }
        cout<<endl<<endl;
    }
    else
    {
        cout<<"Sent Frame     : "<<s1<<endl<<"Received Frame : "<<s2<<endl;
    }

}

///CRC checking

bool check_crc(long long int decimal)
{
    long long divisor,dividend,main,a,b;

    dividend=add_remainder(decimal);
    a=dividend;

    dividend=error_generator(dividend);
    b=dividend;

    show_error_bit(a,b);


    divisor=add_extra_bit(divisor_decimal,digit_count(dividend)-digit_count(divisor_decimal));

    while(1)
    {
        long long temp=dividend^divisor;

        if(temp==0)
        {
            return true;
        }
        else if(digit_count(temp)<digit_count(divisor_decimal))
        {
            Remainder=temp;
            return false;
        }

        divisor=add_extra_bit(divisor_decimal,digit_count(temp)-digit_count(divisor_decimal));
        dividend=temp;
    }
}

void show_frame(int frame)
{
    cout<<"All Frames : "<<endl<<endl;

    for(int i=0;i<frame;i++)
    {
        cout<<"f("<<i<<") :  "<<decimal_to_binary(v[i])<<endl;
    }

    cout<<endl<<"(Frame Size : 40 bits)"<<endl;
}

void show_ack(string s,int k)
{
    string w="     ";

    for(int i=12;i>0;i--)
    {
            cout<<"Transmitter :                                                     :  Reciver " <<endl;
            cout<<"      ";
            for(int j=0;j<i-1;j++)
            {
                 cout<<w;
            }
            cout<<s<<"->"<<k;

            Sleep(200);

            system("cls");
    }
}
int main()
{
    srand(time(NULL));

    int frame;

    cout<<"Enter Number Of Frame : ";

    cin>>frame;

    frame_generating_randomly(frame);


    system("cls");

    show_frame(frame);

    cout<<endl;

    system("pause");

    for(int i=0;i<frame;i++)
    {
        temp.push_back(v[i]);
    }

    string w="    ";
    int flag=1,r;

    for(int k=0;k<v.size();)
    {
        system("cls");



        for(int i=0;i<14;i++)
        {
            if(k%2)
            {
                r=1;
            }
            else
            {
                r=0;
            }

            if(flag)
            {
                 cout<<"Sending Frame ["<<r<<"] "<<endl<<endl;
            }
            else
            {
                cout<<"Resending Frame ["<<r<<"] "<<endl<<endl;
            }

            cout<<"Transmitter :                                                     :  Reciver " <<endl;
            cout<<"         ";
            for(int j=0;j<=i;j++)
            {
                 cout<<w;
            }
            cout<<decimal_to_binary(v[k]);

            Sleep(300);

            system("cls");
        }

        int ans=check_crc(temp[k]);

        if(ans==1)
        {

            cout<<endl<<"Transfer Result : Successful"<<endl<<endl;
            cout<<"Remainder : 0"<<endl<<endl;;
            system("pause");
            system("cls");
            show_ack("ACK",k%2==0?1:0);
            k++;
            flag=1;
        }
        else
        {
            cout<<endl<<"Transfer Result : Unsuccessful "<<endl<<endl;

            cout<<"From Right Hand Side "<<bit_no<<" no. Bit is Changed !(Error)"<<endl<<endl;

            cout<<"Remainder : "<<decimal_to_binary(Remainder)<<endl<<endl;

            system("pause");
            system("cls");
            show_ack("ACK",k%2==0?0:1);
            flag=0;
        }

        system("pause");

    }
}
