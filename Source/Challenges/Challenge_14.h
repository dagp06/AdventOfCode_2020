#pragma once

#include "Common/Challenge.h"

#include <map>

using namespace std;

class CChallenge_14 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    void ExecuteOperation(const string& _operation, bool _part1);
    long long ComputeMemoryValuesSum() const;

    void ResetMask();
    void UpdateMask(const string& _maskStr);
    void WriteInMemory_1(long long _address, long long _value);
    void WriteInMemory_2(long long _address, long long _value);
    void FindAddressesForFloatingBits(vector<long long>& _adresses, vector<int> _floatingBits, int _nextFloatingBitIndex);

    static string const sm_inputFilePath;

    vector<string> m_Operations;

    long long m_BitMask0 = 0;
    long long m_BitMask1 = 0;
    vector<int> m_FloatingBits;
    map<long long, long long> m_Memory;
};
