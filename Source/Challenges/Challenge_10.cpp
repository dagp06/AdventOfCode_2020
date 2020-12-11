#include "Challenge_10.h"
#include "../Helpers/FileHelpers.h"

#include <algorithm>
#include <set>

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_10::sm_inputFilePath = "Inputs/Input_Challenge_10.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000157 s
  Execution :  0.000921 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000139 s
  Execution :  0.001619 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (string s : lines)
    {
        int joltage = stoi(s);
        m_AdapterJoltages.insert(upper_bound(m_AdapterJoltages.begin(), m_AdapterJoltages.end(), joltage), joltage);
    }

    m_AdapterJoltages.push_back(m_AdapterJoltages[m_AdapterJoltages.size() - 1] + 3);

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::Run_FirstPart()
{
    multiset<int> joltageDifferences;

    int previousJoltage = 0;
    for (auto it = m_AdapterJoltages.begin(); it != m_AdapterJoltages.end(); ++it)
    {
        joltageDifferences.insert(*it - previousJoltage);
        previousJoltage = *it;
    }

    int jolt1differences = joltageDifferences.count(1);
    int jolt3differences = joltageDifferences.count(3);
    cout << "Done ! 1-jolt differences (" << jolt1differences << ") * 3-jolt differences (" << jolt3differences << ") = " << jolt1differences * jolt3differences << ".";

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_10::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_AdapterJoltages.push_back(0);

    for (string s : lines)
    {
        int joltage = stoi(s);
        m_AdapterJoltages.insert(upper_bound(m_AdapterJoltages.begin(), m_AdapterJoltages.end(), joltage), joltage);
    }

    m_AdapterJoltages.push_back(m_AdapterJoltages[m_AdapterJoltages.size() - 1] + 3);

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::Run_SecondPart()
{
    m_CombinationsFromAdapters[m_AdapterJoltages[m_AdapterJoltages.size() - 1]] = 1ull;

    for (int i = m_AdapterJoltages.size() - 2; i >= 0; --i)
    {
        int currentJoltage = m_AdapterJoltages[i];
        unsigned long long& combinationsFromCurrentAdaptor = m_CombinationsFromAdapters[currentJoltage];
        for (int j = i + 1; j < m_AdapterJoltages.size(); ++j)
        {
            int higherJoltage = m_AdapterJoltages[j];
            if (higherJoltage - currentJoltage <= 3)
            {
                combinationsFromCurrentAdaptor += m_CombinationsFromAdapters[higherJoltage];
            }
            else
            {
                break;
            }
        }
    }

    cout << "Done ! Max number of combinations is " << m_CombinationsFromAdapters[m_AdapterJoltages[0]] << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_10::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}
