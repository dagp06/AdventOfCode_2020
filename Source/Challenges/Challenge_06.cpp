#include "Challenge_06.h"
#include "../Helpers/FileHelpers.h"

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_06::sm_inputFilePath = "Inputs/Input_Challenge_06.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.012318 s
  Execution :  0.047303 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.013063 s
  Execution :  0.016725 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_06::Run_FirstPart()
{
    ExtractSets();

    size_t sum = 0;
    for (const std::set<char>& questionSet : m_QuestionSets)
    {
        if (DEBUG_LOGS)
        {
            std::cout << sum << " + " << questionSet.size() << " = " << sum + questionSet.size() << " - ";
            for (auto it = questionSet.begin(); it != questionSet.end(); ++it)
            {
                std::cout << *it << ", ";
            }
            std::cout << std::endl;
        }
        sum += questionSet.size();
    }

    std::cout << "Done ! The sum is " << sum << "." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_06::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    
    return EErrorCode::Success;
}

EErrorCode CChallenge_06::Run_SecondPart()
{
    ExtractGroupAnswersList();

    int sum = 0;
    for (const GroupAnswers& answers : m_GroupAnswersList)
    {
        sum += CountCommonAnswers(answers);
    }

    std::cout << "Done ! The sum is " << sum << "." << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_06::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

void CChallenge_06::ExtractSets()
{
    std::set<char> newSet;
    for (const std::string& line : m_Lines)
    {
        if (line.empty())
        {
            if (!newSet.empty())
            {
                m_QuestionSets.push_back(newSet);
                newSet.clear();
            }
        }
        else
        {
            for (const char& c : line)
            {
                newSet.insert(c);
            }
        }
    }

    if (!newSet.empty())
    {
        m_QuestionSets.push_back(newSet);
        newSet.clear();
    }

}

void CChallenge_06::ExtractGroupAnswersList()
{
    GroupAnswers newGroupAnswers;
    for (const std::string& line : m_Lines)
    {
        if (line.empty())
        {
            if (!newGroupAnswers.empty())
            {
                m_GroupAnswersList.push_back(newGroupAnswers);
                newGroupAnswers.clear();
            }
        }
        else
        {
            newGroupAnswers.push_back(line);
        }
    }

    if (!newGroupAnswers.empty())
    {
        m_GroupAnswersList.push_back(newGroupAnswers);
        newGroupAnswers.clear();
    }
}

int CChallenge_06::CountUniqueAnswers(const GroupAnswers& _groupAnswers)
{
    return 0;
}

int CChallenge_06::CountCommonAnswers(const GroupAnswers& _groupAnswers)
{
    int commonAnswerCount = 0;

    // Find shortest answer list
    int shortestAnswerListIndex = FindShortestAnswerListIndex(_groupAnswers);

    // For each answer in list
    for (const char& answer : _groupAnswers[shortestAnswerListIndex])
    {
        bool isCommonAnswer = true;
        // Is it present in every other answer list
        for (int i = 0; i < _groupAnswers.size(); ++i)
        {
            if (i == shortestAnswerListIndex)
                continue;

            const std::string& currentGroupAnswers = _groupAnswers[i];
            if (std::find(currentGroupAnswers.begin(), currentGroupAnswers.end(), answer) == currentGroupAnswers.end())
            {
                isCommonAnswer = false;
                break;
            }
        }
        // increment common answer count
        if (isCommonAnswer)
            ++commonAnswerCount;
    }

    return commonAnswerCount;
}

int CChallenge_06::FindShortestAnswerListIndex(const GroupAnswers& _groupAnswers)
{
    int shortestAnswerListIndex = 0;
    for (int i = 1; i < _groupAnswers.size(); ++i)
    {
        shortestAnswerListIndex = _groupAnswers[i].size() < _groupAnswers[shortestAnswerListIndex].size() ? i : shortestAnswerListIndex;
    }

    return shortestAnswerListIndex;
}