/* PROJECT 2 - C++ CSE232 Katie Albus
10/27/19
Purpose: identify the words that are the
most similar to the given password from a 
list of most common passwords
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::ifstream;
using std::sort;
using std::make_pair;

/*inputs: none;
Purpose: read the common passords file, find the words that are the most 
similar to the given password (by the user)
*/
int main() {
    ifstream in_file("common_passwords.txt");
    cout << "Give me a password: ";
    string password;
    cin >> password;
    cout << endl;
    cout << "You provided a password of " << password << endl;
    cout << "The most similar passwords to " << password << " are: " << endl;
    vector<pair<int, string>> v;
    //gets each password individually from the file
    string line;
    while(getline(in_file, line)) {
        int line_len = static_cast<int>(line.size());
        int difference_cnt = 0;
        //runs for length of the common passord from file
        for(int i = 0; i < line_len; i++) {
            try {
                if(line[i] != password[i]) {
                    difference_cnt += 1;
                }
            //catches when the password is shorter than the line
            } catch (const std::exception& e) {
                break;
            }
        }
        //when the password is longer than the line, add the extra char(s) to diff
        if(line_len < static_cast<int>(password.size())) {
            difference_cnt += static_cast<int>(password.size()) - line_len;
        }
        v.push_back(make_pair(difference_cnt, line));
    }
    sort(v.begin(), v.end()); //sorts the common passwords by the difference
    //cout << v[0].first << v[0].second << endl; debugging
    for(int i = 0; i < static_cast<int>(v.size()); i++){
        //cout << v[i].first << v[i].second << endl; debugging
        //only includes most similar, all words with the same and lowest difference
        if(v[0].first == v[i].first) {
            cout << v[i].second << ", ";
        }
    }
    cout << endl;
    cout << "All of which are " << v[0].first << " character(s) different.";
