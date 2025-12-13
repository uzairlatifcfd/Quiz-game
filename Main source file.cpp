#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h> 

using namespace std;
char level_choice();
char initial_choice();
char valid_subject();
string chose_easy_file(char);
string chose_med_file(char);
string chose_hard_file(char);
char timer(void);
int find(int arr[],int ind);
void updateHighScores(string newName, int newScore);
void display_high_scorers();
void random(int totalSize, const string &f_name, string main_str[], string selected_str[]);
void chose_file(string &f_name);
void easy_mode();
void medium_mode();
void hard_mode();

const int TOTAL_SIZE = 20;
string main_str[TOTAL_SIZE];
string name;
string f_name;
string selected_str[12];
string block;
string line,skip_st;
char Answer;
char correct;
int count_q = 0, n_q = 0;
int score = 0;
int Count = 0;
int swaps = 2,skips = 2;

int main() {
    char numeric, choice;

    do {
        cout << endl << "========================================" << endl;
        cout << "            QUIZ GAME MENU              " << endl;
        cout << "========================================" << endl;

        choice = initial_choice();

        if(choice == '1') {
            numeric = level_choice();
            cout << endl << "Enter your name: ";
            cin >> ws;
            getline(cin, name);
            cout << endl << "========================================" << endl << endl;
            if(numeric == '1')
                 easy_mode();
            else if(numeric == '2')
                 medium_mode();
            else 
                 hard_mode();
        }
        else if(choice == '2') {
            cout << endl << "========================================" << endl;
            cout << setw(35) << "TOP HIGH SCORERS" << endl;
            cout << "========================================" << endl;
            display_high_scorers(); 
            cout << "========================================" << endl;
        }
        else if(choice == '3') {
            cout << endl << "========================================" << endl;
            cout << "               QUIZ EXITED              " << endl;
            cout << "========================================" << endl;
        }

    } while(choice != '3');

    return 0;
}


void random(int totalSize, const string &f_name, string main_str[], string selected_str[]){
    int unique[12];
    for(int i=0;i<12;i++) 
        unique[i]=-1;
    srand(time(0));
    int lines_per_question = 6;
    int n = 0;
    string line;
    string block;
    ifstream file(f_name.c_str());
    if (!file) {
        cout << "file not found" << endl;
        return;
    }

    while(n < totalSize){
        block = "";
        for (int j = 0; j < lines_per_question; j++) {
            if (getline(file, line))
                block += line + "\n";
        }
        main_str[n] = block;
        n++;
    }

    for(int i = 0; i < 12;){
        int index = rand() % totalSize;
        if(find(unique,index)){
            continue;
        }
        selected_str[i] = main_str[index];
        unique[i] = index;
        ++i;
    }
}

int find(int arr[],int ind){
    for (int j = 0; j <= 11; j++) {
        if(arr[j] == ind)
            return 1;
    }
    return 0;
}

char timer(void){
    char c = '\0';
    bool if_key = true;
    int sec = 10;
    for (int i = sec; (i > 0 && if_key) ; i--){
        cout << "\r" << setw(50) << i << " seconds left" << flush;
        Sleep(1000);
        if (kbhit()){
            c = getch();
            if_key = false;
        }
    }
    if(c == 'e')
        cout << endl << "Time's up!" << endl;
    return c;
}

