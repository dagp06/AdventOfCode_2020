#pragma once

#include "Common/Challenge.h"

class CChallenge_03 : public CChallenge
{
private:
    struct Slope
    {
        Slope(int _x, int _y) : m_X(_x), m_Y(_y) {};
        int m_X = 0;
        int m_Y = 0;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;
    static char const sm_treeSymbol;


    std::vector<std::string> m_Lines;
    std::vector<Slope> m_Slopes;
};
