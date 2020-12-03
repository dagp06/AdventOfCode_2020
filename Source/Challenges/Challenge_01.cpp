#include "Challenge_01.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000182 s
  Execution :  0.013659 s
  Clean Up  :  1e-05 s
---------------------------
PART 2 :
  Set Up    :  0.00019 s
  Execution :  0.492299 s
  Clean Up  :  1.1e-05 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (std::string line : lines)
    {
        m_entries.insert(std::stoi(line));
    }

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_01::Run_FirstPart()
{
    int sum = 2020;
    int result = 0;
    int i = 0;
    for (auto it = m_entries.begin(); it != m_entries.end(); it = m_entries.upper_bound(*it))
    {
        int currentValue = *it;
        int targetValue = sum - currentValue;

        std::cout << "Entry[" << i << "] = " << currentValue << " - Target Value = " << targetValue << std::endl;
        if (m_entries.find(targetValue) != m_entries.end())
        {
            result = currentValue * targetValue;
            std::cout << "BINGO ! Entries are " << currentValue << " and " << targetValue << ". Result = " << result << "." << std::endl;
            break;
        }

        ++i;
    }

    return result != 0 ? EErrorCode::Success : EErrorCode::Failure;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_01::CleanUp_FirstPart()
{
    m_entries.clear();
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }


    for (std::string line : lines)
    {
        m_entries.insert(std::stoi(line));
    }
    
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_01::Run_SecondPart()
{
    int sum = 2020;
    int result = 0;
    int i = 0;
    int currentValue = 0;
    int targetValue = 0;
    for (auto it_1 = m_entries.begin(); it_1 != m_entries.end(); it_1 = m_entries.upper_bound(*it_1))
    {
        for (auto it_2 = m_entries.upper_bound(*it_1); it_2 != m_entries.end(); it_2 = m_entries.upper_bound(*it_2))
        {
            currentValue = *it_1 + *it_2;
            if (currentValue > sum)
                break;

            targetValue = sum - currentValue;

            std::cout  << i << " - " << *it_1 << " + " << *it_2 << " = " << currentValue << " - Target Value = " << targetValue << std::endl;
            if (m_entries.find(targetValue) != m_entries.end())
            {
                result = *it_1 * *it_2 * targetValue;
                std::cout << "BINGO ! Entries are " << *it_1 << ", " << *it_2 << " and " << targetValue << ". Result = " << result << "." << std::endl;
                break;
            }

            ++i;
        }

        if (result != 0)
            break;

        if (currentValue > sum)
            continue;
    }

    return result != 0 ? EErrorCode::Success : EErrorCode::Failure;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_01::CleanUp_SecondPart()
{
    m_entries.clear();
    return EErrorCode::Success;
}