#include "Challenge_04.h"
#include "../Helpers/FileHelpers.h"
#include <fstream>

#define DEBUG_LOGS true

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_04::sm_inputFilePath = "Inputs/Input_Challenge_04.txt";
const char* CChallenge_04::sm_passportDelimiter = ": \n";
std::vector<std::string> CChallenge_04::sm_PassportRequiredFields;
std::vector<std::string> CChallenge_04::sm_PassportOptionalFields;

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.051509 s
  Execution :  0.01154 s
  Clean Up  :  0.001432 s
---------------------------
PART 2 :
  Set Up    :  0.051067 s
  Execution :  0.012022 s
  Clean Up  :  0.00145 s
<=========================>
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_FirstPart()
{
    std::ifstream fileToRead(sm_inputFilePath);
    if (!fileToRead.is_open())
    {
        return EErrorCode::FileNotFound;
    }

    bool isFileEmpty = true;
    std::string newLine;
    std::string passportLine;

    while (std::getline(fileToRead, newLine))
    {
        if (newLine.empty() || newLine[0] == '\n')
        {
            if (isFileEmpty && newLine.empty())
            {
                break;
            }
            else
            {
                PassportEntry newEntry;
                EErrorCode result = newEntry.SetupFromLine(passportLine);
                if (result == EErrorCode::Success)
                {
                    m_PassportEntries.push_back(newEntry);
                    passportLine.clear();
                }
                else
                {
                    return result;
                }
            }
        }
        else
        {
            passportLine.append(" ");
            passportLine.append(newLine);
        }

        isFileEmpty &= newLine.empty();
    }
    fileToRead.close();

    if (!passportLine.empty())
    {
        PassportEntry newEntry;
        EErrorCode result = newEntry.SetupFromLine(passportLine);
        if (result == EErrorCode::Success)
        {
            m_PassportEntries.push_back(newEntry);
            passportLine.clear();
        }
        else
        {
            return result;
        }
    }

    sm_PassportRequiredFields.push_back("byr");
    sm_PassportRequiredFields.push_back("iyr");
    sm_PassportRequiredFields.push_back("eyr");
    sm_PassportRequiredFields.push_back("hgt");
    sm_PassportRequiredFields.push_back("hcl");
    sm_PassportRequiredFields.push_back("ecl");
    sm_PassportRequiredFields.push_back("pid");

    sm_PassportOptionalFields.push_back("cid");

    return isFileEmpty ? EErrorCode::FileEmpty : EErrorCode::Success;
}

