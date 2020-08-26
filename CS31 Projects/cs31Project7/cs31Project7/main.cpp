//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class Pet
//{
//  public:
//    Pet(string nm, int initialHealth);
//    void eat(int amt);
//    void play();
//    string name() const;
//    int health() const;
//    bool alive() const;
//  private:
//    string m_name;
//    int m_health;
//
//};
//
//  // Initialize the state of the pet
//Pet::Pet(string nm, int initialHealth)
//{
//    m_name = nm;
//    m_health = initialHealth;
//}
//
//void Pet::eat(int amt)
//{
//    m_health += amt;
//}
//
//void Pet::play()
//{
//    m_health -= 1;
//}
//
//string Pet::name() const
//{
//    return m_name;
//}
//
//int Pet::health() const
//{
//    return m_health;
//}
//
//bool Pet::alive() const
//{
//    return m_health > 0;
//}
//
///////////
//// Do not change any code below this point
///////////
//
//void reportStatus(const Pet* p)
//{
//    cout << p->name() << " has health level " << p->health();
//    if ( ! p->alive())
//        cout << ", so has died";
//    cout << endl;
//}
//
//void careFor(Pet* p, int d)
//{
//    if ( ! p->alive())
//    {
//        cout << p->name() << " is still dead" << endl;
//        return;
//    }
//
//      // Every third day, you forget to feed your pet
//    if (d % 3 == 0)
//        cout << "You forgot to feed " << p->name() << endl;
//    else
//    {
//        p->eat(1);  // Feed the pet one unit of food
//        cout << "You fed " << p->name() << endl;
//    }
//
//    p->play();
//    reportStatus(p);
//}
//
//int main()
//{
//    Pet* myPets[2];
//    myPets[0] = new Pet("Fluffy", 2);
//    myPets[1] = new Pet("Frisky", 4);
//    for (int day = 1; day <= 9; day++)
//    {
//        cout << "======= Day " << day << endl;
//        for (int k = 0; k < 2; k++)
//            careFor(myPets[k], day);
//    }
//    cout << "=======" << endl;
//    for (int k = 0; k < 2; k++)
//    {
//        if (myPets[k]->alive())
//            cout << "Animal Control has come to rescue "
//                 << myPets[k]->name() << endl;
//        delete myPets[k];
//    }
//}

//#include <iostream>
//
//using namespace std;
//
//int pointerSum(int* a, int n)
//{
//    int sum = 0;
//    for (int* i = a; i < a + n; i++)
//        sum += *i;
//    return sum;
//}
//
//int main()
//{
//    int arr[7] = {1, 1, 1, 3};
//    cout << pointerSum(arr, 4) << endl;
//}

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//bool is_alternation(char* startOfWord, char* endOfWord) {
//    while (startOfWord != endOfWord - 2)
//    {
//        if (*startOfWord != *(startOfWord + 2))
//            return false;
//        startOfWord++;
//    }
//    return true;
//}
//
//int main()
//{
//    char word[10] = "cabababab";
//    cout << is_alternation(word, &word[8]) << endl;
//}

//void arraySort(int arr[], int nElements)
//{
//    int countMoved = 0;
//    for (int i = 0; i < nElements; i++)
//    {
//        if (arr[i] % 2 == 0)
//        {
//            int temp = arr[countMoved];
//            arr[countMoved] = arr[i];
//            arr[i] = temp;
//            countMoved++;
//        }
//    }
//}
//
//int main()
//{
//    int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    arraySort(nums, 10);
//    for (int i = 0; i < 10; i++)
//        cout << nums[i] << " ";
//    cout << endl;
//}

//bool isPermutation(string str1, string str2)
//{
//    if (str1.size() != str2.size())
//        return false;
//    bool isFound = false;
//    for (int i = 0; i < str1.size(); i++) {
//        isFound = false;
//        for (int j = 0; j < str2.size(); j++) {
//            if (str1[i] == str2[j]) {
//                isFound = true;
//                str2[j] = ' ';
//            }
//        }
//        if (!isFound)
//            return false;
//    }
//    return true;
//}
//
//int main()
//{
//    string str1 = "flog";
//    string str2 = "golf";
//
//    if (isPermutation(str1, str2))
//        cout << "true" << endl;
//    else
//        cout << "false" << endl;
//}
//
//void reverse(char* arr) {
//    for (int i = 0; i < strlen(arr) / 2; i++)
//    {
//        char temp = *(arr + i);
//        *(arr + i) = *(arr + strlen(arr) - 1 - i);
//        *(arr + strlen(arr) - 1 - i) = temp;
//    }
//}
//
//int main()
//{
//    char arr1[6] = "hello"; reverse(arr1);
//    // now arr1 should be "olleh"
//    cout << arr1 << endl;
//    char arr2[5] = "ucla"; reverse(arr2);
//    // now arr2 should be "alcu"
//    cout << arr2 << endl;
//    char arr3[6] = "kayak"; reverse(arr3);
//    // now arr3 should be "kayak"
//    cout << arr3 << endl;
//}
//
//void descSort(int* nums, int len)
//{
//    int temp = 0;
//    int max = 0;
//    for (int i = 0; i < len; i++)
//    {
//        if (*(nums + i) >= max) {
//            temp = *(nums + i);
//            for (int j = i - 1; j > 0; j--)
//                *(nums + j) = *(nums + j - 1);
//            *nums = temp;
//            max = temp;
//        }
//    }
//}
//
//int main()
//{
//    int a[10] = {3, 1, 4, 0, -1, 2, 3, 4, 1, 2}; descSort(a, 10);
//    //a = {4, 4, 3, 3, 2, 2, 1, 1, 0, -1};
//    for (int i = 0; i < 10; i++)
//        cout << a[i] << " ";
//    cout << endl;
//}

//void sum(int* list1, int list1_size, int* list2, int list2_size)
//{
//    int num1 = 0;
//    int num2 = 0;
//    int multiplier = 1;
//    for (int i = list1_size - 1; i >= 0; i--)
//    {
//        num1 += *(list1 + i) * multiplier;
//        multiplier *= 10;
//    }
//    multiplier = 1;
//    for (int i = list2_size - 1; i >= 0; i--)
//    {
//        num2 += *(list2 + i) * multiplier;
//        multiplier *= 10;
//    }
//    cout << num1 + num2 << endl;
//}
//
//int main()
//{
//    int list1[] = { 8, 5, 3, 1 };
//    int list2[] = { 5, 3, 2, 9 };
//    sum(list1, 4, list2, 4);
//    // prints 13860, the sum of 8531 and 5329
//    int list3[] = {5,3,1};
//    int list4[] = { 5, 3, 2, 9 };
//    sum(list3, 3, list4, 4);
//    // prints 5860, the sum of 531 and 5329
//
//}

void rotate(int* arr, int n)
{
    if (n < 0)
        n *= -1;
    while (n > 0)
    {
        int temp = *(arr + 5);
        for (int i = 5; i > 0; i--)
            *(arr + i) = *(arr + i - 1);
        *arr = temp;
        n--;
    }
}

void printArray(int* a)
{
    for (int i = 0; i < 6; i++)
        cout << *(a + i) << " ";
    cout << endl;
}

int main()
{
    int a[6] = {1,2,3,4,5,6};
    int b[6] = {1,2,3,4,5,6};
    int c[6] = {1,2,3,4,5,6};
    rotate(a, 4); // now a = {3,4,5,6,1,2};
    rotate(b,-1); //nowb={2,3,4,5,6,1};
    rotate(c, 8); // now c = {5,6,1,2,3,4};
    printArray(a);
    printArray(b);
    printArray(c);
    
    
}
