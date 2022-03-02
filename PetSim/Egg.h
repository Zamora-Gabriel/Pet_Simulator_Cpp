#pragma once
#include <iostream>
#include <string>

class Egg
{
public:
    //Getters and setters
    std::string Color;
    //the rank of the pet: Greater rank, greater difficulty for taking care
    int Rank; 
    std::string hatchSpecie;
    std::string Candy; 
    std::string RealSp; 

        //Constructor
    Egg()
    {
        Color = "white";
        Rank = 1;
    }

    ~Egg() {

    }

    void Hatch(int colorOp)
    {
        //Generate a random roll for pet rank
        srand((unsigned)time(0));
        Rank = (rand() % 2) + 1;

        switch (colorOp)
        {
            case 1:
                //White Egg
                
                if (Rank == 1)
                {
                    hatchSpecie = "Swanana";
                    RealSp = "Swan";
                    Candy = "Banana";
                    return;
                }
                Color = "white";
                hatchSpecie = "Moozipan";
                RealSp = "Cow";
                Candy = "Marzipan";

                return;

            case 2:
                //Red egg

                if (Rank == 1)
                {
                    hatchSpecie = "Raisant";
                    RealSp = "Ant";
                    Candy = "Raisin";
                    return;
                }
                Color = "red";
                hatchSpecie = "Pieena";
                RealSp = "Hyena";
                Candy = "Pie";

                return;
            case 3:
                //Blue egg

                if (Rank == 1)
                {
                    hatchSpecie = "Sherbat";
                    RealSp = "Bat";
                    Candy = "Sherbet";
                    return;
                }
                Color = "blue";
                hatchSpecie = "Horstachio";
                RealSp = "Horse";
                Candy = "Pistachio";

                return;

            case 4:
                //Green Egg

                if (Rank == 1)
                {
                    hatchSpecie = "Fudgehog";
                    RealSp = "Hedgehog";
                    Candy = "Fudge";
                    return;
                }
                Color = "green";
                hatchSpecie = "Jameleon";
                RealSp = "Chameleon";
                Candy = "Jam";

                return;

            case 5:
                //Yellow egg

                if (Rank == 1)
                {
                    hatchSpecie = "S'morepion";
                    RealSp = "Scorpion";
                    Candy = "S'more";
                    return;
                }
                Color = "yellow";
                hatchSpecie = "Roario";
                RealSp = "Lion";
                Candy = "Oreo";

                return;
                //Since option was already validated, default status may never be accessed
            default:
                Color = "white";
                hatchSpecie = "Swanana";
                RealSp = "Swan";
                Candy = "Banana";
                return;
        }
    }
};

