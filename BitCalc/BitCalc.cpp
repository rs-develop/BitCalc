

#include <iostream>  //for std::cout
#include <iomanip>   //for std::setw
#include <algorithm> //for toupper

#include "BitCalc.h"

//----------------------------------------------------------------------------------------------------------
//                                      PUBLIC Getter
//----------------------------------------------------------------------------------------------------------
/**
 * @brief getter for the hexValue
 * Reads all bytes from list and return all as string.
 *
 * @return all hex values as string
 **/
std::string BitCalc::getHexValue()
{
    std::string hexValue;

    for (auto hexbyte : byteValueList_)
        hexValue += hexbyte.first;

    return hexValue;
}//end getHexValue

//----------------------------------------------------------------------------------------------------------
/**
 * @brief getter for calculating the dezValue
 * Calculates the dez value of the current bytes.
 *
 * @see getHexValue()
 * @return the dez value as string.
 **/
std::string BitCalc::getDezValue()
{
    std::string dezString;
    if ((getHexValue().size()/2) > 8)
        dezString = "OUT OF RANGE";
    else
        dezString = std::to_string(std::stoull(getHexValue(), nullptr, 16));
    return dezString;
}//end getDezValue

//----------------------------------------------------------------------------------------------------------
/**
 * @brief converts hex to asci
 * Converts all convertible
 **/
std::string BitCalc::getAsciiValue()
{
    std::string ascii;
    for (auto hexbyte : byteValueList_)
    {
        if (std::stoi(hexbyte.first, 0, 16) >= 33 && std::stoi(hexbyte.first, 0, 16) <= 126)
        {
            char sign = std::stoi("0x" + hexbyte.first, nullptr, 16);
            ascii += sign;
            ascii += " ";
        }//end if
        else
            ascii += "  ";
    }//end for

    return ascii;
}//end getAsciiValue

//----------------------------------------------------------------------------------------------------------
/**
 * @brief getBitStringList
 * Generates a list of bit strings. Each string will have 32 bits.
 **/
BitArrStrList BitCalc::getBitStringList()
{
    BitArrStrList bitStrList;
    unsigned int iter = byteValueList_.size();

    //Calculate iterations
    while ((iter % 4) != 0)
        iter++;

    //Build bit strings
    ByteValueList::iterator it = byteValueList_.begin();
    for (int i = iter; i > 0; i--)
    {
        std::string currBitString = "";

        //Get the bits from the bytes. If there are not all 8 bytes are used fill with 0
        if (i > byteValueList_.size())
            currBitString += "0000 0000";
        else
        {
            for (int bit = 0; bit < 8; bit++)
            {
                if (bit > 3 && bit < 5)
                    currBitString += " ";
                currBitString += static_cast<char>(it->second[bit]);
            }//end for fill bit strings
            it++;
        }//end else data in byteValueList
        bitStrList.emplace_back(currBitString);
    }//end for build bit strings

    return bitStrList;
}//end getBitStringList

//----------------------------------------------------------------------------------------------------------
/** @brief Returns the version of BitCalc
 *  @return version string
 */
std::string BitCalc::getBitCalcVersion()
{
    return BIT_CALC_VERSION;
}//end getBitCalcVersion


//----------------------------------------------------------------------------------------------------------
//                                      PUBLIC FUNCTIONS
//----------------------------------------------------------------------------------------------------------
/**
 * @brief inserter for the byte values
 * Main function for inserting the byte values into the BitCalc object. Reads the byte values and
 * add it to the byteValueList_ attribute. If th max byte value of MAX_SIZE bytes is reached: a exception
 * will be thrown.
 *
 * @param byteValue a one or a up to MAX_SIZE byte string of hex values
 * @see BitCalcMaxValueException
 **/
void BitCalc::insertByteValue(std::string byteValue)
{
    //Attributes
    std::vector<std::string> hexValBuffer;

    //be sure that all bytes are upper case
    std::transform(byteValue.begin(), byteValue.end(), byteValue.begin(), ::toupper);

    //Is byteValue odd?
    if (byteValue.size() % 2 != 0)
        byteValue.insert(byteValue.begin(), '0');

    //Check if max size reached
    if (((getHexValue().size() / 2) + (byteValue.size() / 2)) > BIT_CALC_MAX_BYTE_COUNT)
        throw BitCalcMaxValueException();

    //If size greater than two, split the argument
    if (byteValue.size() > 2)
    {
        for (int i = 0; i < byteValue.size(); i+=2)
            hexValBuffer.push_back(byteValue.substr(i, 2));
    }//end if
    //If the string is only one byte push it to the buffer
    else
        hexValBuffer.push_back(byteValue);

    //Split the hex bytes and push them to hexByte list
    for (auto currbyte : hexValBuffer)
    {
        BitArr bitArr;
        //Create Bit-Array
        for (int i = 0; i < 8; i++)
        {
            if (((std::stoi(currbyte, nullptr, 16) >> i) & 1) == 0x00)
                bitArr.insert(bitArr.begin(),'0');
            else
                bitArr.insert(bitArr.begin(),'1');
        }//end for

        //Insert the splittet argument to the global byteValueList
        byteValueList_.push_back(std::make_pair(currbyte, bitArr));

    }//end for create hexByte list

}//end insertByteValue

//----------------------------------------------------------------------------------------------------------
/**
 * @brief prints to std::out
 * Prints the bytes in the byteValueList_ to std::out as hex, dez, ascii and as bits.
 *
 * @see getHexValue
 * @see getDezValue
 */
void BitCalc::printAllToStdOut()
{
    //For printing bit masks
    BitArrStrList printArrStrList (getBitStringList().size()/4);

    int counter = 0;
    BitArrStrList::iterator it = printArrStrList.begin();
    for (auto currBitString : getBitStringList())
    {
        if (counter % 4 == 0 && counter != 0)
            it++;
        else if (counter != 0)
            *it += "  ";
        *it += currBitString;
        counter++;
    }//end for

    //Reset it for printing
    it = printArrStrList.begin();

    std::cout << "+----------------------------------------------+" << std::endl;
    std::cout << std::left << "| HEX-Value: " << std::setw(33) << getHexValue() << " |" << std::endl;
    std::cout << "+----------------------------------------------+" << std::endl;
    std::cout << std::left << "| ASCII:     " << std::setw(33) << getAsciiValue() << " |" << std::endl;
    std::cout << "+----------------------------------------------+" << std::endl;
    std::cout << std::left << "| DEC:       " << std::setw(20) << getDezValue() << "              |" << std::endl;
    std::cout << "+----------------------------------------------+" << std::endl;
    std::cout << std::left << "| Bytes:     " << std::setw(2) << (getHexValue().size()/2) << "                                |" << std::endl;
    std::cout << "+----------------------------------------------+" << std::endl;

    //Add Bit masks
    int posCounter = printArrStrList.size() * 2;
    for (int i = printArrStrList.size(); i > 0; i--)
    {
        //Whrite bit masks
        std::cout << "|  " << std::setw(42) << *it++ << "  |" << std::endl;
        //Whrite byte marks
        std::cout << std::left  << "|  " << std::setw(3) << (16 * (posCounter--))-1 << "                   ";
        std::cout << std::left  << std::setw(3) << (16 * (posCounter--))-1 << "              ";
        std::cout << std::right << std::setw(3) << (16 * posCounter)    << "  |" << std::endl;
    }//end for
    std::cout << "+----------------------------------------------+" << std::endl;

}//end printAllToStdOut

//----------------------------------------------------------------------------------------------------------
