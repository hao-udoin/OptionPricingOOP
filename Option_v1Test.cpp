#include <iostream>
#include "Option_v1.h"

using namespace std;

int main() {
    Option option1;

    option1.setTypeCP("call");
    cout << "Option 1 is a " << option1.getTypeCP() << endl;

    option1.setStrike(100);
    cout << "Option 1 has strike price " << option1.getStrike() << endl;
};