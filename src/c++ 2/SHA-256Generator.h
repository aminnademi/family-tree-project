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

    /* all these functions performs a couple of bitwise AND, NOT, and XOR operations. 
    the execution time is constant and does not depend on the input size. so they all result in O(1)*/

    uint8_t *calculateDigest(const uint8_t *data, uint64_t dataSizeByte);
    /* the time complexity of this method mainly comes from the loop that processes each 512-bit block of data.
    the number of blocks is proportional to the size of the input data. 
    the main loop that processes the blocks runs "numOfBlocks" times, and within this loop, 
    another loop runs 64 times (constant) for creating the message schedule.
    the rest of the operations inside the loop are constant time.
    therefore, the time complexity is (O(n)), where (n) is the size of the input data in bytes.*/

public:
    SHA256();

    string calculateHash(string s);
    /* this method calls "calculateDigest" , which has a time complexity of (O(n)), and then converts the resulting digest into a hex string.
    the conversion loop runs 32 times (for the 256 bits of the hash), which is constant. so it also has a time complexity of (O(n)). */
};