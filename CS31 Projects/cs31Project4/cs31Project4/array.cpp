//
//Reema Kshetramade
//SID: 205328402

#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);

int lookup(const string a[], int n, string target);

int positionOfMax(const string a[], int n);

int rotateLeft(string a[], int n, int pos);

int countRuns(const string a[], int n);

int flip(string a[], int n);

int differ(const string a1[], int n1, const string a2[], int n2);

int subsequence(const string a[], int n1, const string a2[], int n2);

int lookupAny(const string a1[], int n1, const string a2[], int n2);

int separate(string a[], int n, string separator);


//Append string value to each element in array of size n
int appendToAll(string a[], int n, string value)
{
    //It is an error if the array size is negative so function returns -1
    if (n < 0)
        return -1;
    
    //For n elements in the array, append the string value onto each element
    for (int i = 0; i < n; i++)
    {
        a[i] += value;
    }
    
    //Return number of elements in array
    return n;
}

//Return the index of string target in array of size n
int lookup(const string a[], int n, string target)
{
    //Error if array size n is negative
    if (n < 0)
        return -1;
    
    //For n elements in array, check if each one is equal to target and return index of first match
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;
    }
    
    //Return -1 if no element in array matches target
    return -1;
}

//Return index of the max string in array of size n
int positionOfMax(const string a[], int n)
{
    //Error if array size is negative
    if (n < 0)
        return -1;
    
    //Variables for the max string and position of max string
    string maxString = "";
    int pos = -1;

    //Loop through each value in array
    for (int i = 0; i < n; i++)
    {
        //If the current element is greater than the current max string, set max string to the current element
        //and set pos to index of current element (which is the new max string)
        if (a[i] > maxString)
        {
            maxString = a[i];
            pos = i;
        }
            
    }
    
    //Return the position of the max string
    return pos;
}

//Rotate each element from index pos to n left
int rotateLeft(string a[], int n, int pos)
{
    //Error if size of array or position of first element is negative or if position is outside of array
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    
    //Store the first string in a variable because it will be replaced after
    string firstString = a[pos];
    
    for (int i = pos + 1; i < n; i++) {
        //To rotate left, set the element to the left of the current position equal to current element
        a[i - 1] = a[i];
    }
    
    //Set the last element in the array to the eliminated first string value
    a[n - 1] = firstString;
    
    //Return the position of the first element that was rotated
    return pos;
}

//Count the number of runs of consecutive values that occur once or more
int countRuns(const string a[], int n)
{
    //Error if the array size is negative
    if (n < 0)
        return -1;
    
    //Set runCount to 0 and intialize currWord to empty string
    int runCount = 0;
    string currWord = "";
    
    for (int i = 0; i < n; i++) {
        //Increase runCount if the current element is not equal to currWord (the word of the current run)
        //and set currWord to the current element to start a new run
        if (a[i] != currWord)
        {
            runCount++;
            currWord = a[i];
        }
    }
    
    //Return the number of consecutive word runs in the array
    return runCount;
}

//Reverse the elements of the array
int flip(string a[], int n)
{
    //Error if the array size is negative
    if (n < 0)
        return -1;
    
    string currWord = "";
    
    //Loop through half the number of elements in the array because the other half of elements
    //are accessed by subtracting i from the size of the array
    for (int i = 0; i < n / 2; i++) {
        //Switch the word at the current index and the word at the same distance from end of the array
        currWord = a[n - 1 - i];
        a[n - 1 - i] = a[i];
        a[i] = currWord;
    }
    
    //Return size of array
    return n;
}

//Find the index of the first difference between corresponding elements of two arrays
int differ(const string a1[], int n1, const string a2[], int n2)
{
    //Error if either array size is negative
    if (n1 < 0 || n2 < 0)
        return -1;
    
    int endIndex = 0;
    //Set the index to end the for loop to the smaller array size so loop doesn't access element not in array
    if (n2 > n1)
        endIndex = n1;
    else
        endIndex = n2;
    
    for (int i = 0; i < endIndex; i++) {
        //If the corresponding elements in a1 and a2 are not equal, return the index of this difference
        if (a1[i] != a2[i])
            return i;
    }
    
    //If both arrays are equal until one runs out, the smaller array size is returned
    return endIndex;
}

