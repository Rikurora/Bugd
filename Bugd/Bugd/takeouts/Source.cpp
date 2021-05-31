/**

class Exception {

public:
    Exception(const string& msg) : msg_(msg) {}
    ~Exception() {}

    string getMessage() const { return(msg_); }
private:
    string msg_;
};

void f() {
    throw(Exception("Mr. Sulu"));
}

int main() {

    try {
        f();
    }
    catch (Exception& e) {
        cout << "You threw an exception: " << e.getMessage() << endl;
    }
}**/


/* -More streamlined debug function, does not work
#ifdef _DEBUG
    #define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(...))
#else
    #define GLCall(x) x
#endif
*/