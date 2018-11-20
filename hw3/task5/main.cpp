#include <array>
#include <bitset>
#include <iostream>

// Lookup table for one round of DES
static constexpr const auto lookup_table = std::array<std::array<const unsigned char, 16>, 4>{
    std::array<const unsigned char, 16>{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    std::array<const unsigned char, 16>{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    std::array<const unsigned char, 16>{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    std::array<const unsigned char, 16>{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

// S Box takes a 48 bit input to a 32 bit output using a looup table
std::bitset<32> s_box(std::bitset<48> input)
{
    auto output = std::bitset<32>();

    // 6 * 8 = 48
    for (int i = 0; i < 8; i++)
    {
        int start = i * 6;

        // Get row index
        auto row = std::bitset<2>();
        row[0] = input[start];
        row[1] = input[start + 5];

        // Get column index
        auto column = std::bitset<4>();
        for (int j = 0; j < 4; j++)
        {
            column[j] = input[start + j + 1];
        }

        // Lookup new value based on column and row indeces
        auto val = std::bitset<4>(lookup_table[row.to_ulong()][column.to_ulong()]);
        int offset = i * 4;
        for (int j = 0; j < 4; j++)
        {
            output[j + offset] = val[j];
        }
    }

    return output;
}

// DES mangler function
uint64_t mangler(std::uint64_t block, std::bitset<48> round_key)
{
    auto right = std::bitset<32>(block);
    auto left = std::bitset<32>(block >> 32);

    auto expanded_right = std::bitset<48>();
    expanded_right[0] = right[32];
    expanded_right[1] = right[1];
    expanded_right[2] = right[2];
    expanded_right[3] = right[3];
    expanded_right[4] = right[4];
    expanded_right[5] = right[5];
    expanded_right[6] = right[4];
    expanded_right[7] = right[5];
    expanded_right[8] = right[6];
    expanded_right[9] = right[7];
    expanded_right[10] = right[8];
    expanded_right[11] = right[9];
    expanded_right[12] = right[8];
    expanded_right[13] = right[9];
    expanded_right[14] = right[10];
    expanded_right[15] = right[11];
    expanded_right[16] = right[12];
    expanded_right[17] = right[13];
    expanded_right[18] = right[12];
    expanded_right[19] = right[13];
    expanded_right[20] = right[14];
    expanded_right[21] = right[15];
    expanded_right[22] = right[16];
    expanded_right[23] = right[17];
    expanded_right[24] = right[16];
    expanded_right[25] = right[17];
    expanded_right[26] = right[18];
    expanded_right[27] = right[19];
    expanded_right[28] = right[20];
    expanded_right[29] = right[21];
    expanded_right[30] = right[20];
    expanded_right[31] = right[21];
    expanded_right[32] = right[22];
    expanded_right[33] = right[23];
    expanded_right[34] = right[24];
    expanded_right[35] = right[25];
    expanded_right[36] = right[24];
    expanded_right[37] = right[25];
    expanded_right[38] = right[26];
    expanded_right[39] = right[27];
    expanded_right[40] = right[28];
    expanded_right[41] = right[29];
    expanded_right[42] = right[28];
    expanded_right[43] = right[29];
    expanded_right[44] = right[30];
    expanded_right[45] = right[31];
    expanded_right[46] = right[32];
    expanded_right[47] = right[1];

    // Convert 48 bits to 32 bits
    std::bitset<32> output = s_box(expanded_right ^ round_key);
    // put halves back together to form 64 bit output
    return right.to_ullong() << 32 | (left.to_ulong() ^ output.to_ulong());
}

int main(int argc, const char **argv)
{
    static constexpr const auto plaintext = 0xDEADBEEFDEADBEEFULL;
    static constexpr const auto round_key = std::bitset<48>(0x123456789abcULL);

    uint64_t output = mangler(plaintext, round_key);

    std::cout << "Plaintext: " << plaintext << '\n';
    std::cout << "Cipertext: " << output << '\n';

    return 0;
}