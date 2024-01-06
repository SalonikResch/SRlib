#include <iostream>
using namespace std;

// Define a generic class
class genericClass{
private:
    int x = 5;
public:
    int getX(){
        return x;
    }
};

// Define a more specific subclass
class specificClass : public genericClass{
private:
    int y = 2;
public:
    int getY(){
        return y;
    }
};


int main(){
    // Declare an instance
    specificClass obj;
    cout << obj.getX() << " and " << obj.getY() << endl;
    return 0;
}