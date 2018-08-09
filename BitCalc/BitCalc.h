#ifndef BITCALC_H
#define BITCALC_H

//----------------------------------------------------------------------------------------------------------

#include <vector>    //For BitArr
#include <string>    //For Strings
#include <list>      //For ByteValueList
#include <exception> //For BitCalcExceptions

//----------------------------------------------------------------------------------------------------------

//For testing
class BitCalc_Test;

//----------------------------------------------------------------------------------------------------------

using BitArr        = std::vector< unsigned char >;     /**< Type for storing the bit array */
using ByteValue     = std::pair< std::string, BitArr >; /**< Type for storing a hex byte and the bit arry of the hex byte */
using ByteValueList = std::list< ByteValue >;           /**< Type for storing a list of all ByteValues */
using BitArrStrList = std::vector < std::string >;      /**< Type for storing all bit strings in one list */

//----------------------------------------------------------------------------------------------------------

static const unsigned int BIT_CALC_MAX_BYTE_COUNT = 16; /**< max byte count */
static const std::string  BIT_CALC_VERSION = "BitCalc 1.0"; /**< BitCalc version */

//----------------------------------------------------------------------------------------------------------

class BitCalcBaseException : std::runtime_error /**< Base exception class of BitCalc */
{ public: BitCalcBaseException(std::string errMsg)
    : std::runtime_error(errMsg) {}
    using std::runtime_error::what; //tell the compiler we want both, the what from std and ours
    virtual const char* what() { return std::runtime_error::what(); }
};//end BitCalcBaseException
class BitCalcMaxValueException : public BitCalcBaseException /**< Exception for that the max byte value (MAX_SIZE) is reached */
{ public: BitCalcMaxValueException()
    : BitCalcBaseException("Error - max byte size is " + std::to_string(BIT_CALC_MAX_BYTE_COUNT) + " byte.") { }
};//end BitCalcMaxValueException
class BitCalcEmptyException : public BitCalcBaseException /**< Exception that are no values set */
{ public: BitCalcEmptyException ()
    : BitCalcBaseException("Error - no hex bytes set.") { }
};//end BitCalcEmptyException

//----------------------------------------------------------------------------------------------------------
/**
 * @class BitCalc
 * A class for calculating the dez value and the bit sheman of a hex byte or hex string of max 8 bytes.
 */
class BitCalc
{

    //Enable testing private member
    friend BitCalc_Test;

private:

    //Attributes
    ByteValueList byteValueList_; /**< In this attribute all bytes will be stored */

public:

    //Public getter
    std::string   getHexValue();
    std::string   getDezValue();
    std::string   getAsciiValue();
    BitArrStrList getBitStringList();
    std::string   getBitCalcVersion();


    void insertByteValue(std::string byteValue);
    void printAllToStdOut();

}; //end class BitCalc

//----------------------------------------------------------------------------------------------------------
#endif //BITCALC_H
