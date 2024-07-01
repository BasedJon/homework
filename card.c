#include <cs50.h>
#include <stdio.h>

int CardLength(void);
int FindDigitAtIndex(int index);
int CardType(void);
int LuhnCheck(void);
long cardNumber;
int cardLength;
int cardType;

int main(void)
{
    cardNumber = get_long("Number: ");
    cardLength = CardLength();
    cardType = FindDigitAtIndex(0);
    int luhmCheck = LuhnCheck();

    /* CODE FOR TESTING FUNCTIONS:
    printf("CARD NUMBER: %li\n", cardNumber);
    printf("CARD LENGTH: %i\n", cardLength);
    printf("CARD TYPE: %i\n", cardType);
    printf("LUHM CHECK: %i\n", luhmCheck);
    for (int i = 0; i < cardLength; i++)
    {
        int digitAtX = FindDigitAtIndex(i);
        printf("DIGIT AT X: %i\n", digitAtX);
    }
    */

    if (luhmCheck != 0)
    {
        switch (cardType)
        {
            case 3:
            printf("American Express\n");
            break;
            case 4:
            printf("Visa\n");
            break;
            case 5:
            printf("MasterCard\n");
            break;
            default:
            printf("INVALID\n");
            break;

        }
    }
    else
    printf("INVALID\n"); // I'm pretty sure I can remove this reprettion, but I'm too tired
}

int CardLength(void) // Find length by counting how many devisions by 10 are possible
{
    long tempCardNumber = cardNumber;
    int counter = 0;
    do
    {
        tempCardNumber /= 10;
        counter++;
    }
    while (tempCardNumber >= 1);

    return counter;
}

int FindDigitAtIndex(int index) // Find digit at a given index, the formula I ended up using is CARD_NUMBER % 10^(index) / 10^(index - 1)
{
    int power = cardLength - index;
    long tenToThePowerOfLength = 1;
    int findIndex;

    while (power >= 1)
    {
        tenToThePowerOfLength *= 10;
        power--;
    }
    findIndex = (cardNumber % tenToThePowerOfLength) / (tenToThePowerOfLength / 10);
    return findIndex;
}

int CardType(void) // Honestly, it's unnecessary and I could have done this check else where
{
    if (cardType > 5 || cardType < 3)
    {
        cardType = 0;
    }
    return cardType;
}

int LuhnCheck(void) // I think the way I did sums is easy to understand because of the index function, literally works like "string[index]"
{
    if (CardType() == 0)
        return 0;

    int firstSum = 0;
    int secondSum = 0;

    for (int i = cardLength - 2; i >= 0; i -= 2)
    {
        int multipleOf = FindDigitAtIndex(i) * 2;
        firstSum += (multipleOf % 10) + (multipleOf % 100 / 10);
    }

    for (int i = cardLength - 1; i >= 0; i -= 2)
    {
        secondSum += FindDigitAtIndex(i);
    }


    printf("Frist sum = %i\n", firstSum);
    printf("Second sum = %i\n", secondSum);

    if ((firstSum + secondSum) % 10 == 0)
        return cardType;
    else
    return 0;
}
