
#include <string>
#include <algorithm>

#include <gtest/gtest.h>

#include "BitCalc.h"


//----------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------
/**
 * Test class
 */
class BitCalc_Test : public ::testing::Test
{
protected:
    
    /* Setup before test case */
    static void SetUpTestCase()
    {
    }
    
    /*Tear down after test case */
    static void TearDownTestCase()
    {
    }
    
    /* Setup before every test */
    virtual void SetUp()
    {
    }
    
    /*Tear down after every test */
    virtual void TearDown()
    {
    }
    
    //---------------------------------------------------------------------------------#
    
    /** Returns the byteValueList */
    ByteValueList get_byteValueList(BitCalc& srcObj) const
    {
        return srcObj.byteValueList_;
    }//end get_varIntValue
    
    //---------------------------------------------------------------------------------#
    
    /** Returns the bitArr of a hexValue (if exists) of a BitCalc Object */
    BitArr get_bitArr(BitCalc& srcObj, const std::string hexValue) const
    {
        BitArr returnValue;
        for (const auto byte : srcObj.byteValueList_)
        {
            if (byte.first == hexValue)
            {
                returnValue = byte.second;
                break;
            }//end if
        }//end for varint
        
        return returnValue;
    }//end get_bitArr
    
    //---------------------------------------------------------------------------------#
    
    /** Helper function to compare bitArrays */
    bool compare_bitArr(const BitArr& lhs, const BitArr& rhs) const
    {
        bool returnValue = true;
        for (int i = 0; i < 8; i++)
        {
            if (lhs[i] != rhs[i])
            {
                returnValue = false;
                break;
            }//end for
        }//end for
        return returnValue;
    }//end compare_byteArr
    
    //---------------------------------------------------------------------------------#
    
    /** Helper function for printing bits to gtest out */
    void printBits(BitArr& bits, std::string byte)
    {
        std::cout << "Value: " << byte << "; Bits: " << bits[0]
                  << " " << bits[1] << " "   << bits[2]
                  << " " << bits[3] << " | " << bits[4]
                  << " " << bits[5] << " "   << bits[6]
                  << " " << bits[7] << std::endl;
    }//end print
    
};//end

//----------------------------------------------------------------------------------------------------------
/* Tests if the the Byte-Value "D0 is properly set and shown as bit secquence" */
TEST_F(BitCalc_Test, insert_value_D0)
{
    //Testvalues
    static std::string testHexValue = "D0";
    BitArr testByteValue_D0 = {'1', '1', '0', '1', '0', '0', '0', '0'};
    
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    //Get the value pair of the ByteShifter-Class
    ByteValue value = *get_byteValueList(calc).begin();
    
    printBits(value.second, value.first);
    
    EXPECT_TRUE(value.first.size() > 0);
    EXPECT_TRUE(value.second.size() == 8);
    EXPECT_EQ(testHexValue, value.first);
    EXPECT_TRUE(compare_bitArr(testByteValue_D0, value.second));
    
}//end insert_one_hex_value

//----------------------------------------------------------------------------------------------------------
/* Tests if the the Byte-Value "0D" is properly set and shown as bit secquence" */
TEST_F(BitCalc_Test, insert_value_D)
{
    //Testvalues
    static std::string testHexValue = "D";
    static BitArr testByteValue_0D = {'0', '0', '0', '0', '1', '1', '0', '1'};
    
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    //Get the value pair of the ByteShifter-Class
    ByteValue value = *get_byteValueList(calc).begin();
    
    printBits(value.second, value.first);
    
    EXPECT_TRUE(value.first.size() > 0);
    EXPECT_TRUE(value.second.size() == 8);
    EXPECT_EQ("0D", value.first);
    EXPECT_TRUE(compare_bitArr(testByteValue_0D, value.second));
}//endinsert_value_D