void easy_mode(){
    char ch;
    ch = valid_subject();
    f_name = chose_easy_file(ch);
    random(TOTAL_SIZE,f_name, main_str, selected_str);

    count_q=0;n_q=0;score=0;Count=0;swaps=2;skips=2;

    while (n_q < 10) {
        block = selected_str[count_q];
        count_q++;
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << n_q+1 << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << block << endl;

        int col = block.find_last_of(':');
        correct = toupper(block[col + 1]);
        cout << "Enter your answer (A-D): ";
        if (n_q < 9) {
            cout << "Or Press S to skip ";
            cout << "Or Press W to swap ";
        }

        Answer = toupper(timer());

        if (Answer == 'S') {
            if (skips > 0) {
                skips--;
                n_q++;
                continue;
            } else {
                cout << endl << "You are out of skips!" << endl;
                cout << "Enter your answer (A-D): ";
                if (n_q < 9) {
                    cout << "Or Press S to skip ";
                    cout << "Or Press W to swap ";
                }
                Answer = toupper(timer());
            }
        }

        if (Answer == 'W') {
            if (swaps > 0) {
                swaps--;
                skip_st = block;
                if (swaps == 1) {
                    block = selected_str[9];
                    selected_str[9] = skip_st;
                } else {
                    block = selected_str[8];
                    selected_str[8] = skip_st;
                }
                cout << block;
                Answer = timer();
                Answer = toupper(Answer);
            } else {
                cout << endl << "You are out of swaps!" << endl;
                cout << "Enter your answer (A-D): ";
                if (n_q < 9) {
                    cout << "Or Press S to skip ";
                    cout << "Or Press W to swap ";
                }
                Answer = toupper(timer());
            }
        }

        if (Answer == correct) {
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else {
            cout << endl << "Wrong!" << endl;
            cout << "Correct answer is: " << correct << endl;
            score-=2;
            Count = 0;
        }

        if (Count == 3) {
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if (Count == 5) {
            score += 15;
            cout << endl << "Bonus! +15 points" << endl;
        }

        cout << "Current Score: " << score << endl;
        cout << "----------------------------------------" << endl;
        n_q++;
    }
    cout << endl << "========================================" << endl;
    cout << "           QUIZ COMPLETED               " << endl;
    cout << "========================================" << endl;
    cout << "Player: " << name << endl;
    cout << "Final Score: " << score << endl;
    display_high_scorers();
    cout << "========================================" << endl;
    updateHighScores(name, score);
}

void medium_mode(){
    char ch;
    ch = valid_subject();
    f_name = chose_med_file(ch);
    random(TOTAL_SIZE,f_name, main_str, selected_str);

    count_q=0;n_q=0;score=0;Count=0;swaps=2;skips=2;

    while (n_q < 10) {
        block = selected_str[count_q];
        count_q++;
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << n_q+1 << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << block << endl;

        int col = block.find_last_of(':');
        correct = toupper(block[col + 1]);

        if (n_q < 9) {
            cout << "Or Press S to skip ";
            cout << "Or Press W to swap ";
        }

        Answer = toupper(timer());

        if (Answer == 'S') {
            if (skips > 0) {
                skips--;
                n_q++;
                continue;
            } else {
                cout << endl << "You are out of skips!" << endl;
                cout << "Enter your answer (A-D): ";
                if (n_q < 9) {
                    cout << "Or Press S to skip ";
                    cout << "Or Press W to swap ";
                }
                Answer = toupper(timer());
            }
        }

        if (Answer == 'W') {
            if (swaps > 0) {
                swaps--;
                skip_st = block;
                int index = n_q-3;
                if(index<0) index=0;
                if(swaps == 1){
                    block = selected_str[index];
                    selected_str[index] = skip_st;
                }
                else{
                    int index2=n_q-4;
                    if(index2<0) index2=0;
                    block = selected_str[index2];
                    selected_str[index2] = skip_st;
                }
                cout << block;
                Answer = timer();
                Answer = toupper(Answer);
            } else {
                cout << endl << "You are out of swaps!" << endl;
                cout << "Enter your answer (A-D): ";
                if (n_q < 9) {
                    cout << "Or Press S to skip ";
                    cout << "Or Press W to swap ";
                }
                Answer = toupper(timer());
            }
        }

        if (Answer == correct) {
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else {
            cout << endl << "Wrong!" << endl;
            cout << "Correct answer is: " << correct << endl;
            score-=3;
            Count = 0;
        }

        if (Count == 3) {
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if (Count == 5) {
            score += 15;
            cout << endl << "Bonus! +15 points" << endl;
        }

        cout << "Current Score: " << score << endl;
        cout << "----------------------------------------" << endl;
        n_q++;
    }
    cout << endl << "========================================" << endl;
    cout << "           QUIZ COMPLETED               " << endl;
    cout << "========================================" << endl;
    cout << "Player: " << name << endl;
    cout << "Final Score: " << score << endl;
    display_high_scorers();
    cout << "========================================" << endl;
    updateHighScores(name, score);
}

void hard_mode(){
    char ch;
    ch = valid_subject();
    f_name = chose_hard_file(ch);
    random(TOTAL_SIZE,f_name, main_str, selected_str);

    count_q=0;n_q=0;score=0;Count=0;swaps=2;skips=2;

    while (n_q < 10) {
        block = selected_str[count_q];
        count_q++;
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << n_q+1 << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << block << endl;

        int col = block.find_last_of(':');
        correct = toupper(block[col + 1]);

        if (skips > 0 && n_q < 9)
            cout << "Or Press S to skip: ";
        if (swaps > 0 && n_q < 9)
            cout << "Or Press W to swap: ";
            
        Answer = toupper(timer());
            
        if (Answer == 'S' && skips > 0) {
            skips--;
            n_q++;
            continue;
        }

        if(Answer == 'W' && swaps > 0){
            swaps--;
            skip_st = block;
            int index = n_q-3;
            if(index<0) index=0;
            if(swaps == 1){
                block = selected_str[index];
                selected_str[index] = skip_st;
            }
            else{
                int index2=n_q-4;
                if(index2<0) index2=0;
                block = selected_str[index2];
                selected_str[index2] = skip_st;
            }
            cout << block;
            Answer = timer();
            Answer = toupper(Answer);
        }

        if (Answer == correct) {
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else {
            cout << endl << "Wrong!" << endl;
            cout << "Correct answer is: " << correct << endl;
            score-=5;
            Count = 0;
        }

        if (Count == 3) {
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if (Count == 5) {
            score += 15;
            cout << endl << "Bonus! +15 points" << endl;
        }

        cout << "Current Score: " << score << endl;
        cout << "----------------------------------------" << endl;
        n_q++;
    }
    cout << endl << "========================================" << endl;
    cout << "           QUIZ COMPLETED               " << endl;
    cout << "========================================" << endl;
    cout << "Player: " << name << endl;
    cout << "Final Score: " << score << endl;
    display_high_scorers();
    cout << "========================================" << endl;
    updateHighScores(name, score);
}

char level_choice(){
    char numeric;
    do {
        cout << endl << "========================================" << endl;
        cout << "           SELECT DIFFICULTY            " << endl;
        cout << "========================================" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "Enter choice (1-3): ";

        cin >> numeric;

        if (numeric != '1' && numeric != '2' && numeric != '3')
            cout << endl << "Invalid input! Try again." << endl;

    } while (numeric != '1' && numeric != '2' && numeric != '3');
    return numeric;
}

char initial_choice(){
    char numeric;
    do {
        cout << endl << "1. Start Quiz" << endl;
        cout << "2. LeaderBoard" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice (1-3): ";

        cin >> numeric;

        if (numeric != '1' && numeric != '2' && numeric != '3')
            cout << endl << "Invalid input! Try again." << endl;

    } while (numeric != '1' && numeric != '2' && numeric != '3');
    return numeric;
}

void updateHighScores(string newName, int newScore)
{
    string names[5] = {"", "", "", "", ""};
    int scores[5] = {0, 0, 0, 0, 0};

    ifstream fin("high_scorers.txt");
    string line;
    int count = 0;

    while (getline(fin, line) && count < 5)
    {
        if (line == "") 
            continue;

        stringstream ss(line);
        string name, scoreStr;

        if (!getline(ss, name, ','))
            continue;
        if (!getline(ss, scoreStr, ','))
            continue;

        names[count] = name;
        stringstream scoreStream(scoreStr);
        scoreStream >> scores[count];

        count++;
    }
    fin.close();

    int lowIndex = 0;
    for (int i = 1; i < 5; i++)
    {
        if(scores[i] < scores[lowIndex])
            lowIndex = i;
    }

    if (newScore > scores[lowIndex])
    {
        names[lowIndex] = newName;
        scores[lowIndex] = newScore;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (scores[i] > scores[j])
            {
                int tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                string tempName = names[i];
                names[i] = names[j];
                names[j] = tempName;
            }
        }
    }

    ofstream fout("high_scorers.txt");
    for (int i = 0; i < 5; i++)
    {
        fout << names[i] << "," << scores[i] << endl;
    }
    fout.close();
}

void display_high_scorers()
{
    ifstream fin("high_scorers.txt");
    string line;
    int count = 0;

    while (getline(fin, line) && count < 5)
    {
        cout << setw(55) << line << endl;
        count++;
    }
    fin.close();
}

string chose_easy_file(char ch){
    if(ch == '1')
       return "easy_science.txt";
    else if(ch == '2')
       return "easy_maths.txt";
    else if(ch == '3')
       return "easy_sports.txt";
    else
       return "easy_history.txt";
}

string chose_med_file(char ch){
    if(ch == '1')
       return "med_science.txt";
    else if(ch == '2')
       return "med_maths.txt";
    else if(ch == '3')
       return "med_sports.txt";
    else
       return "med_history.txt";
}

string chose_hard_file(char ch){
    if(ch == '1')
       return "hard_science.txt";
    else if(ch == '2')
       return "hard_maths.txt";
    else if(ch == '3')
       return "hard_sports.txt";
    else
       return "hard_history.txt";
}

char valid_subject()
{
    char numeric;

    cout << endl << "1. Science Quiz" << endl;
    cout << "2. Maths Quiz" << endl;
    cout << "3. Sports Quiz" << endl;
    cout << "4. History Quiz" << endl;

    do
    {
        cout << endl << "Enter choice (1-4): ";
        cin >> numeric;

        if (numeric != '1' && numeric != '2' && numeric != '3' && numeric != '4')
        {
            cout << endl << "Invalid input! Try again." << endl;
        }

    } while (numeric != '1' && numeric != '2' && numeric != '3' && numeric != '4');

    return numeric;
}

