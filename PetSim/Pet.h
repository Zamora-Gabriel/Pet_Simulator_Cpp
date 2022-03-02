#pragma once
#include <iostream>
#include <string>
#include <windows.h>

//text Color values for changing
enum TEXT_COLOR_PET {
    PETGREEN = 10,
    PETCYAN,
    PETRED,
    PETMAGENTA,
    PETYELLOW,
    PETWHITE,
};

//windows.h handler get standard output device as it manages screen buffer, in this case only for text color changing
HANDLE petConsole = GetStdHandle(STD_OUTPUT_HANDLE);


class Pet
{
private:
    //private "difficulty" level of the pet. Negative statuses are multiplied by rank
    int Rank;
    std::string PetConclusion;
    std::string Species; //{ get; private set; }

    //Pet private set statusses
    int Hunger; // { get; private set; }
    int Sickness; //{ get; private set; }
    int Happiness; //{ get; private set; }
    int Popularity; //{ get; private set; }


    //Inspired data for the pinata species on the game
    std::string RealSpecie;
    std::string InspiredCandy;

    /*Private Methods*/

    //Set statusses in negative numbers to zero
    void NegativesToZero()
    {
        if (Hunger < 0)
        {
            Hunger = 0;
        }

        if (Tired < 0)
        {
            Tired = 0;
        }

        if (Sickness < 0)
        {
            Sickness = 0;
        }

        if (Popularity < 0)
        {
            Popularity = 0;
        }
    }

    //Check every critical status
    bool CheckHunger(std::string plaName, bool alive)
    {
        //Check hunger level of the pet, if greater than 100, pet dies

        //First Check if the pet is alive
        if (alive)
        {
            if (Hunger >= 80)
            {
                if (Hunger >= 100)
                {
                    std::cout << plaName << " I... can't... too hungry..." << "\n";

                    //Narration
                    SetConsoleTextAttribute(petConsole, PETWHITE);
                    std::cout << Name << " died at day " << DaysAlive << " by hunger" << "\n";

                    PetConclusion = "Died by hunger";
                    return false;
                }

                std::cout << "I-I'm starving" << "\n";
                return true;
            }
        }

        return alive;
    }

    bool CheckSickness(std::string plaName, bool alive)
    {
        //Check sickness level of the pet, if greater than 100, pet dies

        //First Check if the pet is alive
        if (alive)
        {
            if (Sickness >= 80)
            {
                if (Sickness >= 100)
                {
                    std::cout << plaName << ", I don't want to go... I don't want to..." << "\n";

                    //Narration
                    SetConsoleTextAttribute(petConsole, PETWHITE);
                    std::cout << Name << " died at day " << DaysAlive << " by Sickness" << "\n";

                    PetConclusion = "Died by sickness";
                    return false;
                }

                std::cout << plaName << ", I don't feel so good..." << "\n";
                return true;
            }
        }

        return alive;
    }

    bool CheckHappiness(std::string plaName, bool alive)
    {
        //Check happiness of the pet, if it is lower than 0, pet rans away

        //First Check if the pet is alive
        if (alive)
        {
            if (Happiness <= 20)
            {
                if (Happiness <= 0)
                {
                    std::cout << plaName << ", I'm leaving I can't take this anymore!" << "\n";

                    //Narration
                    SetConsoleTextAttribute(petConsole, PETWHITE);
                    std::cout << Name << " ran away at day " << DaysAlive << "\n";

                    PetConclusion = "Ran away";
                    return false;
                }

                std::cout << plaName << ", I think I'm just a money making machine for you..." << "\n";
                return true;
            }
        }
        return alive;
    }

    bool CheckOld(std::string plaName, bool alive)
    {
        //Check if pet is not old enough

        //First Check if the pet is alive
        if (alive)
        {
            //Pinatas live until 5 days past
            if (DaysAlive >= 5)
            {
                std::cout << "I-I had a great life, thank you... " << plaName << "\n";

                //Narration
                SetConsoleTextAttribute(petConsole, PETWHITE);
                std::cout << plaName << " lived a good life, sadly passed away at day " << DaysAlive << "\n";

                PetConclusion = "Lived a good life";
                return false;
            }
        }
        return alive;
    }

public:
    std::string Name;

    int DaysAlive;


    //Tired status
    int Tired;

    //Constructors
    Pet()
    {
        Name = "None";
        Species = "None";
        Rank = 1;
        DaysAlive = 0;
        Hunger = 0;
        Tired = 0;
        Sickness = 0;
        Happiness = 50;
        Popularity = 0;
        RealSpecie = "None";
        InspiredCandy = "None";
    }


    Pet(std::string spec, int rank, std::string realSp, std::string candy)
    {
        Name = "None";
        Species = spec;
        Rank = rank;
        DaysAlive = 0;
        Hunger = 0;
        Tired = 0;
        Sickness = 0;
        Happiness = 50;
        Popularity = 0;
        RealSpecie = realSp;
        InspiredCandy = candy;
    }

    //Getters for private
    std::string GetSpecies() {
        //public get, private set
        return Species;
    }

