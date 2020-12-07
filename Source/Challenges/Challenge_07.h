#pragma once

#include "Common/Challenge.h"

#include <map>
#include <set>

class CChallenge_07 : public CChallenge
{
    struct ParentBagAllowedColorRule
    {
        ParentBagAllowedColorRule(const std::string& _color) : m_ChildColor(_color) {};

        std::string m_ChildColor;
        std::set<std::string> m_ParentBagAllowedColors;
    };

    struct BagColorRule
    {
        BagColorRule(const std::string& _color) : m_ParentColor(_color) {};

        std::string m_ParentColor;
        std::map<std::string, int> m_ChildBagColorMap;
    };

private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode ExtractColorRules(const std::vector<std::string>& _lines);

    const BagColorRule* FindBagColorRule(const std::string& _color);
    BagColorRule& FindOrCreateBagColorRule(const std::string& _color);

    int CountAllowedContainerColorsForColor(const std::string& _color);
    int CountAllowedContainerColorsForColor_Internal(const std::string& _color, const std::string& _initialColor, std::set<std::string>& _allowedColors);

    int CountChildrenBagCountForColor(const std::string& _color);
    int CountChildrenBagCountForColor_Internal(const std::string& _color, const std::string& _initialColor);

    ParentBagAllowedColorRule& FindOrCreateParentBagAllowedColorRule(const std::string& _childColor);

    static std::string const sm_inputFilePath;

    std::vector<BagColorRule> m_BagColorRules;
    std::vector<ParentBagAllowedColorRule> m_ParentBagAllowedColorRules;
};
