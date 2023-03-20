#include <iostream>
#include <limits>
#include "time.h"
#include "DATE.H"
#include "Windlog.h"


void printMenu()
{
    /// Menu information
    std::cout <<"\n===================================================================="<< std::endl;
    std::cout <<"========================ICT 283 Assignment 2========================"<< std::endl;
    std::cout <<"===================================================================="<< std::endl << std::endl;
    std::cout <<"=============================== MENU ==============================="<< std::endl << std::endl;
    std::cout <<"= 1. Average and sample standard deviation of wind speed.          ="<< std::endl << std::endl;
    std::cout <<"= 2. Average and staple standard deviation of ambient temperature. ="<< std::endl << std::endl;
    std::cout <<"= 3. Total solar radiation in kWh/m2.                              ="<< std::endl << std::endl;
    std::cout <<"= 4. Display all data and write to data/WindTempSolar.csv.         ="<< std::endl << std::endl;
    std::cout <<"= 5. Reload file                                                   ="<< std::endl << std::endl;
    std::cout <<"= 6. Exit.                                                         ="<< std::endl << std::endl;
    std::cout <<"===================================================================="<< std::endl;
}

int main()
{
    windlog wl;
    wl.readFiles("data/met_index.txt");


    bool menuLoop = true;
    int ans = 0;

    do
    {
        /// MENU LOOP
        printMenu();
        std::cout << "\n Enter: ";
        std::cin >> ans;

        if(std::cin.fail())
        {
            /// User input validation check, only enter 1 - 6.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ans = 99;
        }
        std::cout << std::endl;
        switch(ans)
        {
        case 1:
            wl.findMonthSpeed();
            break;
        case 2:
            wl.findYearTemperature();
            break;
        case 3:
            wl.findYearSolar();
            break;
        case 4:
            wl.printToFile();
            break;
        case 5:
            wl.reload();
            break;
        case 6:
            std::cout << "\nThanks for using it.\n";
            return 0;
        default:
            std::cout << "\nPlease enter only numbers (1-6)\n\n";
        }
    }
    while(menuLoop);

    return 0;

}
