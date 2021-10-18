// Stopwatch

#include <chrono>
#include <iostream>
using namespace std;

/*snippet-begin*/
using namespace chrono;
struct stopwatch {
    typedef time_point<high_resolution_clock> tp;
    tp last_tick;
    bool notock;
    stopwatch() : notock(false) { tick(); }
    stopwatch(int) : notock(true) { tick(); }
    ~stopwatch() { if (!notock) tock(); }

    void tick() {
        last_tick = high_resolution_clock::now();
    }

    void tock() const {
        duration<double> dur = high_resolution_clock::now() - last_tick;
        cerr << "Time (s): " << dur.count() << '\n';
    }
};
/*snippet-end*/

int main() {
    {
        stopwatch(0);
    }
}
