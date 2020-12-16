#include "Challenge_15.h"
#include "../Helpers/FileHelpers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_15::sm_inputFilePath = "Inputs/Input_Challenge_15.txt";

#define DEBUG_LOGS false

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000127 s
  Execution :  0.002012 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000143 s
  Execution :  14.5326 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_15::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    vector<string> numberStrs;
    FileHelper::SplitLine(lines[0], ",", numberStrs);

    for (string numberStr : numberStrs)
    {
        m_StartingNumbers.push_back(stoi(numberStr));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_15::Run_FirstPart()
{
    long long n = 2020;

    long long lastSpokenNumber = FindNthSpokenNumber(n);

    cout << endl << "Done ! The " << n << "th number spoken will be " << lastSpokenNumber << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_15::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_15::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    vector<string> numberStrs;
    FileHelper::SplitLine(lines[0], ",", numberStrs);

    for (string numberStr : numberStrs)
    {
        m_StartingNumbers.push_back(stoi(numberStr));
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_15::Run_SecondPart()
{
    long long n = 30000000;

    long long lastSpokenNumber = FindNthSpokenNumber(n);

    cout << endl << "Done ! The " << n << "th number spoken will be " << lastSpokenNumber << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_15::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

long long CChallenge_15::FindNthSpokenNumber(long long _n)
{
    for (int i = 0; i < m_StartingNumbers.size() - 1; ++i)
    {
        m_SpokenNumbers[m_StartingNumbers[i]].first = (long long)i + 1ll;
        m_SpokenNumbers[m_StartingNumbers[i]].second = (long long)i + 1ll;

        if (DEBUG_LOGS)
            cout << "Turn " << i + 1 << ": " << m_StartingNumbers[i] << endl;
    }

    long long turn = (long long)m_StartingNumbers.size();
    long long lastSpokenNumber = m_StartingNumbers[m_StartingNumbers.size() - 1];
    while (turn <= _n)
    {
        map<long long, LastOccurences>::iterator it = m_SpokenNumbers.find(lastSpokenNumber);
        if (it != m_SpokenNumbers.end())
        {
            LastOccurences& lastOccurences = it->second;
            int lastOccurencesDelta = lastOccurences.first - lastOccurences.second;

            if (lastOccurencesDelta > 0)
            {
                lastSpokenNumber = lastOccurencesDelta;
            }
            else
            {
                lastSpokenNumber = 0;
            }
        }

        it = m_SpokenNumbers.find(lastSpokenNumber);
        LastOccurences& lastOccurences = m_SpokenNumbers[lastSpokenNumber];

        if (it != m_SpokenNumbers.end())
            lastOccurences.second = lastOccurences.first;
        else
            lastOccurences.second = turn;

        lastOccurences.first = turn;

        if (DEBUG_LOGS)
            cout << "Turn " << turn << ": " << lastSpokenNumber << endl;

        ++turn;
    }

    return lastSpokenNumber;
}