    //Get status
    void PetStatus()
    {
        std::cout<< Name << ": \n";
        std::cout<<"Species: "<< Species << "\n";
        std::cout<<"Rank: "<< Rank << "\n\n";

        std::cout<< Name << "'s Status: \n";
        std::cout<<"Days: " << DaysAlive << "\n";
        std::cout<<"Hunger: "<< Hunger << "\n";
        std::cout<<"Exhaustion: " << Tired << "\n";
        std::cout<<"Sickness: " << Sickness << "\n";
        std::cout<<"Happiness:  " << Happiness << "\n";
        std::cout<<"Popularity: " << Popularity << "\n\n";
    }

    /*Methods*/

    //Pets status and message, returns bool if it is or not alive
    bool StatusMsgAlive(std::string plaName)
    {
        bool alive = true;

        //Check if pet is alive or hasn't run away
        alive = CheckHappiness(plaName, alive);
        alive = CheckHunger(plaName, alive);
        alive = CheckSickness(plaName, alive);
        alive = CheckOld(plaName, alive);

        if (alive)
        {
            std::cout<<"A day full of surprises awaits us!" << "\n\n";
        }

        return alive;
    }

    //Feed the pet: Increase Sickness and Happiness. Decrease Hunger and Money
    int Eat(int mon)
    {
        //Check if has the money to buy food
        Hunger -= 10;
        Sickness += 20;
        Happiness += 10;
        mon -= 10;
        NegativesToZero();

        //Pet dialog, Change text color to cyan
        SetConsoleTextAttribute(petConsole, PETCYAN);
        std::cout<<"Thanks for the treat!" << "\n";
        //return to narrator color
        SetConsoleTextAttribute(petConsole, PETWHITE);

        return mon;
    }

    //Go to a competition with the pet. "Play"
    void CompeteRace()
    {
        std::cout<<"Welcome to the Pinata Grand Race! Let's see which would be the victor!" << "\n";
        //Generate a random roll for place
        srand((unsigned)time(0));
        int place = (rand() % 3) + 1;
        std::cout<< Name << " arrived in " << place << " place!" << "\n";

        //Check place of the race and increase or decrease parameters with that information
        switch (place)
        {
            //First place
        case 1:
            Popularity += 20 * Rank;
            Happiness += 20 * Rank;
            Tired += 20 * Rank;
            Hunger += 10 * Rank;

            //Pet dialog, Change text color to cyan
            SetConsoleTextAttribute(petConsole, PETCYAN);
            std::cout << "Yes! I've won!" << "\n";
            //return to narrator color
            SetConsoleTextAttribute(petConsole, PETWHITE);

            break;
            //Second place
        case 2:
            Popularity += 10 * Rank;
            Tired += 30 * Rank;
            Hunger += 10 * Rank;

            //Pet dialog, Change text color to cyan
            SetConsoleTextAttribute(petConsole, PETCYAN);
            std::cout<<"I was so close!" << "\n";
            //return to narrator color
            SetConsoleTextAttribute(petConsole, PETWHITE);

            break;
            //Third place
        default:
            Popularity -= 10 * Rank;
            Happiness -= 10 * Rank;
            Tired += 30 * Rank;
            Hunger += 20 * Rank;

            //Pet dialog, Change text color to cyan
            SetConsoleTextAttribute(petConsole, PETCYAN);
            std::cout<<"I'm sory boss, I failed you..." << "\n";
            //return to narrator color
            SetConsoleTextAttribute(petConsole, PETWHITE);
            break;
        }
        NegativesToZero();
    }

    //Leave the pet to rest: Increase Hunger. Decrease Sickness and Tired values. 
    void Rest()
    {
        Tired -= 10;
        Sickness -= 10;
        Hunger += 20;
        NegativesToZero();
        
        //Pet dialog, Change text color to cyan
        SetConsoleTextAttribute(petConsole, PETCYAN);

        std::cout<<"I'm feeling a bit refreshed, thanks for the break!" << "\n";
        //return to narrator color
        SetConsoleTextAttribute(petConsole, PETWHITE);
    }

    //Walk with pet: Increase Hunger, Tired and Happiness.
    void Walk()
    {
        Happiness += 20;
        Tired += 20 * Rank;
        Hunger += 20 * Rank;
        NegativesToZero();
        
        //Pet dialog, Change text color to cyan
        SetConsoleTextAttribute(petConsole, PETCYAN);

        std::cout<<"Going for a walk with my partner it certainly brings me to life!" << "\n";
        //return to narrator color
        SetConsoleTextAttribute(petConsole, PETWHITE);
    }

    //Send Pinata to party: Decrease Happiness. Increase Tired, Hunger, Popularity and Money
    int SendParty(int money)
    {
        Popularity += 20 * Rank;
        Happiness -= 20;
        Tired += 20 * Rank;
        Hunger += 20;
        money += 20;
        NegativesToZero();

        //Pet dialog, Change text color to cyan
        SetConsoleTextAttribute(petConsole, PETCYAN);
        
        std::cout<<"Another day, another pay. Parties are so stressfull for us pinatas" << "\n";
        //return to narrator color
        SetConsoleTextAttribute(petConsole, PETWHITE);

        return money;
    }

    //If pet died being old, popularity changes to gold
    int PopularityToMoney()
    {
        if (DaysAlive >= 5)
        {
            return Popularity;
        }
        return 0;
    }

    //Print final information
    void printInfo()
    {
        std::cout << Name << " \t\t ";
        std::cout <<Species << " \t\t ";
        std::cout << RealSpecie <<" \t\t ";
        std::cout << InspiredCandy <<" \t\t ";
        std::cout << PetConclusion <<" \t\t  \n";

    }


};

