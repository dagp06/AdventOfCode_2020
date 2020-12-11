#pragma once

#include "Common/Challenge.h"

using namespace std;

class CChallenge_11 : public CChallenge
{
private:
    enum class SeatType
    {
        SeatType_Floor,
        SeatType_Empty,
        SeatType_Occupied,
        SeatType_Count
    };

    typedef vector<SeatType> SeatRow;
    typedef vector<SeatRow> SeatGrid;

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static string const sm_inputFilePath;

    static SeatType CharToSeatType(const char& _char);

    static bool AreIndicesValidForGrid(const SeatGrid& _grid, int _row, int _seat);
    static void CopySeatGrid(const SeatGrid& _src, SeatGrid& _outDest);
    static int CountSeatType(const SeatGrid& _grid, SeatType _seatType);

    static SeatType ProcessSeat_1(const SeatGrid& _grid, int _rowIndex, int _seatIndex, int _neighboorDistance);
    static SeatType ProcessSeat_2(const SeatGrid& _grid, int _rowIndex, int _seatIndex);

    SeatGrid m_SeatGrids[2];
};
