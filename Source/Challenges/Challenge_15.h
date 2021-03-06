#pragma once

#include "Common/Challenge.h"

#include <map>

using namespace std;

class CChallenge_15 : public CChallenge
{
private:
    typedef pair<long long, long long> LastOccurences;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    long long FindNthSpokenNumber(long long _n);

    static string const sm_inputFilePath;

    vector<int> m_StartingNumbers;
    map<long long, LastOccurences> m_SpokenNumbers;
};
