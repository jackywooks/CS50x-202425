from cs50 import get_string


def main():
    textInput = get_string("Text: ")
    print(checkReadablity(textInput))


def checkReadablity(textInput):
    letters = countLetters(textInput)
    words = countWords(textInput)
    sentances = countSentances(textInput)
    L = letters/words * 100
    S = sentances/words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        return "Before Grade 1"
    elif index <= 16:
        return f"Grade {index}"
    else:
        return "Grade 16+"


def countLetters(textInput):
    return len("".join(filter(str.isalpha, textInput)))


def countWords(textInput):
    return len(textInput.split(" "))


def countSentances(textInput):
    return textInput.count("!") + textInput.count("?") + textInput.count(".")


main()
