// 7/4
class Hamming
{
    static int Encode(int data) {
        int p1 = (data >> 0) & 1;
        int p2 = (data >> 1) & 1;
        int d3 = (data >> 2) & 1;
        int p3 = (data >> 3) & 1;
        int d5 = (data >> 4) & 1;
        int d6 = (data >> 5) & 1;
        int d7 = (data >> 6) & 1;

        int p1Parity = p1 ^ p2 ^ d3 ^ d5 ^ d7;
        int p2Parity = p1 ^ p3 ^ d3 ^ d6 ^ d7;
        int p3Parity = p2 ^ p3 ^ d5 ^ d6 ^ d7;

        int encodedCodeword = (p1Parity << 0) | (p2Parity << 1) | (d3 << 2) | (p3Parity << 3) | (d5 << 4) | (d6 << 5) | (d7 << 6);

        return encodedCodeword;
        }

    static int Decode(int codeword) {
        int p1 = (codeword >> 0) & 1;
        int p2 = (codeword >> 1) & 1;
        int d3 = (codeword >> 2) & 1;
        int p3 = (codeword >> 3) & 1;
        int d5 = (codeword >> 4) & 1;
        int d6 = (codeword >> 5) & 1;
        int d7 = (codeword >> 6) & 1;

        int s1 = p1 ^ p2 ^ d3 ^ d5 ^ d7;
        int s2 = p1 ^ p3 ^ d3 ^ d6 ^ d7;
        int s3 = p2 ^ p3 ^ d5 ^ d6 ^ d7;

        int errorPos = (s3 << 2) | (s2 << 1) | s1;

        // Correct error
        if (errorPos != 0)
        {
            codeword ^= (1 << (7 - errorPos)); // Flip the error bit
        }

        // Extract original data
        int decodedData = (d3 << 0) | (d5 << 1) | (d6 << 2) | (d7 << 3);

        return decodedData;
        }
        
    static array <int> SplitIntToBlocks(int value) {
        array <int> blocks;
        
        for (int i = 0; i < 4; i++)
        {
            blocks[i] = (value >> (i * 256)) & 0xFFFFFFFF;
        }
        
        return blocks;
        }

    static void Main() {
        // Simulated 1024-bit message (4 blocks of 256 bits each)
        int originalInt = 0x1101101101010101001100110011001111111100001111000010101010101010011;

        array <int> splitBlocks = SplitIntToBlocks(originalInt);

        Print("Original 1024-bit Int: " + originalInt);
        Print("Split Blocks:" + splitBlocks);

        array <int> encodedCodewords;

        // Encode the message
        foreach (int block : splitBlocks)
        {
           encodedCodewords.Insert(Encode(block));
        }

        // Simulate flipping a bit in one of the codewords
        encodedCodewords[2] = encodedCodewords[2] ^ (1 << 13);

        array <int> decodedData;

        // Decode the message
        foreach (int encodedBlock : encodedCodewords)
        {
            decodedData.Insert(Decode(encodedBlock));
        }


        // Print the original encoded codewords and the decoded data
        Print("Original Encoded Codewords:");
        foreach (int codeword : encodedCodewords)
        {
            Print(codeword);
        }

        Print("Decoded Data after Simulated Bit Flip:");
        foreach (int data : decodedData)
        {
            Print(data);
        }
     }




}