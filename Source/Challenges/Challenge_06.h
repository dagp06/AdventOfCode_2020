#pragma once

#include "Common/Challenge.h"

#include <set>

class CChallenge_06 : public CChallenge
{
    typedef std::vector<std::string> GroupAnswers;
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void ExtractSets();
    void ExtractGroupAnswersList();
    
    static int CountUniqueAnswers(const GroupAnswers& _groupAnswers);
    static int CountCommonAnswers(const GroupAnswers& _groupAnswers);
    static int FindShortestAnswerListIndex(const GroupAnswers& _groupAnswers);

    std::vector<std::string> m_Lines;
    std::vector<std::set<char>> m_QuestionSets;
    std::vector<GroupAnswers> m_GroupAnswersList;

    static std::string const sm_inputFilePath;
};
