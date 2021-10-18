// Random number generation

#include <random>
#include <chrono>
using namespace std;

using ll = long long;

/*snippet-begin*/
mt19937 eng(chrono::high_resolution_clock::now().time_since_epoch().count());
using uid = uniform_int_distribution<ll>;
using urd = uniform_real_distribution<double>;
/*snippet-end*/

int main() {
    int x = uid(0, 5)(eng);
    return !(0 <= x && x <= 5);
}
