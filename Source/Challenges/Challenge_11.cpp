#include "Challenge_11.h"
#include "../Helpers/FileHelpers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_11::sm_inputFilePath = "Inputs/Input_Challenge_11.txt";

#define DEBUG_LOGS false

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000259 s
  Execution :  0.008936 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000284 s
  Execution :  0.090977 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    SeatGrid& seatGrid = m_SeatGrids[0];
    seatGrid.resize(lines.size());
    for (int i = 0; i < lines.size(); ++i)
    {
        SeatRow& row = seatGrid[i];
        row.reserve(lines[i].size());

        for (const char& c : lines[i])
        {
            row.push_back(CharToSeatType(c));
        }
    }

    CopySeatGrid(seatGrid, m_SeatGrids[1]);

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::Run_FirstPart()
{
    int sourceGridIndex = 0;
    int writingGridIndex = 1;

    bool gridHasChanged = false;

    do
    {
        gridHasChanged = false;
        const SeatGrid& sourceGrid = m_SeatGrids[sourceGridIndex];
        SeatGrid& writingGrid = m_SeatGrids[writingGridIndex];

        for (int i = 0; i < sourceGrid.size(); ++i)
        {
            const SeatRow& sourceRow = sourceGrid[i];
            SeatRow& writingRow = writingGrid[i];

            for (int j = 0; j < sourceRow.size(); ++j)
            {
                writingRow[j] = ProcessSeat_1(sourceGrid, i, j, 1);
                
                gridHasChanged |= writingRow[j] != sourceRow[j];
            }
        }

        swap(sourceGridIndex, writingGridIndex);
    } while (gridHasChanged);

    int occupiedSeatCount = CountSeatType(m_SeatGrids[sourceGridIndex], SeatType::SeatType_Occupied);

    cout << "Done ! There are " << occupiedSeatCount << " occupied seat." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_11::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    SeatGrid& seatGrid = m_SeatGrids[0];
    seatGrid.resize(lines.size());
    for (int i = 0; i < lines.size(); ++i)
    {
        SeatRow& row = seatGrid[i];
        row.reserve(lines[i].size());

        for (const char& c : lines[i])
        {
            row.push_back(CharToSeatType(c));
        }
    }

    CopySeatGrid(seatGrid, m_SeatGrids[1]);

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::Run_SecondPart()
{
    int sourceGridIndex = 0;
    int writingGridIndex = 1;

    bool gridHasChanged = false;

    do
    {
        gridHasChanged = false;
        const SeatGrid& sourceGrid = m_SeatGrids[sourceGridIndex];
        SeatGrid& writingGrid = m_SeatGrids[writingGridIndex];

        for (int i = 0; i < sourceGrid.size(); ++i)
        {
            const SeatRow& sourceRow = sourceGrid[i];
            SeatRow& writingRow = writingGrid[i];

            for (int j = 0; j < sourceRow.size(); ++j)
            {
                writingRow[j] = ProcessSeat_2(sourceGrid, i, j);

                gridHasChanged |= writingRow[j] != sourceRow[j];
            }
        }

        swap(sourceGridIndex, writingGridIndex);
    } while (gridHasChanged);

    int occupiedSeatCount = CountSeatType(m_SeatGrids[sourceGridIndex], SeatType::SeatType_Occupied);

    cout << "Done ! There are " << occupiedSeatCount << " occupied seat." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_11::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}

CChallenge_11::SeatType CChallenge_11::CharToSeatType(const char& _char)
{
    switch (_char)
    {
    case 'L' :
        return SeatType::SeatType_Empty;
    case '#':
        return SeatType::SeatType_Occupied;
    case '.':
        return SeatType::SeatType_Floor;

    default:
        return SeatType::SeatType_Count;
    }
}

void CChallenge_11::CopySeatGrid(const SeatGrid& _src, SeatGrid& _outDest)
{
    _outDest.resize(_src.size());
    for (int i = 0; i < _src.size(); ++i)
    {
        const SeatRow& srcRow = _src[i]; 
        SeatRow& destRow = _outDest[i];
        destRow.reserve(srcRow.size());

        for (const SeatType& seatType : srcRow)
        {
            destRow.push_back(seatType);
        }
    }
}

CChallenge_11::SeatType CChallenge_11::ProcessSeat_1(const SeatGrid& _grid, int _rowIndex, int _seatIndex, int _neighboorDistance)
{
    SeatType currentSeatType = _grid[_rowIndex][_seatIndex];

    if (currentSeatType == SeatType::SeatType_Floor)
        return SeatType::SeatType_Floor;

    int minRowIndex = max(0, _rowIndex - _neighboorDistance);
    int maxRowIndex = min((int)_grid.size() - 1, _rowIndex + _neighboorDistance);

    int minSeatIndex = max(0, _seatIndex - _neighboorDistance);
    int maxSeatIndex = min((int)_grid[minRowIndex].size() - 1, _seatIndex + _neighboorDistance);

    int occupiedSeatCount = 0;
    for (int row = minRowIndex; row <= maxRowIndex; ++row)
    {
        for (int seat = minSeatIndex; seat <= maxSeatIndex; ++seat)
        {
            if (row == _rowIndex && seat == _seatIndex)
                continue;

            if (_grid[row][seat] == SeatType::SeatType_Occupied)
            {
                if (currentSeatType == SeatType::SeatType_Empty)
                    return SeatType::SeatType_Empty;
                else /*if (currentSeatType == SeatType_Occupied)*/
                {
                    ++occupiedSeatCount;
                    if (occupiedSeatCount >= 4)
                        return SeatType::SeatType_Empty;
                }
            }
        }
    }

    return SeatType::SeatType_Occupied;
}

CChallenge_11::SeatType CChallenge_11::ProcessSeat_2(const SeatGrid& _grid, int _rowIndex, int _seatIndex)
{
    SeatType currentSeatType = _grid[_rowIndex][_seatIndex];

    if (currentSeatType == SeatType::SeatType_Floor)
        return SeatType::SeatType_Floor;

    const vector<int> rowIncrements{ -1, 0, 1 };
    const vector<int> seatIncrements{ -1, 0, 1 };

    int row = _rowIndex;
    int seat = _seatIndex;
    SeatType seatType = SeatType::SeatType_Floor;
    int occupiedSeatCount = 0;
    for (int i = 0; i < rowIncrements.size(); i++)
    {
        for (int j = 0; j < seatIncrements.size(); j++)
        {
            if (rowIncrements[i] == 0 && seatIncrements[j] == 0)
                continue;

            row = _rowIndex;
            seat = _seatIndex;
            seatType = SeatType::SeatType_Floor;
            while (seatType == SeatType::SeatType_Floor)
            {
                row += rowIncrements[i];
                seat += seatIncrements[j];

                if (!AreIndicesValidForGrid(_grid, row, seat))
                    break;

                seatType = _grid[row][seat];
            }

            if (seatType == SeatType::SeatType_Floor)
                continue;

            if (seatType == SeatType::SeatType_Occupied)
            {
                if (currentSeatType == SeatType::SeatType_Empty)
                    return SeatType::SeatType_Empty;
                else /*if (currentSeatType == SeatType_Occupied)*/
                {
                    ++occupiedSeatCount;
                    if (occupiedSeatCount >= 5)
                        return SeatType::SeatType_Empty;
                }
            }
        }
    }

    return SeatType::SeatType_Occupied;
}

int CChallenge_11::CountSeatType(const SeatGrid& _grid, SeatType _seatType)
{
    int seatTypeCount = 0;

    for (int i = 0; i < _grid.size(); ++i)
    {
        const SeatRow& row = _grid[i];

        for (int j = 0; j < row.size(); ++j)
        {
            if (_grid[i][j] == _seatType)
                ++seatTypeCount;
        }
    }

    return seatTypeCount;
}

bool CChallenge_11::AreIndicesValidForGrid(const SeatGrid& _grid, int _row, int _seat)
{
    if (_row < 0 || _row >= _grid.size())
        return false;

    if (_seat < 0 || _seat >= _grid[0].size())
        return false;

    return true;
}
