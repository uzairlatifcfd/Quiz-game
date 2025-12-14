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
int find(int arr[], int ind);
void updateHighScores(string newName, int newScore);
void display_high_scorers();
void random(int totalSize, const string &f_name, string main_str[], string selected_str[]);
void chose_file(string &f_name);
void easy_mode();
void medium_mode();
void hard_mode();

void clear_keyboard_buffer(){
    while(kbhit()){
        getch();
    }
}

const int TOTAL_SIZE = 20;
string main_str[TOTAL_SIZE];
string name;
string f_name;
string selected_str[12];
string block;
string line, skip_st;
char Answer;
char correct;
int count_q = 0, n_q = 0;
int score = 0;
int Count = 0;
int swaps = 2, skips = 2;
int available_questions = 0;

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
            cout << endl << endl << "You have 2 maximum swaps and 2 maximum skips in this quiz." << endl;
			cout << "press 'w' to swap and 's' to skip the given question." << endl;
			cout << "If your limit of skip and swap has been finished then further pressing of 's' or 'w' will mark the mcq wrong." << endl;
			cout << "So be careful about the use of swap and skip" << endl;
			cout << "Good Luck !" << endl;
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
    for(int i = 0; i < 12; i++) 
        unique[i] = -1;
    srand(time(0));
    int lines_per_question = 6;
    int n = 0;
    string line;
    string block;
    ifstream file(f_name.c_str());
    if (!file) {
        cout << "file not found" << endl;
        available_questions = 0;
        return;
    }

    // Read only COMPLETE questions (6 lines per question). If file ends early,
    // we stop instead of creating partial/empty questions.
    while(n < totalSize){
        block = "";
        bool full = true;
        for(int j = 0; j < lines_per_question; j++) {
            if(getline(file, line))
                block += line + "\n";
            else{
                full = false;
                break;
            }
        }
        if(!full)
            break;
        main_str[n] = block;
        n++;
    }
    available_questions = n;

    // Pick up to 12 unique questions from what we actually read.
    int pickCount = (available_questions < 12) ? available_questions : 12;
    for(int i = 0; i < pickCount;){
        int index = rand() % available_questions;
        if(find(unique, index)){
            continue;
        }
        selected_str[i] = main_str[index];
        unique[i] = index;
        i++;
    }
    for(int i = pickCount; i < 12; i++){
        selected_str[i] = "";
    }
}

int find(int arr[], int ind){
    for(int j = 0; j <= 11; j++) {
        if(arr[j] == ind)
            return 1;
    }
    return 0;
}

char timer(void){
    char c = '\0';
    bool if_key = true;
    int sec = 10;
    // Clear any previously buffered keys (e.g., Enter) so they don't affect this question.
    clear_keyboard_buffer();
    for(int i = sec; (i > 0 && if_key); i--){
        cout << "\r" << setw(50) << i << " seconds left" << flush;
        Sleep(1000);
        if(kbhit()){
            c = getch();
            if_key = false;
        }
    }
    // Also clear anything typed after the first keypress.
    clear_keyboard_buffer();
    return c;
}

