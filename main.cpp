#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

static const string dialmap[] = { "*", "abc", "def", "ghi", "jkl", "mno", "pqrs","tuv","wxyz"};


void permute( set<string> &results, const string& num) {
    for( unsigned i = 0; i < num.length(); i++) {  // index into phone num
        if (results.empty() )
            results.insert("");

        set<string> newRes;

        for (  set<string>::iterator it = results.begin(); it != results.end(); ++it ) {
            string letters = dialmap[num[i]-'0'];

            for ( string::iterator sit = letters.begin(); sit != letters.end(); ++sit ) {
                string news = *it;
                news.push_back(*sit);
                newRes.insert(news);
            }
        }
        results.clear();
        results = newRes;
    }
}

int main()
{
    cout << "Hello world!" << endl;
    set<string> res1, res2;

    permute(res1, "9418073");
    permute(res2, "3537312");

    cout << "Sizes: " << res1.size() << " " << res2.size() << endl;
    cout << "Same? " << (res1 == res2)  << endl;
//    cout << results << endl;

    if (0)  {
        for (set<string>::iterator sb = res1.begin(); sb != res1.end(); ++sb)
        cout << "res1 " << *sb << endl;
        for (set<string>::iterator sb = res2.begin(); sb != res2.end(); ++sb)
        cout << "res2 " <<*sb << endl;


        }

    return 0;
}

