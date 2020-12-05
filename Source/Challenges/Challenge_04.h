#pragma once

#include "Common/Challenge.h"

class CChallenge_04 : public CChallenge
{
public:
    class PassportEntry
    {
    public:
        typedef std::pair<std::string, std::string> PassportProperty;

        EErrorCode SetupFromLine(const std::string& _line);
        void AddProperty(const PassportProperty& _val) { m_Properties.push_back(_val); }
        bool IsValid_Part1() const;
        bool IsValid_Part2() const;
        bool IsPropertyValid(const PassportProperty& _property) const;
    private:
        std::vector<PassportProperty> m_Properties;
    };


private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static std::string const sm_inputFilePath;
    static const char* sm_passportDelimiter;

    std::vector<PassportEntry> m_PassportEntries;
    static std::vector<std::string> sm_PassportRequiredFields;
    static std::vector<std::string> sm_PassportOptionalFields;
};
