#include "Challenge_09.h"
#include "../Helpers/FileHelpers.h"

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_09::sm_inputFilePath = "Inputs/Input_Challenge_09.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000316 s
  Execution :  0.000937 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.0013 s
  Execution :  0.000973 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (string s : lines)
    {
        m_NumberSerie.push_back(stoull(s));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::Run_FirstPart()
{
    int preambleSize = 25;
    int invalidEntry = 0;

    for (int i = preambleSize; i < m_NumberSerie.size(); ++i)
    {
        bool isValid = false;
        for (int j = i - preambleSize; j < (i - 1); ++j)
        {
            for (int k = j + 1; k < i; ++k)
            {
                if (m_NumberSerie[i] == (m_NumberSerie[j] + m_NumberSerie[k]))
                {
                    isValid = true;
                    break;
                }
            }
            if (isValid)
                break;
        }

        if (!isValid)
        {
            invalidEntry = m_NumberSerie[i];
            break;
        }
    }

    cout << "Done ! Invalid entry is " << invalidEntry << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (string s : lines)
    {
        m_NumberSerie.push_back(stoull(s));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::Run_SecondPart()
{
    const unsigned long long targetValue = 144381670ull;

    // Find Range
    unsigned long long sum;
    int minIndex = 0;
    int maxIndex = 0;
    for (minIndex = 0; minIndex < m_NumberSerie.size() - 1; ++minIndex)
    {
        sum = m_NumberSerie[minIndex];
        for (maxIndex = minIndex + 1; maxIndex < m_NumberSerie.size() && sum < targetValue; ++maxIndex)
        {
            sum += m_NumberSerie[maxIndex];
        }

        if (sum == targetValue)
            break;
    }

    // Find min and max values in range
    unsigned long long minValue = m_NumberSerie[minIndex];
    unsigned long long maxValue = m_NumberSerie[minIndex];
    for (int i = minIndex + 1; i <= maxIndex; ++i)
    {
        minValue = min(minValue, m_NumberSerie[i]);
        maxValue = max(maxValue, m_NumberSerie[i]);
    }

    cout << "Done ! Sum of smallest (" << minValue << ") and largest (" << maxValue << ") entries is " << minValue + maxValue << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_09::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}
