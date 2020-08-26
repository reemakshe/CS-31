//
// Reema Kshetramade
// SID: 205328402
// CS31 Project 2


#include <iostream>
#include <string>
using namespace std;

int main()
{
    //Get input of the defendant's name
    cout << "Defendant: ";
    string name;
    getline(cin, name);
    
    //Get input of amount paid
    cout << "Amount paid (in thousands): ";
    double amtPaid;
    cin >> amtPaid;
    //Remove the extra characters after reading a number
    cin.ignore(10000, '\n');
    
    //Get input of whether they were a fake athlete
    cout << "Fake athlete? (y/n): ";
    string isFake;
    getline(cin, isFake);
    
    //Declare variable to hold the amount of the fine
    double fine;
    
    //If the amount was less than or equal to 40000 it will be 20000 plus 0.66 of the amount paid
    if (amtPaid <= 40)
    {
        fine = 20.0 + (0.66 * amtPaid);
    }
    //If the amount was greater than 40000
    else
    {
        //Variable for the excess amount paid in the midrange of 40000 < amtPaid <= 250000
        double excessPaidMid = 0;
        //Variable for the excess amount paid in the range of amtPaid > 250000
        double excessPaidTop = 0;
        //Base amount for amtPaid > 40000
        double base = 20.0 + (0.66 * 40.0);
        
        //If amtPaid <= 250000, there is  excess payment in the midrange, but no excess in the top range
        if (amtPaid <= 250)
        {
            excessPaidMid = amtPaid - 40.0;
            excessPaidTop = 0;
        }
        //If amtPaid > 250000, the excess in the midrange is capped at 210000
        //The excess in the top range will be the portion of amtPaid greater than 250000
        else
        {
            excessPaidMid = 210;
            excessPaidTop = amtPaid - 250.0;
        }
        
        //If there is no athletic fakery, there is a lower percent for the mid range
        if (isFake == "n")
        {
            fine = base + (0.10 * excessPaidMid) + (0.14 * excessPaidTop);
        }
        //If there is athletic fakery, there is a higher percent for the mid range
        else
        {
            fine = base + (0.22 * excessPaidMid) + (0.14 * excessPaidTop);
        }
    }
    
    //Output three hyphens to separate the input from the calculated value
    cout << "---" << endl;
    
    //Output for if the name inputted in an empty string
    if (name == "")
    {
        cout << "You must enter a defendant name." << endl;
    }
    //Output for if the amount paid is entered as a negative number
    else if (amtPaid < 0)
    {
        cout << "The amount paid must not be negative." << endl;
    }
    //Output for if athletic fakery input is not either y or n
    else if (isFake != "y" && isFake != "n")
    {
        cout << "You must enter y or n." << endl;
    }
    //Output if all the conditions are met and the fine is calculated
    else
    {
        cout.setf(ios::fixed);
        cout.precision(1);
        cout << "The suggested fine for " << name << " is $" << fine << " thousand." << endl;
    }
    

    
}