EErrorCode CChallenge_04::Run_FirstPart()
{
    int validPassportCount = 0;
    for (const CChallenge_04::PassportEntry& entry : m_PassportEntries)
    {
        validPassportCount += entry.IsValid_Part1() ? 1 : 0;
    }

    std::cout << "Done ! There were " << validPassportCount << "/" << m_PassportEntries.size() << " valid passports." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_FirstPart()
{
    m_PassportEntries.clear();
    sm_PassportRequiredFields.clear();
    sm_PassportOptionalFields.clear();
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_SecondPart()
{
    std::ifstream fileToRead(sm_inputFilePath);
    if (!fileToRead.is_open())
    {
        return EErrorCode::FileNotFound;
    }

    bool isFileEmpty = true;
    std::string newLine;
    std::string passportLine;

    while (std::getline(fileToRead, newLine))
    {
        if (newLine.empty() || newLine[0] == '\n')
        {
            if (isFileEmpty && newLine.empty())
            {
                break;
            }
            else
            {
                PassportEntry newEntry;
                EErrorCode result = newEntry.SetupFromLine(passportLine);
                if (result == EErrorCode::Success)
                {
                    m_PassportEntries.push_back(newEntry);
                    passportLine.clear();
                }
                else
                {
                    return result;
                }
            }
        }
        else
        {
            passportLine.append(" ");
            passportLine.append(newLine);
        }

        isFileEmpty &= newLine.empty();
    }
    fileToRead.close();

    if (!passportLine.empty())
    {
        PassportEntry newEntry;
        EErrorCode result = newEntry.SetupFromLine(passportLine);
        if (result == EErrorCode::Success)
        {
            m_PassportEntries.push_back(newEntry);
            passportLine.clear();
        }
        else
        {
            return result;
        }
    }

    sm_PassportRequiredFields.push_back("byr");
    sm_PassportRequiredFields.push_back("iyr");
    sm_PassportRequiredFields.push_back("eyr");
    sm_PassportRequiredFields.push_back("hgt");
    sm_PassportRequiredFields.push_back("hcl");
    sm_PassportRequiredFields.push_back("ecl");
    sm_PassportRequiredFields.push_back("pid");

    sm_PassportOptionalFields.push_back("cid");

    return isFileEmpty ? EErrorCode::FileEmpty : EErrorCode::Success;
}

EErrorCode CChallenge_04::Run_SecondPart()
{
    int validPassportCount = 0;
    for (const CChallenge_04::PassportEntry& entry : m_PassportEntries)
    {
        validPassportCount += entry.IsValid_Part2() ? 1 : 0;
    }

    std::cout << "Done ! There were " << validPassportCount << "/" << m_PassportEntries.size() << " valid passports." << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_SecondPart()
{
    m_PassportEntries.clear();
    sm_PassportRequiredFields.clear();
    sm_PassportOptionalFields.clear();
    return EErrorCode::Success;
}

EErrorCode CChallenge_04::PassportEntry::SetupFromLine(const std::string& _line)
{
    std::vector<std::string> propertiesStr;
    FileHelper::SplitLine(_line, " ", propertiesStr);

    for (const std::string& propertyStr : propertiesStr)
    {
        if (propertyStr.empty())
            continue;

        std::vector<std::string> propertyFieldValue;
        FileHelper::SplitLine(propertyStr, ":", propertyFieldValue);

        if (propertyFieldValue.size() != 2)
        {
            std::cout << "ERROR : Wrong input format for property \"" << propertyStr << "\" in entry \"" << _line << "\"." << std::endl;
            return EErrorCode::Failure;
        }

        PassportProperty newProperty(propertyFieldValue[0], propertyFieldValue[1]);
        AddProperty(newProperty);
    }

    return EErrorCode::Success;
}

bool CChallenge_04::PassportEntry::IsValid_Part1() const
{
    if (m_Properties.size() < sm_PassportRequiredFields.size())
    {
        return false;
    }
    else
    {
        for (const std::string& requiredField : sm_PassportRequiredFields)
        {
            bool found = false;
            for (const PassportProperty property : m_Properties)
            {
                if (property.first == requiredField)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }

        return true;
    }
}

bool CChallenge_04::PassportEntry::IsValid_Part2() const
{
    if (m_Properties.size() < sm_PassportRequiredFields.size())
    {
        return false;
    }
    else
    {
        for (const std::string& requiredField : sm_PassportRequiredFields)
        {
            bool presentAndValid = false;
            for (const PassportProperty property : m_Properties)
            {
                if (property.first == requiredField)
                {
                    presentAndValid = IsPropertyValid(property);
                    break;
                }
            }

            if (!presentAndValid)
                return false;
        }

        return true;
    }
}

bool CChallenge_04::PassportEntry::IsPropertyValid(const PassportProperty& _property) const
{
    if (_property.first == "byr")
    {
        if (_property.second.size() == 4 && std::stoi(_property.second) >= 1920 && std::stoi(_property.second) <= 2002)
            return true;
    }
    else if (_property.first == "iyr")
    {
        if (_property.second.size() == 4 && std::stoi(_property.second) >= 2010 && std::stoi(_property.second) <= 2020)
            return true;
    }
    else if (_property.first == "eyr")
    {
        if (_property.second.size() == 4 && std::stoi(_property.second) >= 2020 && std::stoi(_property.second) <= 2030)
            return true;
    }
    else if (_property.first == "hgt")
    {
        std::string heightStr;
        std::string unit;
        for (auto it = _property.second.begin(); it != _property.second.end(); ++it)
        {
            if (isdigit(*it))
                heightStr.push_back(*it);
            else
            {
                unit.append(it, _property.second.end());
                break;
            }
        }

        if (heightStr.empty())
            return false;

        int height = std::stoi(heightStr);
        if (unit == "cm")
        {
            return height >= 150 && height <= 193;
        }
        else if (unit == "in")
        {
            return height >= 59 && height <= 76;
        }
        else
            return false;
    }
    else if (_property.first == "hcl")
    {
        std::string color = _property.second;
        if (color.size() != 7)
            return false;

        if (color[0] != '#')
            return false;

        color.erase(0);
        for (const char& c : color)
        {
            if (!isdigit(c) && (c < 'a' || c > 'f'))
                return false;
        }

        return true;
    }
    else if (_property.first == "ecl")
    {
        const std::string& color = _property.second;
        if (color.empty())
            return false;

        if (color == "amb" || color == "blu" || color == "brn" || color == "gry" || color == "grn" || color == "hzl" || color == "oth")
            return true;

        return false;
    }
    else if (_property.first == "pid")
    {
        if (_property.second.size() != 9)
            return false;

        for (const char& c : _property.second)
        {
            if (!isdigit(c))
                return false;
        }

        return true;
    }

    return false;
}
