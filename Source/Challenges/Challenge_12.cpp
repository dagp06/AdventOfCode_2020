#include "Challenge_12.h"
#include "../Helpers/FileHelpers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_12::sm_inputFilePath = "Inputs/Input_Challenge_12.txt";

#define DEBUG_LOGS false

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000246 s
  Execution :  0.001342 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000247 s
  Execution :  0.001478 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_Actions.resize(lines.size());
    for (size_t i = 0; i < lines.size(); ++i)
    {
        InitializeActionFromLine(m_Actions[i], lines[i]);
    }

    m_FerryPosition = Vector2(0);
    m_FerryDirection = Vector2(1, 0);

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::Run_FirstPart()
{
    Vector2 initialPos = m_FerryPosition;
    if (DEBUG_LOGS)
        cout << "Initial Pos : " << m_FerryPosition << " - Initial Direction : " << m_FerryDirection << endl;

    for (const Action& action : m_Actions)
    {
        ExecuteAction_1(action);
    }

    cout << "Done ! Manhattan distance from start to end is " << initialPos.ManathanDistanceTo(m_FerryPosition) << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_12::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_Actions.resize(lines.size());
    for (size_t i = 0; i < lines.size(); ++i)
    {
        InitializeActionFromLine(m_Actions[i], lines[i]);
    }

    m_FerryPosition = Vector2(0);
    m_FerryDirection = Vector2(1, 0);

    m_WaypointPosition = Vector2(10, 1);

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::Run_SecondPart()
{
    Vector2 initialPos = m_FerryPosition;
    if (DEBUG_LOGS)
        cout << "Initial Ferry Pos : " << m_FerryPosition << " - Initial Waypoint Pos : " << m_WaypointPosition << endl;

    for (const Action& action : m_Actions)
    {
        ExecuteAction_2(action);
    }

    cout << "Done ! Manhattan distance from start to end is " << initialPos.ManathanDistanceTo(m_FerryPosition) << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_12::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

void CChallenge_12::InitializeActionFromLine(Action& _action, const string& line)
{
    _action.first = line[0];
    _action.second = stoi(line.substr(1));
}

void CChallenge_12::ExecuteAction_1(const Action& _action)
{
    if (DEBUG_LOGS)
        cout << "Executing Action: " << _action.first << _action.second << "\t-\t";

    switch (_action.first)
    {
    case 'N' :
    case 'S' :
    case 'E' :
    case 'W' :
    case 'F' :
        DisplaceVector(m_FerryPosition, _action);
        break;

    case 'L':
    case 'R':
        RotateVector(m_FerryDirection, _action);
    default:
        break;
    }

    if (DEBUG_LOGS)
        cout << "P" << m_FerryPosition << "\tD" << m_FerryDirection << endl;
}

void CChallenge_12::ExecuteAction_2(const Action& _action)
{
    if (DEBUG_LOGS)
        cout << "Executing Action: " << _action.first << _action.second << "\t-\t";

    switch (_action.first)
    {
    case 'N':
    case 'S':
    case 'E':
    case 'W':
        DisplaceVector(m_WaypointPosition, _action);
        break;

    case 'F':
        MoveToWaypoint(_action.second);
        break;

    case 'L':
    case 'R':
        RotateVector(m_WaypointPosition, _action);
    default:
        break;
    }

    if (DEBUG_LOGS)
        cout << "F" << m_FerryPosition << "\tW" << m_WaypointPosition << endl;
}

void CChallenge_12::MoveToWaypoint(int _repeatCount)
{
    m_FerryPosition += _repeatCount * m_WaypointPosition;
}

void CChallenge_12::DisplaceVector(Vector2& _vector, const Action& _action)
{
    Vector2 direction;
    switch (_action.first)
    {
    case 'N':
        direction = Vector2(0, 1);
        break;
    case 'S':
        direction = Vector2(0, -1);
        break;
    case 'E':
        direction = Vector2(1, 0);
        break;
    case 'W':
        direction = Vector2(-1, 0);
        break;
    case 'F':
        direction = m_FerryDirection;
        break;
    }

    _vector += _action.second * direction;
}

void CChallenge_12::RotateVector(Vector2& _vector, const Action& _action)
{
    int sign = 1;
    switch (_action.first)
    {
    case 'L':
        sign = 1;
        break;
    case 'R':
        sign = -1;
        break;
    }

    _vector.Rotate(sign * _action.second);
}
