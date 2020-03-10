#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

int FrameSize,WindowSize;
char Reminder[500]= {};



char* CRC16(char *frame,char devi[])
{
    int i,j,devilen,framelen;
    char temp[500],quot[100],rem[500],devi1[500],xtra[500];
    char fin[500]= {};

    devilen=strlen(devi);
    framelen=strlen(frame);

    strcpy(devi1,devi);
    strcpy(xtra,frame);
    //cout<<"rk:"<<xtra<<endl;
    for (i=0; i<devilen-1; i++){
        xtra[framelen+i]='0';
    }


    for (i=0; i<devilen; i++){
        temp[i]=xtra[i];
    }


    for (i=0; i<framelen; i++)
    {
        quot[i]=temp[0];
        if(quot[i]=='0')
        {
            for (j=0; j<devilen; j++){
                devi[j]='0';
            }

        }
        else
        {
            for (j=0; j<devilen; j++){
                devi[j]=devi1[j];
            }

        }

        for (j=devilen-1; j>0; j--)
        {
            if(temp[j]==devi[j]){
                rem[j-1]='0';
            }

            else{
                rem[j-1]='1';
            }

        }

        rem[devilen-1]=xtra[i+devilen];
        strcpy(temp,rem);
    }

    strcpy(rem,temp);
    for (i=0; i<devilen-1; i++){
        Reminder[i]=rem[i];
    }


    for (i=0; i<framelen; i++){
        fin[i]=frame[i];
    }

    for (j=0; i<framelen+devilen-1; i++,j++){
        fin[i]=rem[j];
    }

    return fin;
}


bool ErrorFind(char* frame,char P[])
{
    int IsSafe,ranindex;
    char changed_frame[1000];
    strcpy(changed_frame,CRC16(frame,P));

    IsSafe=rand()%2; // if IsSafe is 0 then we will forcefully make an error

    ranindex=rand()%40; // randomely select an index to change if IsSafe is 0
    if(!IsSafe)
    {
        if(changed_frame[ranindex]=='1')
        {
            changed_frame[ranindex]='0';
        }

        else{
            changed_frame[ranindex]='1';
        }

    }
    strcpy(changed_frame,CRC16(changed_frame,P));

    //printf("\n\nReminder:%s\n",Reminder);
    cout<<right<<setw(55);

    cout<<"Reminder :"<<Reminder<<endl;
    for(int i=0; Reminder[i]; i++)
    {
        if(Reminder[i]=='1')
        {
            return true;
        }
    }

    return false;
}


int main()
{

    srand(time(NULL));
    char Frame[500][500];
    int i,start,last,chk=2,SW_bit,flag=0;

    printf("Enter the total number of frames to be transmitted: ");
    cin>>FrameSize;

    cout << "  *** for simplicity we use -------- " << endl;
    cout << "  *** 40 bit DATA segment"<< endl<<endl;


    for(i=0; i<FrameSize; i++)
    {
        for(int j=0; j<40; j++)
        {
            Frame[i][j]=((rand()%2)+48);   //Randomly Generate 40 bit for per frame

        }
    }
    cout<<right<<setw(60);
    cout<<"*Sending Frame[0] To Frame["<<FrameSize-1<<"]*"<<endl;
    cout<<right<<setw(90);
    cout<<"[SENDER]--------->--------->-------->-------->------>[RECEIVER]"<<endl;
    i=0;
    for(i=0; i<FrameSize; )
    {

        start=i;
        last=(FrameSize-1);

        cout<<endl;

        for(int j=start; j<=last; j++)
        {
            chk=0;
            char P[]="11000000000000101";

            printf("Press Enter to continue...");
            getch();
            system("cls");
            cout<<right<<setw(32);
            cout<<"Current frame["<<j<<"] out of "<< FrameSize <<" : "<<Frame[j]<<endl;
            cout<<endl;
            cout<<right<<setw(55);
            cout<<"Divisor: "<<P<<endl;
            cout<<endl;

            if(!ErrorFind(Frame[j],P))
            {
                if((j+1)%2 != 0)
                {
                    SW_bit=0;
                    printf("\n\n!!!!!!!!!!! Here the remainder is '0' using CRC16 method, The Frame[%d] is Successfully Received !!!!!!!!\n\n\n",SW_bit);
                    cout<<right<<setw(65);
                    cout<<"*Acknowledgment (ACK-1) sent*"<<endl;
                    cout<<right<<setw(90);
                    cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;
                    if(j==last)
                     {
                         flag=1;
                     }

                }
                else
                {
                     SW_bit=1;
                     printf("\n\n!!!!!!!!!!! Here the remainder is '0' using CRC16 method, The Frame[%d] is Successfully Received !!!!!!!!\n\n\n",SW_bit);
                     cout<<right<<setw(65);
                     cout<<"*Acknowledgment (ACK-0) sent*"<<endl;
                     cout<<right<<setw(90);
                     cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;
                     if(j==last)
                     {
                         flag=1;
                     }
                }

            }
            else
            {
                if((j+1)%2 != 0)
                {
                    SW_bit=0;
                    printf("\n\n!!!!!!!!!!! As all the bit of the remainder is not '0' using CRC16 method, The Frame[%d] is corrupted !!!!!!!!!\n\n",SW_bit);
                    cout << "!!!!!!!!!!! Need to Re-Send Frame[" << SW_bit << "] !!!!!!!!!!!" << endl << endl;
                    cout<<right<<setw(69);
                    cout<<"*Negative Acknowledgment (NAK-" << SW_bit <<") sent*"<<endl;
                    cout<<right<<setw(90);
                    cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;
                }
                else
                {
                    SW_bit=1;
                    printf("\n\n!!!!!!!!!!! As all the bit of the remainder is not '0' using CRC16 method, The Frame[%d] is corrupted !!!!!!!!!\n\n",SW_bit);
                    cout << "!!!!!!!!!!! Need to Re-Send Frame[" << SW_bit << "] !!!!!!!!!!!" << endl << endl;
                    cout<<right<<setw(69);
                    cout<<"*Negative Acknowledgment (NAK-" << SW_bit << ") sent*"<<endl;
                    cout<<right<<setw(90);
                    cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;

                }

                i=j;
                chk=1;

            }
            if(chk==1)
            {
                break;
            }
        }
        if(flag==1)
        {
            break;
        }

    }

    cout<<endl<<endl<<endl<<right<<setw(50);
    cout<<left<<' ';
    cout<<' ';
    for(int j=0; j<FrameSize; j++)
        cout<<j<<',';
    cout<<endl;
    cout<<"\n\n!!!!!!!!!!! All frames are transmitted Successfully !!!!!!!!!!!\n\n\n\n";
     cout<<right<<setw(40);

    return 0;


}













