#pragma once

#include "Common/Challenge.h"

#include <map>

using namespace std;

class CChallenge_10 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;

    vector<int> m_AdapterJoltages;
    map<int, unsigned long long> m_CombinationsFromAdapters;
};
