
#define NOMINMAX

#include <iostream>
#include <string>
#include <windows.h>
#include "Player.h"
#include "Pet.h"
#include "Egg.h"

//text Color values for changing
enum TEXT_COLOR {
    GREEN = 10,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE,
};

//windows.h handler get standard output device as it manages screen buffer, in this case only for text color changing
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Function to ask player if wants to keep playing with the actual values
static bool KeepPlaying(std::string Msg)
{
    std::cout << Msg;
    std::cout<<" Type Y if you want to play, else type anything: " << "\n";
    std::string option = "";
    std::cin >> option;

    if (!(option == "y" || option == "yes" || option == "Yes" || option == "Y"))
    {
        //The player doesn't want to play
        return false;
    }
    return true;
}

//Function to ask player if wants to start a new game
static bool PlayAgain()
{
    std::cout<<"Would you like to start a new game? (Type Y if you want to play, else type anything)" << "\n";
    std::string option = "";
    std::cin >> option;

    //Leave a line to separate text
    std::cout<<"\n\n";

    if (!(option == "y" || option == "yes" || option == "Yes" || option == "Y"))
    {
        //The player doesn't want to play
        return false;
    }
    return true;
}

//function to change text color
void DialogColor(int Colour)
{
    switch (Colour) {
    case 0:
        //Narrator Color dialog
        SetConsoleTextAttribute(hConsole, WHITE);
        return;
    case 1:
        //Pet color dialog
        SetConsoleTextAttribute(hConsole, CYAN);
        return;
    case 2:
        //Money displaying color
        SetConsoleTextAttribute(hConsole, YELLOW);
        return;
    default:
        return;
    }
}

int main()
{

    //Flag for player to start or continue playing
    bool play = true;

    //Instantiate player
    Player player1 = Player();

    //limit of pets per game
    const int petLimit = 5;

    //instantiate egg object
    Egg myEgg = Egg();

    //start pet array
    Pet petArr[petLimit];

    //Flag to determine if pet is still active (alive and hasn't run away)
    bool active = true;

    //Restart game
    bool reset = true;

    //Name flag, check if player has already a name
    bool namFlag = false;

    while (reset) {

        //Greet and ask user if he wants to play
        //Intro message in yellow
        DialogColor(2);
        std::cout << "Welcome to picturesque Pinata Island!\n in its many gardens all variety of pinatas live, dance, and dream \n";
        std::cout << "that one day they will be chosen by a human to find a partner and have \n a wonderful life \n";
        play = KeepPlaying("");
        
        //Restart flags
        reset = play;
        namFlag = false;
        

        while (play)
        {
            //Ask, user's name, if user's name already asked and approved, won't be asked 
            namFlag = player1.YourName(namFlag);

            //Ask the user for an input to choose the pet's egg
            player1.ChooseEgg(&myEgg);
            
            Pet pinata = Pet(myEgg.hatchSpecie, myEgg.Rank, myEgg.RealSp, myEgg.Candy);
            
            std::cout<<"Congratulations you got a: " << pinata.GetSpecies() << " pinata" << "\n\n";
            player1.PetNaming(&pinata);

            //While pinata hasn't died or ran away
            while (active)
            {
                //change color of console to money color (yellow)
                DialogColor(2); 

                //Print user's money
                std::cout<<"------------------------------------------------------------ \n";
                std::cout<<"\n Your actual money balance to buy food is: " << player1.Money << "\n";
                std::cout<<"------------------------------------------------------------ \n\n";

                //Color of console to narrator (white)
                DialogColor(0);

                //choose morning action (Pet, morning(0) or evening(any other number), money)
                player1.Action(&pinata, 0);
                //choose evening action
                player1.Action(&pinata, 1);

                //Showing pet status (Debug purposes)
                
                std::cout<<"\n Would you like to see " << pinata.Name <<" status? (Type y if yes, else type anything)" << "\n";
                std::string optionStatus;
                std::cin >> optionStatus;
                if (optionStatus == "y" || optionStatus == "yes" || optionStatus == "Y" || optionStatus == "Yes")
                {
                    pinata.PetStatus();
                }

                //Pet's response and status
                //pet dialog color (cyan)
                DialogColor(2);
                active = pinata.StatusMsgAlive(player1.GetName());
                player1.Money += pinata.PopularityToMoney();

                //Increase pet days
                pinata.DaysAlive++;
            }

            petArr[player1.petcount] = pinata;

            //Increase number of pets that user had
            player1.petcount++;

            if (player1.petcount < petLimit)
            {
                //Narrator color (white)
                DialogColor(0);
                //Ask user if he wants to keep playing
                play = KeepPlaying("Would you like to keep playing? ");
                
                //Division line for readability
                std::cout << "============================================" << "\n\n";
            }
            else
            {
                //Narrator color (white)
                DialogColor(0);
                //Game completed at maximum pets
                std::cout<<"\n Congratulations! You've already had "<< player1.petcount << " pets! Thank you for playing and please, come again!" << "\n\n";
                play = false;
            }

            //Set active flag to play with new pet
            active = true;
        }

        //Print all Pinatas information and conclusions

        std::cout<<"Name \t\t Specie \t\t Inspired Specie \t\t Inspired Candy \t\t Status" << "\n";

        for(Pet pet : petArr)
        {
            if (pet.Name == "None")
            {
                break;
            }

            //random colors per line
            srand((unsigned)time(0));
            int randColor = (rand() % 5) + 10;

            SetConsoleTextAttribute(hConsole, randColor);

            pet.printInfo();
        }

        //Player wants to start a new game
        reset = PlayAgain();
        if (reset)
        {
            //clear console for new game
            system("cls");
            std::cout << "New Game" << std::endl;
        }
    }

    std::cout<<"Thank you for playing!";
}

