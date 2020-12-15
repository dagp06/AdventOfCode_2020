#include "Challenge_13.h"
#include "../Helpers/FileHelpers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_13::sm_inputFilePath = "Inputs/Input_Challenge_13.txt";

#define DEBUG_LOGS false

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000191 s
  Execution :  0.001653 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  ? s
  Execution :  ? s
  Clean Up  :  ? s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_EarliestAvailableTime = stoull(lines[0]);

    vector<string> out;
    FileHelper::SplitLine(lines[1], ",", out);

    for (const string& IDstr : out)
    {
        if (isdigit(IDstr[0]))
        {
            m_BusIDs.push_back(stoi(IDstr));
        }
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::Run_FirstPart()
{
    int bestBusID = 0;
    int earliestDepartureTime = INT_MAX;
    for (int busID : m_BusIDs)
    {
        int nextDepartureTime = (busID - (m_EarliestAvailableTime % busID)) + m_EarliestAvailableTime;
        if (nextDepartureTime < earliestDepartureTime)
        {
            earliestDepartureTime = nextDepartureTime;
            bestBusID = busID;
        }
    }

    cout << "Done ! The result is " << ((earliestDepartureTime - m_EarliestAvailableTime) * bestBusID) << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_13::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    vector<string> busIDStrings;
    FileHelper::SplitLine(lines[1], ",", busIDStrings);

    for (int i = 0; i < busIDStrings.size(); ++i)
    {
        if (isdigit(busIDStrings[i][0]))
        {
            m_BusDepartureTimes.push_back(BusDepartureTime(stoi(busIDStrings[i]), i));
        }
    }
    
    return EErrorCode::Success;
}

EErrorCode CChallenge_13::Run_SecondPart()
{
    BusDepartureTime highestBusDepartureTime;
    for (int i = 0; i < m_BusDepartureTimes.size(); ++i)
    {
        if (highestBusDepartureTime.m_BusID < m_BusDepartureTimes[i].m_BusID)
        {
            highestBusDepartureTime.m_BusID = m_BusDepartureTimes[i].m_BusID;
            highestBusDepartureTime.m_DepartureTimeOffset = m_BusDepartureTimes[i].m_DepartureTimeOffset;
        }
    }

    bool found = false;
    unsigned long long t = unsigned long long(highestBusDepartureTime.m_BusID - highestBusDepartureTime.m_DepartureTimeOffset);
    while (t > 0 && !found)
    {
        found = true;
        for (int i = 0; i < m_BusDepartureTimes.size(); ++i)
        {
            int busID = m_BusDepartureTimes[i].m_BusID;
            unsigned long long departureTime = t + m_BusDepartureTimes[i].m_DepartureTimeOffset;
            bool busDepartsAtDepartureTime = departureTime % busID == 0;
            if (busID != highestBusDepartureTime.m_BusID && !busDepartsAtDepartureTime)
            {
                found = false;
                break;
            }
        }

        if (found)
            break;

        t += highestBusDepartureTime.m_BusID;
    }

    cout << "Done ! t = " << t << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_13::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}
