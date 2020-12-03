#include "Challenge_03.h"
#include "../Helpers/FileHelpers.h"

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_03::sm_inputFilePath = "Inputs/Input_Challenge_03.txt";
char const CChallenge_03::sm_treeSymbol = '#';

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000263 s
  Execution :  0.001833 s
  Clean Up  :  1.1e-05 s
---------------------------
PART 2 :
  Set Up    :  0.000246 s
  Execution :  0.002331 s
  Clean Up  :  1.5e-05 s
<=========================>
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_Slopes.push_back(Slope(3, 1));

    return m_Lines.size() > 0 ? EErrorCode::Success : EErrorCode::Failure;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_03::Run_FirstPart()
{
    if (m_Lines.empty() || m_Slopes.size() != 1)
    {
        std::cout << "ERROR : m_Lines is empty !" << std::endl;
        return EErrorCode::Failure;
    }

    int treeCount = 0;
    int row = 0;
    int col = 0;
    int rowSize = m_Lines[0].size();
    Slope slope = m_Slopes[0];
    while (row < m_Lines.size())
    {
        treeCount += m_Lines[row][col % rowSize] == sm_treeSymbol ? 1 : 0;

        col += slope.m_X;
        row += slope.m_Y;
    }

    std::cout << "There are " << treeCount << " on the slope (" << slope.m_X << ", " << slope.m_Y << ")." << std::endl;

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_03::CleanUp_FirstPart()
{
    m_Lines.clear();
    m_Slopes.clear();
    return EErrorCode::Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_Slopes.push_back(Slope(1, 1));
    m_Slopes.push_back(Slope(3, 1));
    m_Slopes.push_back(Slope(5, 1));
    m_Slopes.push_back(Slope(7, 1));
    m_Slopes.push_back(Slope(1, 2));

    return m_Lines.size() > 0 ? EErrorCode::Success : EErrorCode::Failure;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_03::Run_SecondPart()
{
    if (m_Lines.empty())
    {
        std::cout << "ERROR : m_Lines is empty !" << std::endl;
        return EErrorCode::Failure;
    }

    if (m_Slopes.empty())
    {
        std::cout << "ERROR : m_Slopes is empty !" << std::endl;
        return EErrorCode::Failure;
    }

    int rowSize = m_Lines[0].size();
    int result = 0;

    int treeCount = 0;
    int row = 0;
    int col = 0;
    for (const Slope& slope : m_Slopes)
    {
        treeCount = 0;
        row = 0;
        col = 0;
        while (row < m_Lines.size())
        {
            treeCount += m_Lines[row][col % rowSize] == sm_treeSymbol ? 1 : 0;

            col += slope.m_X;
            row += slope.m_Y;
        }

        if (result == 0)
        {
            result = treeCount;
        }
        else
        {
            result *= treeCount;
        }

        if (DEBUG_LOGS)
        {
            std::cout << "For Slope (" << slope.m_X << ", " << slope.m_Y << "), there were " << treeCount << " trees. Result was updated : " << result << "." << std::endl;
        }
    }

    std::cout << "Done ! Result is " << result << "." << std::endl;

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_03::CleanUp_SecondPart()
{
    m_Lines.clear();
    m_Slopes.clear();
    return EErrorCode::Success;
}
