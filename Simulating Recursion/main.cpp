#include <iostream>
#include <stack>

using namespace std;

int cur_subset[100];

struct subsetArr
{
    int start;
    int remain;
    int cur_ind;
};

GenerateSubsetsIterative(int* a, int k, int n, int start, int remain)
{
    subsetArr itStart={start,remain,0};
    stack<subsetArr> caller;
    caller.push(itStart);

    while (!caller.empty())
    {
        subsetArr cal1 =caller.top();   caller.pop();

        if(cal1.start==n)
        {
            if(cal1.cur_ind==k)
            {
                for(int i=0;i<k;i++)
                    cout<<cur_subset[i]<<" ";
                cout<<endl;
            }
            continue;
        }

        subsetArr cal2;
        if(n-start>remain)
        {
            cal2.start=cal1.start+1;    cal2.remain=cal1.remain;    cal2.cur_ind=cal1.cur_ind;
            caller.push(cal2);
        }

        if(cal1.remain>0)
        {
            cur_subset[cal1.cur_ind++]=a[cal1.start];
            cal2.start=cal1.start+1;    cal2.remain=cal1.remain-1;  cal2.cur_ind=cal1.cur_ind;
            caller.push(cal2);
            cal1.cur_ind--;
        }

    }
}


void GenerateSubsets(int* a, int k, int n)
{
    GenerateSubsetsIterative(a, k, n, 0, k);
}

int main()
{
    int a[]={1,3,5,8,10}; int n=sizeof(a)/sizeof(a[0]), k=3;
    GenerateSubsets(a, k, n);
    return 0;
}
