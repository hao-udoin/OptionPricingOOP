//Option class v1
//2 data member, "call/put type" and "strike price"

#include <string>

class Option {
    private:
        std::string typeCP; // call or put
        double strike;
    
    public:
        void setTypeCP(std::string type) {
            typeCP = type;
        }
        
        std::string getTypeCP() const {
            return typeCP;
        }

        void setStrike(double price) {
            strike = price;
        }

        double getStrike() const {
            return strike;
        }
};