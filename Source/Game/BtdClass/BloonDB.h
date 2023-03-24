#include <fstream>
#include <iostream>
#include <string>

#include "BtdUtil.h"

namespace Btd
{
    class BloonDB
    {
    private:
        vector<vector<UnitRound>> _roundses;

    public:
        void GetRoutes()
        {
            vector<UnitRound> nextRound;
            std::string delimiter = ",";
            std::ifstream fin("resources/bloon/round.csv");
            while (fin)
            {
                std::string s;
                getline(fin, s);
                size_t pos = 0;
                std::string token;
                std::string time;
                while ((pos = s.find(delimiter)) != std::string::npos)
                {
                    token = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    pos = s.find(delimiter);
                    time = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    UnitRound nextBloon;
                    nextBloon.nextTime = stoi(time);

                    if (token == "red")
                        nextBloon.type = Layer::red;
                    if (token == "blue")
                        nextBloon.type = Layer::blue;
                    if (token == "green")
                        nextBloon.type = Layer::green;
                    if (token == "yellow")
                        nextBloon.type = Layer::yellow;
                    if (token == "black")
                        nextBloon.type = Layer::black;
                    if (token == "white")
                        nextBloon.type = Layer::white;
                    nextRound.push_back(nextBloon);
                }
                _roundses.push_back(nextRound);
            }
            fin.close();
        }
    };
} // namespace Btd
