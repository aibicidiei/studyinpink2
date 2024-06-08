#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
const Position Position::npos = Position{ -1, -1 };
const Position Sherlock::npos(-1, -1);
const Position Watson::npos = Position(-1, -1);
const Position Criminal::directions[NUM_DIRECTIONS] = {
    Position(-1, 0),
    Position(0, -1),
    Position(1, 0),
    Position(0, 1)
};
const Position Criminal::npos(-1, -1);
int calculateDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    };
string createItem(int i, int j) {
    int p = i * j;
    int s = calculateDigitSum(p);
    while (s >= 10) {
        s = calculateDigitSum(s);
    }

    int t = (i * 11 + j) % 4;

    if (s >= 0 && s <= 1) {
        return "MagicBook";
    }
    else if (s >= 2 && s <= 3) {
        return "EnergyDrink";
    }
    else if (s >= 4 && s <= 5) {
        return "FirstAid";
    }
    else if (s >= 6 && s <= 7) {
        return "ExcemptionCard";
    }
    else {
        switch (t) {
        case 0:
            return "PassingCard: RobotS";
        case 1:
            return "PassingCard: RobotC";
        case 2:
            return "PassingCard: RobotSW";
        default:
            return "PassingCard: all";
        }
    }
}
void giftExchange(SherlockBag* sherlockBag, WatsonBag* watsonBag) {

    BaseItem* passingCard = sherlockBag->get(PassingCardType);
    while (passingCard) {

        watsonBag->insert(passingCard);
        passingCard = sherlockBag->get(PassingCardType);
    }
    BaseItem* excemptionCard = watsonBag->get(ExceptionCardType);
    while (excemptionCard) {
        excemptionCard = watsonBag->get(ExceptionCardType);
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////


