#include "SHA-256Generator.h"

using namespace std;

uint32_t SHA256::rightRotate(uint32_t x, unsigned int shift)
{
    return (x >> shift) | (x << (32 - shift));
}

uint32_t SHA256::choice(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ ((~x) & z);
}

uint32_t SHA256::major(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t SHA256::bigSigma0(uint32_t x)
{
    uint32_t RotR2, RotR13, RotR22;
    RotR2 = rightRotate(x, 2);
    RotR13 = rightRotate(x, 13);
    RotR22 = rightRotate(x, 22);

    return RotR2 ^ RotR13 ^ RotR22;
}

uint32_t SHA256::bigSigma1(uint32_t x)
{
    uint32_t RotR6, RotR11, RotR25;
    RotR6 = rightRotate(x, 6);
    RotR11 = rightRotate(x, 11);
    RotR25 = rightRotate(x, 25);

    return RotR6 ^ RotR11 ^ RotR25;
}

uint32_t SHA256::sigma0(uint32_t x)
{
    uint32_t RotR7, RotR18, ShR3;
    RotR7 = rightRotate(x, 7);
    RotR18 = rightRotate(x, 18);
    ShR3 = x >> 3;

    return RotR7 ^ RotR18 ^ ShR3;
}

uint32_t SHA256::sigma1(uint32_t x)
{
    uint32_t RotR17, RotR19, ShR10;
    RotR17 = rightRotate(x, 17);
    RotR19 = rightRotate(x, 19);
    ShR10 = x >> 10;

    return RotR17 ^ RotR19 ^ ShR10;
}

uint8_t *SHA256::calculateDigest(const uint8_t *data, uint64_t dataSizeByte)
{
    uint64_t dataSizeBits;
    uint32_t numOfBlocks;
    uint8_t **dataBlock;

    // schedule array
    uint32_t W[64];

    // block hash, temporary hash in compression loop, and auxiliary temporary variable to calculate temporary hash
    uint32_t blockH[8], tempH[8], temp1, temp2;

    // hashed data
    uint8_t *digest;

    // calculating the data size in bits
    dataSizeBits = dataSizeByte * 8;

    // calculating the quantity of 512bits data blocks
    numOfBlocks = ceil(static_cast<double>(dataSizeByte) / 64);

    // allocating 512bits blocks
    dataBlock = new uint8_t *[numOfBlocks];
    for (uint32_t i = 0; i < numOfBlocks; i++)
        dataBlock[i] = new uint8_t[64];

    // pre-processing data into blocks
    for (uint32_t block = 0; block < numOfBlocks; block++)
    {
        // if it's in the last block
        if (block == numOfBlocks - 1)
        {
            // copy the last bytes from data
            for (uint32_t byteOnBlock = 0; byteOnBlock < (dataSizeByte % 64); byteOnBlock++)
                dataBlock[block][byteOnBlock] = data[(block * 64) + byteOnBlock];

            // append bit 1 at the end of data
            dataBlock[block][dataSizeByte % 64] = 0x80;

            // pad with 0's until data is multiple of (512 - 64) = 448
            for (uint32_t byteOnBlock = (dataSizeByte % 64) + 1; byteOnBlock < 56; byteOnBlock++)
                dataBlock[block][byteOnBlock] = 0x0;

            // append 64bits of data size value in bits as big-endian
            dataBlock[block][56] = (dataSizeBits >> 56) & 0x00000000000000FF;
            dataBlock[block][57] = (dataSizeBits >> 48) & 0x00000000000000FF;
            dataBlock[block][58] = (dataSizeBits >> 40) & 0x00000000000000FF;
            dataBlock[block][59] = (dataSizeBits >> 32) & 0x00000000000000FF;
            dataBlock[block][60] = (dataSizeBits >> 24) & 0x00000000000000FF;
            dataBlock[block][61] = (dataSizeBits >> 16) & 0x00000000000000FF;
            dataBlock[block][62] = (dataSizeBits >> 8) & 0x00000000000000FF;
            dataBlock[block][63] = dataSizeBits & 0x00000000000000FF;
        }
        else
        {
            // copy bytes from data to block
            for (uint32_t byteOnBlock = 0; byteOnBlock < 64; byteOnBlock++)
                dataBlock[block][byteOnBlock] = data[(block * 64) + byteOnBlock];
        }
    }

    // initialize the current hash table
    blockH[0] = H[0];
    blockH[1] = H[1];
    blockH[2] = H[2];
    blockH[3] = H[3];
    blockH[4] = H[4];
    blockH[5] = H[5];
    blockH[6] = H[6];
    blockH[7] = H[7];

    // create message schedule loop 512bit block
    for (uint32_t block = 0; block < numOfBlocks; block++)
    {
        // divide 512bits block into 16 32bit words [w0 to w15]
        for (uint32_t byteOnBlock = 0; byteOnBlock < 64; byteOnBlock += 4)
        {
            W[byteOnBlock / 4] = (((uint32_t)dataBlock[block][byteOnBlock]) << 24) |
                                 (((uint32_t)dataBlock[block][byteOnBlock + 1]) << 16) |
                                 (((uint32_t)dataBlock[block][byteOnBlock + 2]) << 8) |
                                 ((uint32_t)dataBlock[block][byteOnBlock + 3]);
        }
        // add more 48 32bit words [w16 to w63]
        for (uint32_t i = 16; i < 64; i++)
            W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];

        // initialize enumerators a, b, c, d, e, f, g, h to blockH[0...7] respectively
        tempH[a] = blockH[0];
        tempH[b] = blockH[1];
        tempH[c] = blockH[2];
        tempH[d] = blockH[3];
        tempH[e] = blockH[4];
        tempH[f] = blockH[5];
        tempH[g] = blockH[6];
        tempH[h] = blockH[7];

        // compression of the message schedule (W[0...63])
        for (uint32_t i = 0; i < 64; i++)
        {
            temp1 = tempH[h] + bigSigma1(tempH[e]) + choice(tempH[e], tempH[f], tempH[g]) + K[i] + W[i];
            temp2 = bigSigma0(tempH[a]) + major(tempH[a], tempH[b], tempH[c]);

            tempH[h] = tempH[g];
            tempH[g] = tempH[f];
            tempH[f] = tempH[e];
            tempH[e] = tempH[d] + temp1;
            tempH[d] = tempH[c];
            tempH[c] = tempH[b];
            tempH[b] = tempH[a];
            tempH[a] = temp1 + temp2;
        }
        // update hash values for the current block
        blockH[0] += tempH[a];
        blockH[1] += tempH[b];
        blockH[2] += tempH[c];
        blockH[3] += tempH[d];
        blockH[4] += tempH[e];
        blockH[5] += tempH[f];
        blockH[6] += tempH[g];
        blockH[7] += tempH[h];
    }
    // deallocate dataBlock
    for (uint32_t i = 0; i < numOfBlocks; ++i)
        delete[] dataBlock[i];

    delete[] dataBlock;

    // allocate memory for digest pointer
    digest = new uint8_t[32];

    // prepare digest for return
    for (uint32_t i = 0; i < 32; i += 4)
    {
        digest[i] = (uint8_t)((blockH[i / 4] >> 24) & 0x000000FF);
        digest[i + 1] = (uint8_t)((blockH[i / 4] >> 16) & 0x000000FF);
        digest[i + 2] = (uint8_t)((blockH[i / 4] >> 8) & 0x000000FF);
        digest[i + 3] = (uint8_t)(blockH[i / 4] & 0x000000FF);
    }

    return digest;
}

// Implement the rest of the functions here...

SHA256::SHA256() : H{0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19},
                   K{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
                     0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                     0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
                     0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                     0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
                     0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                     0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                     0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
                     0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                     0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
                     0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                     0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
                     0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                     0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                     0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2}
{}

string SHA256::calculateHash(string s)
{
    uint8_t *digest, *data;
    uint64_t dataSizeByte;

    // convert string to uint8_t* and uint64_t
    data = reinterpret_cast<uint8_t *>(const_cast<char *>(s.c_str()));
    dataSizeByte = static_cast<uint64_t>(s.size());

    digest = calculateDigest(data, dataSizeByte);

    // convert the hash to a string
    stringstream hash;
    for (int i = 0; i < 32; ++i)
    {
        hash << hex << setw(2) << setfill('0') << static_cast<int>(digest[i]);
    }

    // deallocate memory
    delete[] digest;

    // return the hash as a string
    return hash.str();
}