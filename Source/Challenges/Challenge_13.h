#pragma once

#include "Common/Challenge.h"

using namespace std;

class CChallenge_13 : public CChallenge
{
private:
    struct BusDepartureTime
    {
        BusDepartureTime() : m_BusID(0), m_DepartureTimeOffset(0) {}
        BusDepartureTime(int _busID, int _departureTime) : m_BusID(_busID), m_DepartureTimeOffset(_departureTime) {}

        int m_BusID;
        int m_DepartureTimeOffset;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    unsigned long long m_EarliestAvailableTime;
    vector<int> m_BusIDs;
    vector<BusDepartureTime> m_BusDepartureTimes;
};
