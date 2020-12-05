#pragma once

#include "Common/Challenge.h"

class CChallenge_02 : public CChallenge
{
private:

    class PasswordEntry_Part1
    {
    public:
        bool SetupFromLine(std::string _line);
        bool IsValid() const;

    private:
        int m_MinOccurenceCount = 0;
        int m_MaxOccurenceCount = 0;
        char m_Character = '\0';
        std::string m_Password;
    };

    class PasswordEntry_Part2
    {
    public:
        bool SetupFromLine(std::string _line);
        bool IsValid() const;

    private:
        int m_Index1 = 0;
        int m_Index2 = 0;
        char m_Character;
        std::string m_Password;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;

    std::vector<PasswordEntry_Part1> m_PasswordEntries_Part1;
    std::vector<PasswordEntry_Part2> m_PasswordEntries_Part2;
};
