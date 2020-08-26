//
//  practice.cpp
//  cs31Project5
//
//  Created by Reema Kshetramade on 11/18/19.
//  Copyright © 2019 Reema Kshetramade. All rights reserved.
//

#include <iostream>

using namespace std;

void zeroLeft(int array[], int array_size);

int main()
{
    char names[34] = "Anthony Millie Sophia Nina Kyle ";
    int count = 0;
    
    for (int i = 0; names[i] != '\0'; i++)
    {
        int j = i;
        
        if (count == 0)
        {
            for (j = i; names[j] != '\0' && names[j] != ' '; j++)
            {
                if (j % 2 == 0)
                    cout << names[j];
            }
            cout << j;
        }
        else if (count == 2)
        {
            for (j = i; names[j] != '\0' && names[j] != ' '; j++)
            {
                if (j % 2 == 0)
                    cout << names[j - 1];
            }
        }
        else if (count == 1)
        {
            cout << names[j + 1];
            for (j = i; names[j] != '\0' && names[j] != ' '; j++);
            cout << j;
            
        }
        else
        {
            cout << names[j];
            for (j = i; names[j] != '\0' && names[j] != ' '; j++);
        }
        i = j;
        count++;
    }
    cout << endl;
}

void zeroLeft(int array[], int array_size)
{
    int swapIndex = 0;
    int currNum;
    for (int i = 0; i < array_size; i++)
    {
        currNum = array[i];
        if (currNum == 0)
        {
            array[i] = array[swapIndex];
            array[swapIndex] = currNum;
            swapIndex++;
        }
    }
}