//----------------------------------------------------------------------------------------------------------
/* Tests if the the two Byte-Values "0D05" is properly set and shown as bit secquence" */
TEST_F(BitCalc_Test, insert_value_D05)
{
    //Testvalues
    static std::string testHexValue = "D05";
    static BitArr testByteValue_0D = {'0', '0', '0', '0', '1', '1', '0', '1'};
    static BitArr testByteValue_05 = {'0', '0', '0', '0', '0', '1', '0', '1'};
    
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    //Expect two values
    EXPECT_EQ(2, get_byteValueList(calc).size());
    
    //Get Values
    ByteValue val_0D = *get_byteValueList(calc).begin();
    printBits(val_0D.second, val_0D.first);
    ByteValue val_05 = *get_byteValueList(calc).rbegin();
    printBits(val_05.second, val_05.first);
    
    //Test the first value
    EXPECT_TRUE(val_0D.first.size() > 0); //Is there any data
    EXPECT_EQ(8, val_0D.second.size()); //Is the Byte-Array size 8-Bit
    EXPECT_EQ("0D", val_0D.first); //Check the Byte-Value
    EXPECT_TRUE(compare_bitArr(testByteValue_0D, val_0D.second));
    
    //Test the second value
    EXPECT_TRUE(val_05.first.size() > 0); //Is there any data
    EXPECT_EQ(8, val_05.second.size()); //Is the Byte-Array size 8-Bit
    EXPECT_EQ("05", val_05.first); //Check the Byte-Value
    EXPECT_TRUE(compare_bitArr(testByteValue_05, val_05.second));
}//end insert_value_D05

//----------------------------------------------------------------------------------------------------------
/* Tests if a byte string greater than 8 byte will be inserted, the getDezString function will be return "OUT OF RANGE"*/
TEST_F(BitCalc_Test, dez_out_of_range_test)
{
    //Testvalues
    static std::string testHexValue = "FF";
    
    BitCalc calc;
    //Fill
    for (int i = 0; i < 9; i++)
        calc.insertByteValue(testHexValue);
    
    EXPECT_EQ("OUT OF RANGE", calc.getDezValue());
}//end dez_out_of_range_test

//----------------------------------------------------------------------------------------------------------
/* Tests if the max value of BIT_CALC_MAX_BYTE_COUNT 0xFF is properly set and shown as bit secquence" */
TEST_F(BitCalc_Test, insert_max_byte_value)
{
    //Testvalues
    static std::string testHexValue = "FF";
    
    BitCalc calc;
    //Fill
    for (int i = 0; i < BIT_CALC_MAX_BYTE_COUNT; i++)
        calc.insertByteValue(testHexValue);
    
    EXPECT_EQ(BIT_CALC_MAX_BYTE_COUNT, get_byteValueList(calc).size());
    
    //Check all values
    for (auto currByte : get_byteValueList(calc))
    {
        printBits(currByte.second, currByte.first);
        EXPECT_EQ(testHexValue, currByte.first);
        EXPECT_TRUE(compare_bitArr(get_bitArr(calc, testHexValue), currByte.second));
    }//end for
    
}//end insert_max_byte_value

//----------------------------------------------------------------------------------------------------------
/* Expect a max value reched exception if the byte string is greater then BIT_CALC_MAX_BYTE_COUNT */
TEST_F(BitCalc_Test, expect_BitCalcMaxValueException_test)
{
    //Testvalues
    static std::string testHexValue = "FF";
    
    BitCalc calc;
    //Fill
    for (int i = 0; i < BIT_CALC_MAX_BYTE_COUNT; i++)
        calc.insertByteValue(testHexValue);
    EXPECT_THROW(calc.insertByteValue(testHexValue), BitCalcMaxValueException);
}//end expect_BitCalcMaxValueException_test

//----------------------------------------------------------------------------------------------------------
/* Test if the hex value 0xA1E4A7899955AA will be printet */
TEST_F(BitCalc_Test, print_test_0xA1E4A7899955AA)
{
    //Testvalues
    static std::string testHexValue = "A1E4A7899955AA";
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    calc.printAllToStdOut();
}//end print_test_0xA1E4A7899955AA
    
//----------------------------------------------------------------------------------------------------------
/* Test if the max value will printed as it should */
TEST_F(BitCalc_Test, print_test_max_value)
{
    //Testvalues
    static std::string testHexValue = "FF";
    
    BitCalc calc;
    //Fill
    for (int i = 0; i < BIT_CALC_MAX_BYTE_COUNT; i++)
        calc.insertByteValue(testHexValue);
    
    calc.printAllToStdOut();
    
}//end print_test_max_value

//----------------------------------------------------------------------------------------------------------
/* Test if the min value will printed as it should */
TEST_F(BitCalc_Test, print_test_min_value)
{
    //Testvalues
    static std::string testHexValue = "1";
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    calc.printAllToStdOut();
    
}//end print_test_min_value

//----------------------------------------------------------------------------------------------------------
/* Test if the ascii value will printed as it should */
TEST_F(BitCalc_Test, print_test_ascii)
{
    //Testvalues
    static std::string testHexValue = "48616C6C6F";
    BitCalc calc;
    calc.insertByteValue(testHexValue);
    
    calc.printAllToStdOut();
    
}//end print_test_ascii
//----------------------------------------------------------------------------------------------------------