//Check if one array is subsequence of another
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    //Error if either array size is negative, or the subsequence array size is larger than the first array
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;
    
    //If the subsequence is an array of 0 elements, this always occurs at index 0 in any array
    if (n2 == 0)
        return 0;
    
    for (int i = 0; i < n1 - n2; i++) {
        for (int j = 0; j < n2; j++) {
            //If the corresponding elements in each array are not equal, so break out of loop
            //This goes to next iteration of outer loop and check for subsequence at the next i
            if (a1[i + j] != a2[j]) {
                break;
            }
            //If you reach the last element of the subsequence array, then subsequence is in the array at i
            if (j == n2 - 1) {
                return i;
            }
        }
    }
    
    //If this point is reached, then subsequence has not been found in array
    return -1;
}

//Finds index of any element in a2 if it occurs in a1
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    //Error if either array size is negative
    if (n1 < 0 || n2 < 0)
        return -1;
    
    //Loop through each element in first array
    for (int i = 0; i < n1; i++) {
        //Loop through each element in second array
        for (int j = 0; j < n2; j++) {
            //If current element in a1 is equal to curr element in a2, return index i of element in a1
            if (a1[i] == a2[j]) {
                return i;
            }
        }
    }
    
    //If no matches were found, return -1
    return -1;
}

//Separate elements in array by those less than separator and those greater than separator
int separate(string a[], int n, string separator)
{
    //Error if array size is negative
    if (n < 0)
        return -1;
    
    string tempWord = "";
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        //Hold word that may be replaced in separate variable
        tempWord = a[count];
        
        //If the current word is less than the separator swap current element with element 'count' distance
        //from the start of the array
        if (a[i] < separator) {
            a[count] = a[i];
            a[i] = tempWord;
            //Count is incremented each time a word less than separator is moved to the beginning of array
            count++;
        }
    }
    
    //If the separator is in the array, place it at the index after the last word in array that was swapped
    int isSepIn = lookup(a, n, separator);
    if (isSepIn != -1) {
        a[isSepIn] = a[count];
        a[count] = separator;
    }
    
    //Return the position of element that is not less than separator
    return count;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool separatecheck(const string a[], int n, int p, string separator)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= separator)
            return false;
    for ( ; p < n  &&  a[p] == separator; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= separator)
            return false;
    string b[100];
    copy(a, a+n, b);
    sort(b, b+n);
    return equal(b, b+n, c);
}

