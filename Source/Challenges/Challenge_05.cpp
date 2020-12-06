#include "Challenge_05.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_05::sm_inputFilePath = "Inputs/Input_Challenge_05.txt";
int const CChallenge_05::sm_RowCount = 128;
int const CChallenge_05::sm_ColCount = 8;

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.005917 s
  Execution :  0.002339 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.008025 s
  Execution :  0.00203 s
  Clean Up  :  0 s
<=========================>
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_BoardingPasses);;
}

EErrorCode CChallenge_05::Run_FirstPart()
{
    int highestSeatID = 0;
    for (const std::string& boardingPass : m_BoardingPasses)
    {
        highestSeatID = std::max(highestSeatID, ComputeSeatID(boardingPass));
    }

    std::cout << "Done ! Highest seat ID is : " << highestSeatID << "." << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_BoardingPasses);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (const std::string& boardingPass : m_BoardingPasses)
    {
        m_SeatIDs.insert(ComputeSeatID(boardingPass));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_05::Run_SecondPart()
{
    if (m_SeatIDs.size() < 2)
        return EErrorCode::Failure;

    int mySeatID = 0;

    std::set<int>::iterator previousIt = m_SeatIDs.begin();
    std::set<int>::iterator it = m_SeatIDs.begin();
    ++it;
    while (it != m_SeatIDs.end())
    {
        if (DEBUG_LOGS)
        {
            std::cout << "Previous : " << *previousIt << " - Current : " << *it << std::endl;
        }

        if (*previousIt + 1 != *it)
        {
            mySeatID = *previousIt + 1;
            break;
        }

        previousIt = it++;
    }

    std::cout << "Done ! Your ID is " << mySeatID << "." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



int CChallenge_05::ComputeSeatID(const std::string& _boardingPass)
{
    int currentRow = 0;
    int rowCount = sm_RowCount;
    int currentCol = 0;
    int colCount = sm_ColCount;

    for (const char& c : _boardingPass)
    {
        switch (c)
        {
        case 'F':
            rowCount /= 2;
            break;
        case 'B':
            rowCount /= 2;
            currentRow += rowCount;
            break;
        case 'L':
            colCount /= 2;
            break;
        case 'R':
            colCount /= 2;
            currentCol += colCount;
            break;
        default:
            break;
        }
    }

    return currentRow * 8 + currentCol;
}