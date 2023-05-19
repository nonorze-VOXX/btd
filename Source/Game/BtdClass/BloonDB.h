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
        void LoadRounds()
        {
            std::string delimiter = ",";
            std::ifstream fin("resources/bloon/round.csv");
            while (fin)
            {
                std::string s;
                getline(fin, s);
                size_t pos = 0;
                std::string token;
                std::string time;
                std::string num;
                vector<UnitRound> nextRound;
                while ((pos = s.find(delimiter)) != std::string::npos)
                {
                    token = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    
                    pos = s.find(delimiter);
                    time = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    
                    pos = s.find(delimiter);
                    num = s.substr(0, pos);
                    s.erase(0, pos + delimiter.length());
                    int loopTimes = stoi(num);
                    Layer nextLayer = Layer::red;
                    if (token == "red"||token=="r")
                        nextLayer = Layer::red;
                    if (token == "blue"||token=="b")
                        nextLayer = Layer::blue;
                    if (token == "green"||token =="g")
                        nextLayer = Layer::green;
                    if (token == "yellow"||token=="y")
                        nextLayer = Layer::yellow;
                    if (token == "black"||token=="bl")
                        nextLayer = Layer::black;
                    if (token == "white"||token=="w")
                        nextLayer = Layer::white;
                    for(int j=0;j<loopTimes;j++)
                    {
                        UnitRound nextBloon{};
                        nextBloon.nextTime = stoi(time);
                        nextBloon.type = nextLayer;
                        nextRound.push_back(nextBloon);
                    }
                }
                _roundses.push_back(nextRound);
            }
            fin.close();
        }
        vector<vector<UnitRound>> GetRounds()
        {
            return _roundses;
        }
        
    };
} // namespace Btd
