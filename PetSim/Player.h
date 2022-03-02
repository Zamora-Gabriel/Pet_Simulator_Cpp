#pragma once

#define NOMINMAX

#include <iostream>
#include <string>
#include <windows.h>
#include "Egg.h"
#include "Pet.h"


//text Color values for changing
enum TEXT_COLOR_PLAY {
    PLGREEN = 10,
    PLCYAN,
    PLRED,
    PLMAGENTA,
    PLYELLOW,
    PLWHITE,
};

//windows.h handler get standard output device as it manages screen buffer, in this case only for text color changing
HANDLE playConsole = GetStdHandle(STD_OUTPUT_HANDLE);


class Player
{
    
private:
    /*Variables*/
    std::string Name;

    /*Private Methods*/
    bool ChooseAction(Pet* p)
    {
        int op = 0;

        std::cout << " What would you like to do with your pet? \n (Choose an option) \n";

        std::cout << "1 - Feed! \n";
        //Variable Results
        std::cout << "2 - Compete in race! \n";

        std::cout << "3 - Rest! \n";

        std::cout << "4 - Walk! \n";

        std::cout << "5 - Send to a party! \n";

        //Check user's input
        std::cin >> op;

        if (!std::cin || op > 5 || op < 1) {
            //user's input isn't a number (or is an incorrect value). Reset failbit
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Typed an unrecognized symbol, please type a valid number" << "\n \n";
            //Return error as true
            return true;
        }

        //Check until a valid option was selected
        switch (op)
        {
        case 1:
            if (Money < 10)
            {
                std::cout << "Your actual balance is $" << Money << " and food costs $10... You can't buy food!";
                //Return error as true
                return true;
            }
            else
            {
                Money = p->Eat(Money);
                return false;
            }
        case 2:
            p->CompeteRace();
            return false;
        case 3:
            p->Rest();
            return false;
        case 4:
            p->Walk();
            return false;
        case 5:
            Money = p->SendParty(Money);
            return false;
        default:
            std::cout << "Error: " << p->Name << " is confused, Please type a valid option \n";
            return true;
        }
    }

    //Variables
public:
    int Money;
    int petcount;

    /*Getters for privates*/
    std::string GetName() {
        return Name;
    }


    //Constructor
    Player()
    {
        //Starting money
        Name = " ";
        Money = 20;
        petcount = 0;
    }

    //Destructor
    ~Player()
    {

    }

    /*Public Methods*/
    bool YourName(bool done)
    {
        //Asks for user's name if hasn't asked before
        while (!done)
        {
            //Change text color to white
            SetConsoleTextAttribute(playConsole, PLWHITE);

            std::cout << "Welcome to Pinata Island! Please type your name: " << "\n";
            std::cin.ignore();
            std::getline(std::cin, Name);

            std::cout << "So... your name is " << Name << ". Is that right? (Type yes or y if it is correct)" << "\n \n";
            std::string option;
            std::cin >> option;

            if (option == "y" || option == "yes" || option == "Y" || option == "Yes")
            {
                std::cout << "Well " << Name << ", It is time for you to meet your new partner" << "\n \n";
                return true;
            }
        }
        return true;
    }

    void ChooseEgg(Egg* myEgg)
    {
        bool error = false;
        int option = 0;
        std::cout << "Please select the color of the egg you would like: " << "\n";

        //Change text color to white
        SetConsoleTextAttribute(playConsole, PLWHITE);
        std::cout << "1 - White" << "\n";

        //Change text color to white
        SetConsoleTextAttribute(playConsole, PLRED);
        std::cout << "2 - Red" << "\n";

        //Change text color to cyan
        SetConsoleTextAttribute(playConsole, PLCYAN);
        std::cout << "3 - Blue" << "\n";

        //Change text color to Green
        SetConsoleTextAttribute(playConsole, PLGREEN);
        std::cout << "4 - Green" << "\n";

        //Change text color to yellow
        SetConsoleTextAttribute(playConsole, PLYELLOW);
        std::cout << "5 - Yellow" << "\n\n";

        //Cycle until a valid option is typed
        do
        {
            //Check user's input
            std::cin >> option;

            if (!std::cin || option > 5 || option < 1) {
                //user's input isn't a number (or is an incorrect value). Reset failbit
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Typed an unrecognized symbol, please type a valid number" << "\n \n";
                error = true;
            }
            else {
                error = false;
            }
        } while (error == true);

        //call hatch function
        myEgg->Hatch(option);
    }

    void PetNaming(Pet* p)
    {
        //Pet naming
        std::cout << "Please choose a name for your new " << p->GetSpecies() << " buddy: " << "\n"; 
        std::cin.ignore();
        std::getline(std::cin, p->Name);
        std::cout << "Your pet's name is:" << p->Name << "\n\n";
    }

    //Do something ith pet
    void Action(Pet* mascot, int daytime)
    {
        bool err = false;
        std::string MsgMorning = "\n Time to get up! ";
        std::string MsgEvening = "\n Now is evening, ";


        do
        {
            //Morning
            if (daytime == 0)
            {
                std::cout << MsgMorning << "\n\n";
            }
            //Evening
            else
            {
                std::cout << MsgEvening << "\n\n";
            }

            //if pet is tired tired - 20 and jump the action
            if (mascot->Tired >= 80)
            {
                std::cout << "Wait... " << mascot->Name << " seems exhausted... Let it rest a while \n\n";
                mascot->Tired -= 20;
                break;
            }

            err = ChooseAction(mascot);

        } while (err);
    }



    
};