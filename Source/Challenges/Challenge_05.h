#pragma once

#include "Common/Challenge.h"

#include <set>

class CChallenge_05 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    int ComputeSeatID(const std::string& _boardingPass);

    static std::string const sm_inputFilePath;

    std::vector<std::string> m_BoardingPasses;
    std::set<int> m_SeatIDs;

    static const int sm_RowCount;
    static const int sm_ColCount;
};
