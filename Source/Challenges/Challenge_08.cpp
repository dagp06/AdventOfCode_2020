#include "Challenge_08.h"
#include "../Helpers/FileHelpers.h"

#include <set>
#include <unordered_set>

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_08::sm_inputFilePath = "Inputs/Input_Challenge_08.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.003541 s
  Execution :  0.003615 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.003863 s
  Execution :  0.30355 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_FirstPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_LinesOfCode);
}

EErrorCode CChallenge_08::Run_FirstPart()
{
    bool ignore = false;
    int accumulator = 0;
    RunProgram(ignore, accumulator);

    cout << "Done ! Accumulator's value is " << accumulator << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_SecondPart()
{
    return FileHelper::ReadLines(sm_inputFilePath, m_LinesOfCode);
}

EErrorCode CChallenge_08::Run_SecondPart()
{
    bool infiniteLoopFound = false;
    int accumulator = 0;
    for (size_t i = 0; i < m_LinesOfCode.size(); ++i)
    {
        if (!ChangeOp(i))
            continue;

        infiniteLoopFound = false;
        accumulator = 0;
        RunProgram(infiniteLoopFound, accumulator);

        if (!infiniteLoopFound)
            break;

        RestoreOp();
    }

    cout << "Done ! Accumulator's value is " << accumulator << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}

void CChallenge_08::RunProgram(bool& _infiniteLoopFound, int& accumulator)
{
    unordered_set<int> opHistory;
    for (size_t i = 0; i < m_LinesOfCode.size(); ++i)
    {
        if (opHistory.find(i) != opHistory.end())
        {
            _infiniteLoopFound = true;
            break;
        }

        opHistory.insert(i);

        vector<string> opArgs;
        FileHelper::SplitLine(m_LinesOfCode[i], " ", opArgs);

        if (opArgs[0] == "acc")
        {
            accumulator += stoi(opArgs[1]);
        }
        else if (opArgs[0] == "jmp")
        {
            i += stoi(opArgs[1]) - 1;
        }
    }
}

bool CChallenge_08::ChangeOp(int opIndex)
{
    vector<string> opArgs;
    FileHelper::SplitLine(m_LinesOfCode[opIndex], " ", opArgs);

    string newOp;
    if (opArgs[0] == "jmp")
    {
        newOp = "nop " + opArgs[1];
    }
    else if (opArgs[0] == "nop")
    {
        newOp = "jmp " + opArgs[1];
    }
    else
    {
        return false;
    }

    m_CachedOp = pair<int, string>(opIndex, m_LinesOfCode[opIndex]);
    m_LinesOfCode[opIndex] = newOp;
}

void CChallenge_08::RestoreOp()
{
    if (m_CachedOp.first < m_LinesOfCode.size())
        m_LinesOfCode[m_CachedOp.first] = m_CachedOp.second;
}