void testone(int n)
{
    const int N = 6;

          // Act as if  a  were declared:
          //   string a[N] = {
          //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
          //   };
          // This is done in a way that will probably cause a crash if
          // a[-1] or a[N] is accessed:  We place garbage in those positions.
    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~string();
    a[N].string::~string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };

    string d[9] = {
        "alpha", "beta",  "beta", "beta", "alpha",
        "alpha", "delta", "beta", "beta"
    };

    switch (n)
    {
                     case  1: {
        assert(appendToAll(z, -1, "rho") == -1 && a[0] == "alpha");
            } break; case  2: {
        assert(appendToAll(z, 0, "rho") == 0 && a[0] == "alpha");
            } break; case  3: {
        assert(appendToAll(a, 1, "rho") == 1 && a[0] == "alpharho" &&
                            a[1] == "beta");
            } break; case  4: {
        assert(appendToAll(a, 6, "rho") == 6 && a[0] == "alpharho" &&
            a[1] == "betarho" && a[2] == "gammarho" &&
            a[3] == "gammarho" && a[4] == "betarho" &&
            a[5] == "deltarho");
            } break; case  5: {
        assert(lookup(z, -1, "alpha") == -1);
            } break; case  6: {
        assert(lookup(z, 0, "alpha") == -1);
            } break; case  7: {
        assert(lookup(a, 1, "alpha") == 0);
            } break; case  8: {
        assert(lookup(a, 6, "delta") == 5);
            } break; case  9: {
        assert(lookup(a, 6, "beta") == 1);
            } break; case 10: {
        assert(lookup(a, 6, "zeta") == -1);
            } break; case 11: {
        assert(positionOfMax(z, -1) == -1);
            } break; case 12: {
        assert(positionOfMax(z, 0) == -1);
            } break; case 13: {
        assert(positionOfMax(a, 1) == 0);
            } break; case 14: {
        assert(positionOfMax(a, 3) == 2);
            } break; case 15: {
        assert(positionOfMax(a, 6) == 2);
            } break; case 16: {
        assert(positionOfMax(a+3, 3) == 0);
            } break; case 17: {
        a[0] = "";
        a[1] = " ";
        a[2] = "";
        assert(positionOfMax(a, 3) == 1);
            } break; case 18: {
        assert(rotateLeft(z, -1, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 19: {
        assert(rotateLeft(a, 6, -1) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 20: {
        assert(rotateLeft(a, 6, 6) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 21: {
        assert(rotateLeft(z, 0, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 22: {
        assert(rotateLeft(a, 1, 0) == 0 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 23: {
        assert(rotateLeft(a, 6, 0) == 0 &&
            a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
            } break; case 24: {
        assert(rotateLeft(a, 6, 5) == 5 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 25: {
        assert(rotateLeft(a, 6, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
            } break; case 26: {
        assert(rotateLeft(a, 5, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
            } break; case 27: {
        assert(countRuns(z, -1) == -1);
            } break; case 28: {
        assert(countRuns(z, 0) == 0);
            } break; case 29: {
        assert(countRuns(a, 1) == 1);
            } break; case 30: {
        assert(countRuns(a, 3) == 3);
            } break; case 31: {
        assert(countRuns(a, 4) == 3);
            } break; case 32: {
        assert(countRuns(a+2, 4) == 3);
            } break; case 33: {
        assert(countRuns(d, 9) == 5);
            } break; case 34: {
        assert(flip(z, -1) == -1 && a[0] == "alpha");
            } break; case 35: {
        assert(flip(z, 0) == 0 && a[0] == "alpha");
            } break; case 36: {
        assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                    a[1] == "beta");
            } break; case 37: {
        assert(flip(a, 2) == 2 && a[0] == "beta" &&
                    a[1] == "alpha" && a[2] == "gamma");
            } break; case 38: {
        assert(flip(a, 5) == 5 && a[0] == "beta" &&
            a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
            a[4] == "alpha" && a[5] == "delta");
            } break; case 39: {
        a[2] = "zeta";
        assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
            a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
            a[5] == "alpha");
            } break; case 40: {
        assert(differ(z, -1, b, 6) == -1);
            } break; case 41: {
        assert(differ(a, 6, z, -1) == -1);
            } break; case 42: {
        assert(differ(z, 0, b, 0) == 0);
            } break; case 43: {
        assert(differ(a, 3, b, 3) == 3);
            } break; case 44: {
        assert(differ(a, 3, b, 2) == 2);
            } break; case 45: {
        assert(differ(a, 2, b, 3) == 2);
            } break; case 46: {
        assert(differ(a, 6, b, 6) == 3);
            } break; case 47: {
        assert(subsequence(z, -1, b, 6) == -1);
            } break; case 48: {
        assert(subsequence(a, 6, z, -1) == -1);
            } break; case 49: {
        assert(subsequence(z, 0, b, 6) == -1);
            } break; case 50: {
        assert(subsequence(a, 6, z, 0) == 0);
            } break; case 51: {
        assert(subsequence(a, 6, b, 1) == 0);
            } break; case 52: {
        assert(subsequence(a, 6, b+4, 2) == 4);
            } break; case 53: {
        assert(subsequence(a, 6, b+3, 1) == 5);
            } break; case 54: {
        assert(subsequence(a, 6, b+3, 2) == -1);
            } break; case 55: {
        assert(subsequence(a, 6, b+2, 2) == -1);
            } break; case 56: {
        assert(subsequence(a, 6, a, 6) == 0);
            } break; case 57: {
        assert(lookupAny(a, 6, z, -1) == -1);
            } break; case 58: {
        assert(lookupAny(z, -1, b, 6) == -1);
            } break; case 59: {
        assert(lookupAny(z, 0, b, 1) == -1);
            } break; case 60: {
        assert(lookupAny(a, 6, z, 0) == -1);
            } break; case 61: {
        assert(lookupAny(a, 1, b, 1) == 0);
            } break; case 62: {
        assert(lookupAny(a, 6, b+3, 3) == 1);
            } break; case 63: {
        assert(lookupAny(a, 4, b+3, 3) == 1);
            } break; case 64: {
        assert(lookupAny(a, 2, b+2, 2) == -1);
            } break; case 65: {
        assert(separate(z, -1, "beta") == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 66: {
        assert(separate(z, 0, "beta") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 67: {
        assert(separate(a, 1, "aaa") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 68: {
        assert(separate(a, 1, "alpha") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 69: {
        assert(separate(a, 1, "zeta") == 1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 70: {
        assert(separate(a, 2, "aaa") == 0 &&
            separatecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 71: {
        assert(separate(a, 2, "alpha") == 0 &&
            separatecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 72: {
        assert(separate(a, 2, "beta") == 1 &&
            separatecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 73: {
        assert(separate(a, 2, "zeta") == 2 &&
            separatecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 74: {
        assert(separate(a, 6, "aaa") == 0 && separatecheck(a, 6, 0, "aaa"));
            } break; case 75: {
        assert(separate(a, 6, "alpha") == 0 &&
            separatecheck(a, 6, 0, "alpha"));
            } break; case 76: {
        assert(separate(a, 6, "beta") == 1 &&
            separatecheck(a, 6, 1, "beta"));
            } break; case 77: {
        assert(separate(a, 6, "delta") == 3 &&
            separatecheck(a, 6, 3, "delta"));
            } break; case 78: {
        assert(separate(a, 6, "gamma") == 4 &&
            separatecheck(a, 6, 4, "gamma"));
            } break; case 79: {
        assert(separate(a, 6, "zeta") == 6 &&
            separatecheck(a, 6, 6, "zeta"));
            } break; case 80: {
        a[2] = "mu";
        c[5] = "mu";
        assert(separate(a, 6, "mu") == 5 && separatecheck(a, 6, 5, "mu"));
            } break; case 81: {
        assert(separate(a, 6, "chi") == 3 && separatecheck(a, 6, 3, "chi"));
            } break; case 82: {
          // To earn the bonus point for rotateLeft, this and all other
          // rotateLeft tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[BIG-2] = "gamma";
        h[BIG-1] = "delta";
        rotateLeft(h, BIG, 0);
        assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
            } break; case 83: {
          // To earn the bonus point for flip, this and all other
          // flip tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[0] = "gamma";
        h[BIG-1] = "delta";
        flip(h, BIG);
        assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
            } break; case 84: {
          // To earn the bonus point for separate, this and all other
          // separate tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        string i[3] = { "alpha", "beta", "gamma" };
        for (int k = 0; k < BIG; k++)
            h[k] = i[k % 3];
        separate(h, BIG, "beta");
        int m = 0;
        for (m = 0; m < (BIG+2)/3; m++)
            assert(h[m] == "alpha");
        for ( ; m < (BIG+1)/3; m++)
            assert(h[m] == "beta");
        for ( ; m < BIG/3; m++)
            assert(h[m] == "gamma");
            } break;
    }

    new (&a[-1]) string;
    new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 84): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 84)
    {
    cout << "Bad test number" << endl;
    return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}
