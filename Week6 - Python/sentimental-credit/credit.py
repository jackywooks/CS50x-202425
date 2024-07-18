from cs50 import get_string
import re


def main():
    while (True):
        cardNumber = get_string("Please input your credit card no.: ")
        try:
            if (validateCardLenth(cardNumber) == True and validateCheckSum(cardNumber) == True):
                print(validateCardIssuer(cardNumber))
            else:
                print("INVALID")
            break
        except ValueError:
            pass


def validateCardIssuer(cardNumber):
    if (re.match(r"^4(\d{12}|\d{15})$", cardNumber)):
        return "VISA"
    elif (re.match(r"^(34|37)\d{13}$", cardNumber)):
        return "AMEX"
    elif (re.match(r"^(51|52|53|54|55)\d{14}$", cardNumber)):
        return "MASTERCARD"
    else:
        return "INVALID"


def validateCardLenth(cardNumber):
    if (re.match("^(\\d{13}|\\d{15}|\\d{16})$", cardNumber)):
        return True
    return False


def validateCheckSum(cardNumber):
    checkSum = 0
    # Traverse the cardNumber from right to left, and start from 1
    for index, value in enumerate(reversed(cardNumber), start=1):
        if index % 2 == 0:
            evenValue = int(value) * 2
            if (evenValue < 10):
                checkSum += evenValue
            else:
                checkSum += int(evenValue / 10) + evenValue % 10
        else:
            checkSum += int(value)
    if (checkSum % 10 == 0):
        return True
    return False


main()
