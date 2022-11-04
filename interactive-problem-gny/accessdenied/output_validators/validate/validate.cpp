#include <climits>
#include <set>
#include <vector>

#include "validate.h"
using namespace std;

const int MAX_QUERIES = 2500;

int total_time;

void op_branch() {
    total_time += 1;
}

void op_assign() {
    total_time += 1;
}

void op_comp() {
    total_time += 3;
}

void op_return() {
    total_time += 1;
}

int main(int argc, char **argv) {
    init_io(argc,argv);

    string password;
    judge_in >> password;
#ifdef DEBUG
   cerr << "Password is " << password << endl;
#endif

    int q = 0;
    for (; q < MAX_QUERIES; q++) {
        string guess;
        if (!(author_out >> guess)) {
            wrong_answer("Wrong answer: failed to read guess. Queries used: %d\n", q+1);
        }
#ifdef DEBUG
	cerr << "Guess " << guess << endl;
#endif

        if (guess.length() < 1) {
            wrong_answer("Wrong answer: guess is empty. Queries used: %d\n", q+1);
        }
        if (guess.length() > 20) {
            wrong_answer("Wrong answer: guess is too long. Queries used: %d\n", q+1);
        }

        bool valid = true;
        for (int i = 0; i < guess.length(); i++) {
            valid = valid && (
                    ('a' <= guess[i] && guess[i] <= 'z') ||
                    ('A' <= guess[i] && guess[i] <= 'Z') ||
                    ('0' <= guess[i] && guess[i] <= '9')
                );
        }
        if (!valid) {
            wrong_answer("Wrong answer: invalid characters in guess. Queries used: %d\n", q+1);
        }

        if (guess.compare(password) == 0) {
            cout << "ACCESS GRANTED" << endl;
#ifdef DEBUG
	    cerr << "Correct" << endl;
#endif
            break;
        }

        total_time = 0;
        if (op_branch(), op_comp(), guess.length() != password.length()) {
            op_return(), cout << "ACCESS DENIED (" << total_time << " ms)" << endl;
#ifdef DEBUG
	    cerr << "Denied 1" << endl;
#endif
            continue;
        }

        for (int i = (op_assign(), 0); op_branch(), op_comp(), i < password.length(); op_assign(), i++) {
            if (op_branch(), op_comp(), password[i] != guess[i]) {
                op_return();
                break;
            }
        }

        cout << "ACCESS DENIED (" << total_time << " ms)" << endl;
#ifdef DEBUG
	    cerr << "Denied 1" << endl;
#endif
    }

#ifdef DEBUG
    cerr << "Queries = " << q+1 << endl;
#endif
    if (q == MAX_QUERIES) {
        wrong_answer("Wrong answer: used all %d queries without finding the password.\n", MAX_QUERIES);
    }

    string junk;
    if (author_out >> junk) {
        wrong_answer("Wrong answer: trailing output.\n");
    }

    judge_message("Queries used: %d.\n", q+1);

    accept();
}

