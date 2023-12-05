#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
const int DataCount = 100000;
inline void quick_sort(long double a[], int l, int r){
    if (l < r){
        int i = l,j = r;
        long double x = a[i];
        while (i < j){
            while(i < j && a[j] > x) j--;
            if(i < j) a[i++] = a[j];
            while(i < j && a[i] < x) i++;
            if(i < j) a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i-1);
        quick_sort(a, i+1, r);
    }
}
inline long double compare(long double a[], int i){
    if(a[i+1] - a[i] > 0)
        return a[i+1] - a[i];
    else
        return (-1)*(a[i+1] - a[i]);
}
int main(){
    clock_t start, finish;
    double Total_time;
    start = clock();
    long double arr[DataCount];

    fstream my_file;
    my_file.open("D:\\Data Structure\\points.dat", ios::in);
    for(long double & i : arr)  my_file >> setprecision(10) >> i;
    quick_sort(arr,0,10000);
    for (int i = 0; i < DataCount; ++i) {
        arr[i] = compare(arr,i);
    }
    quick_sort(arr,0,DataCount-1);
    cout << setprecision(10) << arr[0];
    cout << endl;
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("program consume %f seconds\n", Total_time);
    return 0;
}
