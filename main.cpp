#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream inFile;
    ofstream outFile;
    char byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0;
    char red5 = 0, green5 = 0, blue5 = 0;
    uint8_t outByte = 0x0, outByte2 = 0x0;
    for (int i=1;i<argc;i++){
        inFile.open(argv[i], std::fstream::binary);
        char output[5000];
        strncpy(output, argv[i], strlen(argv[i])-5);
        output[strlen(argv[i])-5] = '\0';
        cout << "Input filename: " << argv[i] << endl;
        cout << "Output filename: " << output << endl;
        outFile.open(output, std::fstream::binary);
        int pixelNumber = 1;
        if (inFile.is_open()) {
            cout << "File " << argv[i] << " opened for processing." << endl;
            while (!inFile.eof()) {
                byte1 = 0;
                byte2 = 0;
                byte3 = 0;
                byte4 = 0;
                inFile.read(&byte1, 1);
                inFile.read(&byte2, 1);
                inFile.read(&byte3, 1);
                //inFile.read(&byte4, 1);
                red5 = byte1 >> 3;
                red5 = red5 & 0b00011111;
                green5 = byte2 >> 3;
                green5 = green5 & 0b00011111;
                blue5 = byte3 >> 3;
                blue5 = blue5 & 0b00011111;
                outByte = 0;
                outByte2 = 0;
                outByte = outByte | red5;
                outByte = outByte | green5 << 5;
                outByte2 = outByte2 | green5 >> 3;
                outByte2 = outByte2 | blue5 << 2;

                outFile.write(reinterpret_cast<const char *>(&outByte), sizeof (outByte));
                outFile.write(reinterpret_cast<const char *>(&outByte2), sizeof (outByte2));
                pixelNumber++;
            }
            cout << "Processing of file " << argv[i] << " completed." << endl;
            cout << "Output filename: " << output << " completed." << endl;
        } else {
            cout << "Error opening file " << argv[i] << endl;
        }
    }
        return 0;
    }
