#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"


#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000764 s
  Execution :  0.001951 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000805 s
  Execution :  0.001967 s
  Clean Up  :  2.8e-05 s
<=========================>
*/
////////////////////////////////////////////////////////////////////////////////////////////////////


bool CChallenge_02::PasswordEntry_Part1::SetupFromLine(std::string _line)
{
    char* line_cstr = new char[_line.length() + 1];
    strcpy_s(line_cstr, _line.length() + 1, _line.c_str());
    char delimiters[] = "- :\n";
    char* nextToken = nullptr;
    char* pch = strtok_s(line_cstr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_MinOccurenceCount = atoi(pch);

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_MaxOccurenceCount = atoi(pch);

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Character = pch[0];

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Password = std::string(pch);

    delete[] line_cstr;
    return true;
}

// -------------------------------------------------------------------------------------------

bool CChallenge_02::PasswordEntry_Part1::IsValid() const
{
    int occurences = std::count(m_Password.begin(), m_Password.end(), m_Character);

    if (DEBUG_LOGS)
    {
        bool isValid = occurences >= m_MinOccurenceCount && occurences <= m_MaxOccurenceCount;
        
        std::cout << (isValid ? "  " : "IN") << "VALID PASSWORD : " << m_MinOccurenceCount << "-" << m_MaxOccurenceCount << " " << m_Character << ": " << m_Password << std::endl;
    }

    return occurences >= m_MinOccurenceCount && occurences <= m_MaxOccurenceCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (std::string line : lines)
    {
        PasswordEntry_Part1 newEntry;
        if (!newEntry.SetupFromLine(line))
            return EErrorCode::Failure;

        m_PasswordEntries_Part1.push_back(newEntry);
    }

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_02::Run_FirstPart()
{
    int validEntries = 0;
    for (const PasswordEntry_Part1& entry : m_PasswordEntries_Part1)
    {
        validEntries += entry.IsValid() ? 1 : 0;
    }

    std::cout << "Validation completed. " << validEntries << "/" << m_PasswordEntries_Part1.size() << " passwords were valid." << std::endl;

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
    m_PasswordEntries_Part1.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
bool CChallenge_02::PasswordEntry_Part2::SetupFromLine(std::string _line)
{
    char* line_cstr = new char[_line.length() + 1];
    strcpy_s(line_cstr, _line.length() + 1, _line.c_str());
    char delimiters[] = "- :\n";
    char* nextToken = nullptr;
    char* pch = strtok_s(line_cstr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Index1 = atoi(pch) - 1;

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Index2 = atoi(pch) - 1;

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Character = pch[0];

    pch = strtok_s(nullptr, delimiters, &nextToken);
    if (pch == nullptr)
    {
        std::cout << "ERROR - Wrong format in input file for line : " << _line << std::endl;
        delete[] line_cstr;
        return false;
    }
    m_Password = std::string(pch);

    delete[] line_cstr;
    return true;
}

// -------------------------------------------------------------------------------------------

bool CChallenge_02::PasswordEntry_Part2::IsValid() const
{
    bool isValid = m_Index1 < m_Password.size() && m_Index2 < m_Password.size();
    if (isValid)
    {
        isValid = m_Password[m_Index1] == m_Character;
        isValid ^= m_Password[m_Index2] == m_Character;
    }

    if (DEBUG_LOGS)
    {
        std::cout << (isValid ? "  " : "IN") << "VALID PASSWORD : " << m_Index1 << "-" << m_Index2 << " " << m_Character << ": " << m_Password << std::endl;
    }

    return isValid;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_02::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    for (std::string line : lines)
    {
        PasswordEntry_Part2 newEntry;
        if (!newEntry.SetupFromLine(line))
            return EErrorCode::Failure;

        m_PasswordEntries_Part2.push_back(newEntry);
    }

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_02::Run_SecondPart()
{
    int validEntries = 0;
    for (const PasswordEntry_Part2& entry : m_PasswordEntries_Part2)
    {
        validEntries += entry.IsValid() ? 1 : 0;
    }

    std::cout << "Validation completed. " << validEntries << "/" << m_PasswordEntries_Part2.size() << " passwords were valid." << std::endl;

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
    m_PasswordEntries_Part2.clear();
    return EErrorCode::Success;
}
