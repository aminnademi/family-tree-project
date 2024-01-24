#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

class SHA256
{
private:
    const uint32_t H[8];
    const uint32_t K[64];
    enum tempH { a, b, c, d, e, f, g, h };

    // functions and operations

    uint32_t rightRotate(uint32_t x, unsigned int shift);

    uint32_t choice(uint32_t x, uint32_t y, uint32_t z);

    uint32_t major(uint32_t x, uint32_t y, uint32_t z);

    uint32_t bigSigma0(uint32_t x);

    uint32_t bigSigma1(uint32_t x);

    uint32_t sigma0(uint32_t x);

    uint32_t sigma1(uint32_t x);

    uint8_t *calculateDigest(const uint8_t *data, uint64_t dataSizeByte);

public:
    SHA256();

    string calculateHash(string s);
};