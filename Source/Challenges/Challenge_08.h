#pragma once

#include "Common/Challenge.h"

using namespace std;

class CChallenge_08 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;

    void RunProgram(bool& _infiniteLoopFound, int& accumulator);
    bool ChangeOp(int opIndex);
    void RestoreOp();

    vector<string> m_LinesOfCode;
    pair<int, string> m_CachedOp;
};
