#include <cs50.h>
#include <stdio.h>
#include <string.h>

string validateCardIssuer(long cardNumber);
bool validateCheckSum(long cardNumber);

int main(void)
{
    long cardNumber;
    // Capture User Input
    do
    {
        cardNumber = get_long("Please input your credit card number: ");
    }
    while (!validateCheckSum(cardNumber) && !validateCardIssuer(cardNumber));
    printf("%s\n", validateCardIssuer(cardNumber));
}

/**
 * Check Card Issuer by credit card
 * @param cardNumber the credit card number
 * @return the card type or invalid string
 */

string validateCardIssuer(long cardNumber)
{
    // Calculate the no of digits of the card Number
    int noOfDigits = 0;
    long digitTemp = cardNumber;
    while (digitTemp != 0)
    {
        digitTemp = digitTemp / 10;
        noOfDigits++;
    }

    // check Visa card numbers that start with 4 with 13-digits
    if (noOfDigits == 13)
    {
        // reduce the card Number to single digit
        long leadingDigits = cardNumber;
        while (leadingDigits > 10)
        {
            leadingDigits /= 10;
        }
        if (leadingDigits == 4)
        {
            if (validateCheckSum(cardNumber))
            {
                return "VISA";
            }
        }
        return "INVALID";
    }
    else if (noOfDigits == 15)
    {
        // All American Express numbers start with 34 or 37, 15-digit numbers
        // reduce the card Number to double digit
        long leadingDigits = cardNumber;
        while (leadingDigits > 100)
        {
            leadingDigits /= 10;
        }
        if (leadingDigits == 34 || leadingDigits == 37)
        {
            if (validateCheckSum(cardNumber))
            {
                return "AMEX";
            }
        }
        return "INVALID";
    }
    else if (noOfDigits == 16)
    {
        // MasterCard numbers start with 51, 52, 53, 54, or 55, 16-digit numbers
        // reduce the card Number to double digit
        long leadingDigits = cardNumber;
        while (leadingDigits > 100)
        {
            leadingDigits /= 10;
        }
        if (leadingDigits >= 51 && leadingDigits <= 55)
        {
            if (validateCheckSum(cardNumber))
            {
                return "MASTERCARD";
            }
        }
        // check Visa card numbers that start with 4 with 16-digits
        // reduce the card Number to single digit
        while (leadingDigits > 10)
        {
            leadingDigits /= 10;
        }
        if (leadingDigits == 4)
        {
            if (validateCheckSum(cardNumber))
            {
                return "VISA";
            }
        }
        return "INVALID";
    }
    else
    {
        return "INVALID";
    }
}


/**
 * Check Sum by credit card
 * @param cardNumber the credit card number
 * @return true if the card's checkSum is valid, other-wise false
 */
bool validateCheckSum(long cardNumber)
{
    // get the total digits of the cardNumber
    int noOfDigits = 0;
    long digitTemp = cardNumber;
    while (digitTemp != 0)
    {
        digitTemp = digitTemp / 10;
        noOfDigits++;
    }

    int evenSum = 0;
    int oddSum = 0;
    int currentDigit = 0;

    for (int i = 1; i <= noOfDigits; i++)
    {
        // Getting the current digits from the card number, from the last to the first
        // get the current digit by the remainder of it to 10
        currentDigit = cardNumber % 10;
        // move the card Number forward by one digit
        cardNumber /= 10;

        // Debugger
        // printf("%dth Current Digit: %d\n",i,currentDigit);
        if (i % 2 == 0)
        {
            // times the even digits by 2, then add the digits to evenSum
            // two conditions
            // if the product is less than 10 > add to the sum
            int evenProduct = currentDigit * 2;
            if (evenProduct < 10)
            {
                evenSum += evenProduct;
            }
            else
            {
                // if the product is >10, modulus it and add it with the remainder
                evenSum = evenSum + (evenProduct) % 10 + (evenProduct) / 10;
            }
            // Debugger
            // printf("%dth Even Sum: %d\n",i,evenSum);
        }
        else
        {
            // add the odd digit to the sum of odd directly
            oddSum = oddSum + currentDigit;

            // Debugger
            // printf("%dth Odd Sum: %d\n",i,oddSum);
        }
    }

    // Debugger
    // printf("Even Sum: %d\n",evenSum);
    // printf("Odd Sum: %d\n",oddSum);

    // add both even sum and odd sum, check if the last digit is 0 by %10
    int checkSum = evenSum + oddSum;
    if (checkSum % 10 == 0)
    {
        // printf("True\n");
        return true;
    }
    // printf("False\n");
    return false;
}
