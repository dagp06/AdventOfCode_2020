#include "Challenge_07.h"
#include "../Helpers/FileHelpers.h"

#define DEBUG_LOGS false

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_07::sm_inputFilePath = "Inputs/Input_Challenge_07.txt";

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.129111 s
  Execution :  0.02171 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.127855 s
  Execution :  0.003311 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    ExtractColorRules(lines);

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_07::Run_FirstPart()
{
    std::string childColor = "shiny gold";
    int allowedContainerColorCount = CountAllowedContainerColorsForColor(childColor);

    std::cout << "Done ! There are " << allowedContainerColorCount << " color bags that can contain at least 1 " << childColor << " bag." << std::endl;
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_07::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    ExtractColorRules(lines);
    
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_07::Run_SecondPart()
{
    std::string parentColor = "shiny gold";
    int childrenBagCount = CountChildrenBagCountForColor(parentColor);

    std::cout << "Done ! " << parentColor << " bags contain " << childrenBagCount << " bags." << std::endl;
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

EErrorCode CChallenge_07::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------



EErrorCode CChallenge_07::ExtractColorRules(const std::vector<std::string>& _lines)
{
    for (const std::string& line : _lines)
    {
        std::vector<std::string> tokens;
        FileHelper::SplitLine(line, " bags contain ", tokens);

        std::string parentColor = tokens[0];
        BagColorRule& colorRule = FindOrCreateBagColorRule(parentColor);

        if (tokens[1] == "no other bags.")
            continue;

        std::vector<std::string> lineParts;
        FileHelper::SplitLine(tokens[1], " ", lineParts);
        for (int i = 0; i < lineParts.size(); i += 4)
        {
            int amount = stoi(lineParts[i]);
            const std::string& childColor = lineParts[i + 1] + " " + lineParts[i + 2];
            colorRule.m_ChildBagColorMap.insert(std::pair<std::string, int>(childColor, amount));

            ParentBagAllowedColorRule& colorRule = FindOrCreateParentBagAllowedColorRule(childColor);
            colorRule.m_ParentBagAllowedColors.insert(parentColor);
        }
    }

    return EErrorCode::Success;
}

// -------------------------------------------------------------------------------------------

const CChallenge_07::BagColorRule* CChallenge_07::FindBagColorRule(const std::string& _color)
{
    for (BagColorRule& rule : m_BagColorRules)
    {
        if (_color == rule.m_ParentColor)
            return &rule;
    }

    return nullptr;
}

// -------------------------------------------------------------------------------------------

CChallenge_07::BagColorRule& CChallenge_07::FindOrCreateBagColorRule(const std::string& _color)
{
    for (BagColorRule& rule : m_BagColorRules)
    {
        if (_color == rule.m_ParentColor)
            return rule;
    }

    m_BagColorRules.push_back(BagColorRule(_color));
    return m_BagColorRules[m_BagColorRules.size() - 1];
}

// -------------------------------------------------------------------------------------------

int CChallenge_07::CountAllowedContainerColorsForColor(const std::string& _color)
{
    std::set<std::string> allowedColors;
    return CountAllowedContainerColorsForColor_Internal(_color, _color, allowedColors);
}

// -------------------------------------------------------------------------------------------

int CChallenge_07::CountAllowedContainerColorsForColor_Internal(const std::string& _color, const std::string& _initialColor, std::set<std::string>& _allowedColors)
{
    for (const ParentBagAllowedColorRule& rule : m_ParentBagAllowedColorRules)
    {
        if (rule.m_ChildColor == _color)
        {
            _allowedColors.insert(rule.m_ParentBagAllowedColors.begin(), rule.m_ParentBagAllowedColors.end());
            for (const std::string& parentColor : rule.m_ParentBagAllowedColors)
            {
                if (parentColor == _initialColor)
                    continue;
                CountAllowedContainerColorsForColor_Internal(parentColor, _initialColor, _allowedColors);
            }

            break;
        }
    }

    return (int)_allowedColors.size();
}

// -------------------------------------------------------------------------------------------

int CChallenge_07::CountChildrenBagCountForColor(const std::string& _color)
{
    return CountChildrenBagCountForColor_Internal(_color, _color);
}

// -------------------------------------------------------------------------------------------

int CChallenge_07::CountChildrenBagCountForColor_Internal(const std::string& _color, const std::string& _initialColor)
{
    int totalBags = 0;
    const BagColorRule* rule = FindBagColorRule(_color);
    if (rule != nullptr)
    {
        for (auto childBagPair : rule->m_ChildBagColorMap)
        {
            if (childBagPair.first == _initialColor)
            {
                std::cout << "ERROR : Recursion found in input rules." << std::endl;
                return 0;
            }

            totalBags += childBagPair.second * (1 + CountChildrenBagCountForColor_Internal(childBagPair.first, _initialColor));
        }
    }

    return totalBags;
}

// -------------------------------------------------------------------------------------------

CChallenge_07::ParentBagAllowedColorRule& CChallenge_07::FindOrCreateParentBagAllowedColorRule(const std::string& _childColor)
{
    for (ParentBagAllowedColorRule& rule : m_ParentBagAllowedColorRules)
    {
        if (_childColor == rule.m_ChildColor)
            return rule;
    }

    m_ParentBagAllowedColorRules.push_back(ParentBagAllowedColorRule(_childColor));
    return m_ParentBagAllowedColorRules[m_ParentBagAllowedColorRules.size() - 1];
}
