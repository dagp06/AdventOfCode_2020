#pragma once

#include "Common/Challenge.h"
#include "../Helpers/MathHelper.h"

using namespace std;
using namespace MathHelper;

class CChallenge_12 : public CChallenge
{
private:
    typedef pair<char, int> Action;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void InitializeActionFromLine(Action& _action, const string& line);
    void ExecuteAction_1(const Action& _action);
    void ExecuteAction_2(const Action& _action);
    void MoveToWaypoint(int _repeatCount);
    void DisplaceVector(Vector2& _vector, const Action& _action);
    void RotateVector(Vector2& _vector, const Action& _action);

    static string const sm_inputFilePath;


    vector<Action> m_Actions;
    Vector2 m_WaypointPosition;
    Vector2 m_FerryPosition;
    Vector2 m_FerryDirection;
};