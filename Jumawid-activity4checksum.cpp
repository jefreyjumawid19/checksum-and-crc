#include <iostream>
#include <math.h>
using namespace std;
int main()
{
string a;
int a1=0,a2=0,a3=0,a4=0,i=0;

/*At the sender side it tries to add frames using 1’s complement to get the sum. 
After that, it then complements the sum to get the checksum. 
It then sends it along with the data segments.*/
cout<<"Sender Side\n";
cout<<"Enter a 16 bit data word\n";                                                              /*input*/
cin>>a;
if(a.size()!=16)                                                                                 /*input should have 16 characters*/
{
cout<<"The dataword doesnt have 16 bits please re-enter\n";
cin>>a;
}
for(i=0;i<a.size();i++)
{
if(i<4)
{
if(a[i]=='1')
{
a1+=pow(2,3-i%4);
}
}
else if(i>=4 && i<8)
{
if(a[i]=='1')
{
a2+=pow(2,3-i%4);
}
}
else if(i>=8 && i<12)
{
if(a[i]=='1')
{
a3+=pow(2,3-i%4);
}
}
else if(i>=12 && i<16)
{
if(a[i]=='1')
{
a4+=pow(2,3-i%4);
}
}
}
int sum;
sum=a1+a2+a3+a4;
int bsum[32];
i=0;
while (sum > 0) 
{
bsum[i] = sum % 2;sum = sum / 2;i++;
}
int length_bsum=i-1,carry=0;int arr2[4],arr3[4]={0,0,0,0};
for(int k=0;k<=3;k++)
{
arr2[3-k]=bsum[k];
}
int j=0;
int flag=0;
for(i=4;i<length_bsum+1;i++)
{
arr3[3-flag]=bsum[i];flag++;
}
int chksum[4]={0,0,0,0};
for(i=3;i>=0;i--)
{
sum=arr2[i]+arr3[i]+carry;
carry=sum/2;
if(sum%2==0)
chksum[i]=0;
else
chksum[i]=1;
}
i=3;
if(carry!=0)
{
for(i=3;i>=0;i--)
{
sum=chksum[i]+carry;
carry=sum/2;
if(sum%2==0)
chksum[i]=0;
else
chksum[i]=1;
}
}
for(i=0;i<4;i++)
{
chksum[i]=(chksum[i]==0)?1:0;
}
cout<<"The final checksum is :";
for(i=0;i<4;i++)
{
cout<<chksum[i];
}
cout<<"\nThe codeword sent to the receiver is :";
cout<<a;
for(i=0;i<4;i++)
{
cout<<chksum[i];
}
string receiver;
/*here the receiver adds the incoming frames along with the checksum. 
This is done by using 1’s complement to get the sum and then complement it.*/
cout<<"\n\nReceiver Side\n";
cout<<"Enter the receiver side codeword: ";             
cin>>receiver;
int ra1=0,ra2=0,ra3=0,ra4=0,ra5_chksum=0;
for(i=0;i<receiver.size();i++)
{
if(i<4)
{
if(receiver[i]=='1')
{
ra1+=pow(2,3-i%4);
}
}
else if(i>=4 && i<8)
{
if(receiver[i]=='1')
{
ra2+=pow(2,3-i%4);
}
}
else if(i>=8 && i<12)
{
if(receiver[i]=='1')
{
ra3+=pow(2,3-i%4);
}
}
else if(i>=12 && i<16)
{
if(receiver[i]=='1')
{
ra4+=pow(2,3-i%4);
}
}
else if( i>=16 && i<20)
{
if(receiver[i]=='1')
{
ra5_chksum+=pow(2,3-i%4);
}
}
}
int rec_sum;rec_sum=ra1+ra2+ra3+ra4+ra5_chksum;
int bin_rec_sum[4];
i=0;
while (rec_sum > 0) 
{
bin_rec_sum[i] = rec_sum % 2;
rec_sum = rec_sum / 2;
i++;
}
int rec_arr2[4],rec_arr3[4]={0,0,0,0};
for(int k=0;k<=3;k++)
{
rec_arr2[3-k]=bin_rec_sum[k];
}
j=0;
flag=0;
for(i=4;i<length_bsum+1;i++)
{
rec_arr3[3-flag]=bin_rec_sum[i];
flag++;
}
sum=0,carry=0;
int rec_chksum[4]={0,0,0,0};
for(i=3;i>=0;i--)
{
sum=rec_arr2[i]+rec_arr3[i]+carry;
carry=sum/2;
if(sum%2==0)rec_chksum[i]=0;
else
rec_chksum[i]=1;
}
i=3;
if(carry!=0)
{
for(i=3;i>=0;i--)
{
sum=rec_chksum[i]+carry;
carry=sum/2;
if(sum%2==0)
rec_chksum[i]=0;
else
rec_chksum[i]=1;
}
}
for(i=0;i<4;i++)
{
rec_chksum[i]=(rec_chksum[i]==0)?1:0;
}
cout<<"\nThe Sums complement is :";                          /*output*/
flag=0;
for(i=3;i>=0;i--)
{
cout<<rec_chksum[i];
if(rec_chksum[i]!=0)
flag++;
}
if(flag!=0)

cout<<"\nTHERE IS AN ERROR\n";          
else
cout<<"\nTHERE IS NO ERROR\n";
return 0;
}
