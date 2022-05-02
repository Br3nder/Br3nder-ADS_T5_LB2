#include <iostream>
#include "encoding.h"

using namespace std;
int main() {

    string str = "You're the king? Well, I didn't vote for you.";
    br3nder::List<br3nder::pair<char, int>> list = br3nder::list_count_symbols(str);

    br3nder::pair<char, int> pair1('l', br3nder::count_symbols(str, 'l'));
    br3nder::pair<char, int>* pair2 = new br3nder::pair<char, int>('l', br3nder::count_symbols(str, 'l'));

    cout << "Start string: " << str << endl;
    string encode_str = encode(str).data1;
    tree<br3nder::pair<char, int>> key = encode(str).data2;
    cout << "\nencode: " << encode_str << endl;

    cout << "decode: " << decode(encode_str, &key) << endl;

    cout << "Table:\n";
    show_alphabet(str, &key);

	return 0;
}