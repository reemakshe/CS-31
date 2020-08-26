//
//  main.cpp
//  cs31Project6
//
//  Created by Reema Kshetramade on 11/23/19.
//  Copyright © 2019 Reema Kshetramade. All rights reserved.
//

#include <iostream>
using namespace std;


//Problem 1a
//int main()
//    {
//        int arr[3] = { 5, 10, 15 };
//        int* ptr = arr;
//
//        *ptr = 30;          // set arr[0] to 30
//        *(ptr + 1) = 20;      // set arr[1] to 20
//        ptr += 2;
//        *ptr = 10;        // set arr[2] to 10
//        ptr -= 2;
//
//        while (ptr < arr + 3)
//        {
//            cout << *ptr << endl;    // print values
//            ptr++;
//        }
//    }



//Problem 1b
//void findMax(int arr[], int n, int*& pToMax)
//    {
//        if (n <= 0)
//            return;      // no items, no maximum!
//
//        pToMax = arr;
//
//        for (int i = 1; i < n; i++)
//        {
//            if (arr[i] > *pToMax)
//                 pToMax = arr + i;
//        }
//    }
//
//int main()
//    {
//        int nums[4] = { 5, 3, 15, 6 };
//        int* ptr;
//
//        findMax(nums, 4, ptr);
//        cout << "The maximum is at address " << ptr << endl;
//        cout << "It's at position " << ptr - nums << endl;
//        cout << "Its value is " << *ptr << endl;
//    }

//Problem 1c
//void computeCube(int n, int* ncubed)
//    {
//        *ncubed = n * n * n;
//    }
//
//    int main()
//    {
//        int x = 0;
//        int* ptr = &x;
//        computeCube(5, ptr);
//        cout << "Five cubed is " << *ptr << endl;
//    }


//Problem 1d
//bool strequal(const char str1[], const char str2[])
//    {
//        while (*str1 != 0  &&  *str2 != 0)
//        {
//            if (*str1 != *str2)  // compare corresponding characters
//                return false;
//            str1++;            // advance to the next character
//            str2++;
//        }
//        return *str1 == *str2;   // both ended at same time?
//    }
//
//    int main()
//    {
//        char a[15] = "Chang";
//        char b[15] = "Cheng";
//
//        if (strequal(a,b))
//            cout << "They're the same person!\n";
//    }

//Problem 1e
//int* nochange(int* p)
//{
//    return p;
//}
//
//int* getPtrToArray(int& m)
//{
//    int anArray[100];
//    for (int j = 0; j < 100; j++)
//        anArray[j] = 100-j;
//    m = 100;
//    return nochange(anArray);
//}
//
//void f()
//{
//    int junk[100];
//    for (int k = 0; k < 100; k++)
//        junk[k] = 123400000 + k;
//    junk[50]++;
//}
//
//int main()
//{
//    int n;
//    int* ptr = getPtrToArray(n);
//    f();
//    for (int i = 0; i < 3; i++)
//        cout << ptr[i] << ' ';
//    for (int i = n-3; i < n; i++)
//        cout << ptr[i] << ' ';
//    cout << endl;
//}


//Problem 2
//int main()
//{
//    double* cat;
//    double mouse[5] = {0, 1, 2, 3, 4};
//    cat = mouse + 4;
//    *cat = 25;
//    *(mouse + 3) = 54;
//    cat -= 3;
//    cout << *cat << endl;
//    cat[1] = 27;
//    cat[0] = 42;
//    bool b = (*cat == *(cat + 1));
//    bool d = (cat == mouse);
//
//}

//Problem 3a
//double mean(const double* scores, int numScores)
//{
//    const double* ptr = scores;
//    double tot = 0;
//    while (ptr != scores + numScores)
//    {
//        tot += *ptr;
//        ptr++;
//    }
//    return tot/numScores;
//}
//
//double mean2(const double* scores, int numScores)
//{
//    double tot = 0;
//    int i = 0;
//    while (scores + i != scores + numScores)
//    {
//        tot += *(scores + i);
//        i++;
//    }
//    return tot/numScores;
//}
//
//
//int main()
//{
//    double scores[5] = {92, 95, 93, 97, 99};
//    const double* scoresPtr = scores;
//    cout << mean(scoresPtr, 5) << endl;
//    cout << mean2(scoresPtr, 5) << endl;
//}


//Problem 3b and 3c
//const char* findTheChar(const char str[], char chr)
//{
//    for (int k = 0; str[k] != 0; k++)
//        if (str[k] == chr)
//            return &str[k];
//
//    return nullptr;
//}
//
//const char* findTheChar2(char* str, char chr)
//    {
//        for (int k = 0; *(str + k) != 0; k++)
//            if (*(str + k) == chr)
//                return (str + k);
//
//        return nullptr;
//    }
//
//const char* findTheChar3(char* str, char chr)
//    {
//        while (*str != 0)
//        {
//            if (*str == chr)
//                return str;
//
//         str++;
//        }
//
//        return nullptr;
//    }
//
//
//int main()
//{
//    char str[6] = "hello";
//    cout << findTheChar(str, 'e') << endl;
//    cout << findTheChar2(str, 'e') << endl;
//    cout << findTheChar3(str, 'e') << endl;
//}

//Problem 4
//int* maxwell(int* a, int* b)
//{
//    if (*a > *b)
//        return a;
//    else
//        return b;
//}
//
//void swap1(int* a, int* b)
//{
//    int* temp = a;
//    a = b;
//    b = temp;
//}
//
//void swap2(int* a, int* b)
//{
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//int main()
//{
//    int array[6] = { 5, 3, 4, 17, 22, 19 };
//
//    int* ptr = maxwell(array, &array[2]);
//    *ptr = -1;
//    ptr += 2;
//    ptr[1] = 9;
//    *(array+1) = 79;
//
//    cout << &array[5] - ptr << endl;
//
//    swap1(&array[0], &array[1]);
//    swap2(array, &array[2]);
//
//    for (int i = 0; i < 6; i++)
//        cout << array[i] << endl;
//}


//Problem 5
//void removeS(char* str)
//{
//    char* ptr;
//    while (*str != 0) {
//        ptr = str;
//        if (*str == 's' || *str == 'S') {
//            while (*ptr != 0) {
//                *ptr = *(ptr + 1);
//                ptr++;
//            }
//        }
//        else
//            str++;
//    }
//}
//
//
//int main()
//{
//    char msg[50] = "She'll be a massless princess.";
//    removeS(msg);
//    cout << msg<< endl;  // prints   he'll be a male prince.
//}
//
