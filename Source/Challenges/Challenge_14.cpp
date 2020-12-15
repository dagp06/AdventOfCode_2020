#include "Challenge_14.h"
#include "../Helpers/FileHelpers.h"

#include <bitset>

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_14::sm_inputFilePath = "Inputs/Input_Challenge_14.txt";

#define DEBUG_LOGS false

/*
<==> Execution times <==>
PART 1 :
  Set Up    :  0.000291 s
  Execution :  0.00256 s
  Clean Up  :  0 s
---------------------------
PART 2 :
  Set Up    :  0.000284 s
  Execution :  0.013407 s
  Clean Up  :  0 s
<=========================>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_FirstPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Operations);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::Run_FirstPart()
{
    for (string operation : m_Operations)
    {
        ExecuteOperation(operation, true);
    }

    long long sum = ComputeMemoryValuesSum();

    cout << "Done ! The sum of all values in memory is " << sum << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_14::SetUp_SecondPart()
{
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, m_Operations);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    
    return EErrorCode::Success;
}

EErrorCode CChallenge_14::Run_SecondPart()
{
    for (string operation : m_Operations)
    {
        ExecuteOperation(operation, false);
    }

    long long sum = ComputeMemoryValuesSum();

    cout << "Done ! The sum of all values in memory is " << sum << "." << endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_14::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}

void CChallenge_14::ExecuteOperation(const string& _operation, bool _part1)
{
    vector<string> opArgs;
    FileHelper::SplitLine(_operation, " = ", opArgs);

    if (opArgs[0] == "mask")
    {
        UpdateMask(opArgs[1]);
    }
    else if (opArgs[0].substr(0, 3) == "mem")
    {
        if (_part1)
            WriteInMemory_1(stoll(opArgs[0].substr(4, opArgs[0].size() - 2)), stoll(opArgs[1]));
        else
            WriteInMemory_2(stoll(opArgs[0].substr(4, opArgs[0].size() - 2)), stoll(opArgs[1]));
    }
}

long long CChallenge_14::ComputeMemoryValuesSum() const
{
    long long sum = 0;

    for (auto it = m_Memory.begin(); it != m_Memory.end(); ++it)
    {
        sum += it->second;
    }

    return sum;
}

void CChallenge_14::ResetMask()
{
    m_BitMask0 = 0;
    m_BitMask1 = 0;
    m_FloatingBits.clear();
}

void CChallenge_14::UpdateMask(const string& _maskStr)
{
    ResetMask();

    long long bitShift = _maskStr.size() - 1;
    for (int i = 0; i < _maskStr.size(); ++i)
    {
        switch (_maskStr[i])
        {
        case '0':
            m_BitMask0 |= 1ll << bitShift;
            break;
        case '1':
            m_BitMask1 |= 1ll << bitShift;
            break;
        case 'X':
            m_FloatingBits.push_back(bitShift);
        default:
            break;
        }

        --bitShift;
    }

    m_BitMask0 = ~m_BitMask0;

}

void CChallenge_14::WriteInMemory_1(long long _address, long long _value)
{
    long long result = _value;
    result &= m_BitMask0;
    result |= m_BitMask1;

    if (DEBUG_LOGS)
    {
        cout << "value:\t" << bitset<36>(_value) << "\t(decimal " << _value << ")" << endl;
        cout << "mask 0:\t" << bitset<36>(m_BitMask0) << endl;
        cout << "mask 1:\t" << bitset<36>(m_BitMask1) << endl;
        cout << "value:\t" << bitset<36>(result) << "\t(decimal " << result << ")" << endl;
        cout << endl;
    }

    m_Memory[_address] = result;
}

void CChallenge_14::WriteInMemory_2(long long _address, long long _value)
{
    long long result = _address;
    result |= m_BitMask1;

    vector<long long> addressesToWriteTo;
    addressesToWriteTo.push_back(result);

    FindAddressesForFloatingBits(addressesToWriteTo, m_FloatingBits, 0);

    if (DEBUG_LOGS)
    {
        cout << "addr.:\t" << bitset<36>(_address) << "\t(decimal " << _address << ")" << endl;
        cout << "mask 0:\t" << bitset<36>(m_BitMask0) << endl;
        cout << "mask 1:\t" << bitset<36>(m_BitMask1) << endl;
        cout << "result:\t" << bitset<36>(result) << "\t(decimal " << result << ")" << endl;
        for (long long address : addressesToWriteTo)
        {
            cout << "\taddress:\t" << bitset<36>(address) << "\t(decimal " << address << ")" << endl;
        }
        cout << endl;
    }

    for (long long address : addressesToWriteTo)
    {
        m_Memory[address] = _value;
    }

}

void CChallenge_14::FindAddressesForFloatingBits(vector<long long>& _adresses, vector<int> _floatingBits, int _nextFloatingBitIndex)
{
    if (_adresses.empty())
    {
        cout << "ERROR - CChallenge_14::FindAddressesForFloatingBits - _adresses is empty ! Needs to have at least one address." << endl;
        return;
    }

    long long bit = _floatingBits[_nextFloatingBitIndex];
    
    if (++_nextFloatingBitIndex < _floatingBits.size())
    {
        FindAddressesForFloatingBits(_adresses, _floatingBits, _nextFloatingBitIndex);
    }

    int lastAddressIndex = _adresses.size() - 1;
    for (int i = 0; i <= lastAddressIndex; ++i)
    {
        // Invert bit and add new address
        long long newAddress = _adresses[i] ^ (1ll << bit);
        _adresses.push_back(newAddress);
    }
}