void easy_mode(){
    char ch;
    ch = valid_subject();
    f_name = chose_easy_file(ch);
    random(TOTAL_SIZE, f_name, main_str, selected_str);

    count_q = 0; n_q = 0; score = 0; Count = 0; swaps = 2; skips = 2;
    int max_questions = (available_questions < 10) ? available_questions : 10;
    if(max_questions < 2){
        cout << endl << "Not enough questions in file: " << f_name << endl;
        return;
    }

    while(n_q < max_questions){
        block = selected_str[count_q];
        count_q++;

        int col = block.rfind(':');
        string q_text = block.substr(0, col);
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << count_q << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << q_text << endl;
        
        string prompt = "Enter your answer (A-D)";
        if(skips > 0 && n_q < (max_questions - 1))
            prompt += " or S to skip";
        if(swaps > 0 && n_q < (max_questions - 1))
            prompt += " or W to swap";
        prompt += " (press key only, no Enter): ";
        cout << prompt << flush;
            

        correct = toupper(block[col + 1]);

        
        Answer = toupper(timer());

        if(Answer == 'S' && skips > 0){
            skips--;
            continue;
        }

        if(Answer == 'W' && swaps > 0){
            swaps--;
            skip_st = block;
            int idx = (swaps == 1) ? (max_questions - 1) : (max_questions - 2);
            if(idx < 0) idx = 0;
            block = selected_str[idx];
            selected_str[idx] = skip_st;
            cout << endl;
			col = block.rfind(':');
            q_text = block.substr(0, col);
            correct = toupper(block[col + 1]);
            cout << q_text;
            Answer = timer();
            Answer = toupper(Answer);
        }

        if(Answer == correct){
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else{
            cout << endl << "Wrong!" << endl;
            score -= 2;
            Count = 0;
        }

        if(Count == 3){
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if(Count == 5){
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
    random(TOTAL_SIZE, f_name, main_str, selected_str);

    count_q = 0; n_q = 0; score = 0; Count = 0; swaps = 2; skips = 2;
    int max_questions = (available_questions < 10) ? available_questions : 10;
    if(max_questions < 2){
        cout << endl << "Not enough questions in file: " << f_name << endl;
        return;
    }

    while(n_q < max_questions){
        block = selected_str[count_q];
        count_q++;

        int col = block.rfind(':');
        string q_text = block.substr(0, col);
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << count_q << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << q_text << endl;

        correct = toupper(block[col + 1]);

        cout << "Enter your answer (A-D)";
        if(skips > 0 && n_q < (max_questions - 1))
            cout << " or S to skip";
        if(swaps > 0 && n_q < (max_questions - 1))
            cout << " or W to swap";
        cout << " (press key only, no Enter): ";

        Answer = toupper(timer());

        if(Answer == 'S' && skips > 0){
            skips--;
            continue;
        }

        if(Answer == 'W' && swaps > 0){
            swaps--;
            skip_st = block;
            int index = n_q - 3;
            if(index < 0) index = 0;
            if(index >= max_questions) index = max_questions - 1;
            if(swaps == 1){
                block = selected_str[index];
                selected_str[index] = skip_st;
            }
            else{
                int index2 = n_q - 4;
                if(index2 < 0) index2 = 0;
                if(index2 >= max_questions) index2 = max_questions - 1;
                block = selected_str[index2];
                selected_str[index2] = skip_st;
            }
            cout << endl;
			col = block.rfind(':');
            q_text = block.substr(0, col);
            correct = toupper(block[col + 1]);
            cout << q_text;
            Answer = timer();
            Answer = toupper(Answer);
        }

        if(Answer == correct){
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else{
            cout << endl << "Wrong!" << endl;
            score -= 3;
            Count = 0;
        }

        if(Count == 3){
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if(Count == 5){
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
    random(TOTAL_SIZE, f_name, main_str, selected_str);

    count_q = 0; n_q = 0; score = 0; Count = 0; swaps = 2; skips = 2;
    int max_questions = (available_questions < 10) ? available_questions : 10;
    if(max_questions < 2){
        cout << endl << "Not enough questions in file: " << f_name << endl;
        return;
    }

    while(n_q < max_questions){
        block = selected_str[count_q];
        count_q++;

        int col = block.rfind(':');
        string q_text = block.substr(0, col);
        correct = toupper(block[col + 1]);
        cout << endl << "----------------------------------------" << endl;
        cout << "Question " << count_q << ":" << endl;
        cout << "----------------------------------------" << endl;
        cout << q_text << endl;

        correct = toupper(block[col + 1]);

        cout << "Enter your answer (A-D)";
        if(skips > 0 && n_q < (max_questions - 1))
            cout << " or S to skip";
        if(swaps > 0 && n_q < (max_questions - 1))
            cout << " or W to swap";
        cout << " (press key only, no Enter): ";

        Answer = toupper(timer());

        if(Answer == 'S' && skips > 0){
            skips--;
            continue;
        }

        if(Answer == 'W' && swaps > 0){
            swaps--;
            skip_st = block;
            int index = n_q - 3;
            if(index < 0) index = 0;
            if(index >= max_questions) index = max_questions - 1;
            if(swaps == 1){
                block = selected_str[index];
                selected_str[index] = skip_st;
            }
            else{
                int index2 = n_q - 4;
                if(index2 < 0) index2 = 0;
                if(index2 >= max_questions) index2 = max_questions - 1;
                block = selected_str[index2];
                selected_str[index2] = skip_st;
            }
			cout << endl;
			col = block.rfind(':');
            q_text = block.substr(0, col);
            correct = toupper(block[col + 1]);
            cout << q_text;
            Answer = timer();
            Answer = toupper(Answer);
        }

        if(Answer == correct){
            cout << endl << "Correct!" << endl;
            score++;
            Count++;
        }
        else{
            cout << endl << "Wrong!" << endl;
            score -= 5;
            Count = 0;
        }

        if(Count == 3){
            score += 5;
            cout << endl << "Bonus! +5 points" << endl;
        } else if(Count == 5){
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

        if(numeric != '1' && numeric != '2' && numeric != '3')
            cout << endl << "Invalid input! Try again." << endl;

    } while(numeric != '1' && numeric != '2' && numeric != '3');
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

        if(numeric != '1' && numeric != '2' && numeric != '3')
            cout << endl << "Invalid input! Try again." << endl;

    } while(numeric != '1' && numeric != '2' && numeric != '3');
    return numeric;
}

void updateHighScores(string newName, int newScore){
    string names[5] = {"", "", "", "", ""};
    int scores[5] = {0, 0, 0, 0, 0};

    ifstream fin("high_scorers.txt");
    string line;
    int count = 0;

    while(getline(fin, line) && count < 5){
        if(line == "")
            continue;
        stringstream ss(line);
        string name, scoreStr;
        if(!getline(ss, name, ','))
            continue;
        if(!getline(ss, scoreStr, ','))
            continue;
        names[count] = name;
        stringstream scoreStream(scoreStr);
        scoreStream >> scores[count];
        count++;
    }
    fin.close();

    int lowIndex = 0;
    for(int i = 1; i < 5; i++){
        if(scores[i] < scores[lowIndex])
            lowIndex = i;
    }

    if(newScore > scores[lowIndex]){
        names[lowIndex] = newName;
        scores[lowIndex] = newScore;
    }

    for(int i = 0; i < 5; i++){
        for(int j = i + 1; j < 5; j++){
            if(scores[i] > scores[j]){
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
    for(int i = 0; i < 5; i++){
        fout << names[i] << "," << scores[i] << endl;
    }
    fout.close();
}

void display_high_scorers(){
    ifstream fin("high_scorers.txt");
    string line;
    int count = 0;
    while(getline(fin, line) && count < 5){
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

char valid_subject(){
    char numeric;
    cout << endl << "1. Science Quiz" << endl;
    cout << "2. Maths Quiz" << endl;
    cout << "3. Sports Quiz" << endl;
    cout << "4. History Quiz" << endl;

    do{
        cout << endl << "Enter choice (1-4): ";
        cin >> numeric;
        if(numeric != '1' && numeric != '2' && numeric != '3' && numeric != '4'){
            cout << endl << "Invalid input! Try again." << endl;
        }
    } while(numeric != '1' && numeric != '2' && numeric != '3' && numeric != '4');

    return numeric;
}

