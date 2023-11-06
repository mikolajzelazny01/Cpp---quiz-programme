#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>


using namespace std;

class BaseOfQuestions;

class Question {
    private:
        string content;
        string answer_a,answer_b,answer_c,answer_d;
        string correct_answer;
        string user_answer;
        int question_number;
    public:
        Question(string content, string answer_a, string answer_b, string answer_c, string answer_d,string correct_answer, int question_number);
        int AskAndCheck();
        
};

class BaseOfQuestions {
    private:
        vector<Question> questions;
        int points;
    public:
        void LoadQuestions();
        void Play();
        
};

Question::Question(string content_in, string answer_a_in, string answer_b_in, string answer_c_in, string answer_d_in,string correct_answer_in, int question_number){
    content = content_in;
    answer_a = answer_a_in;
    answer_b = answer_b_in;
    answer_c = answer_c_in;
    answer_d = answer_d_in;
    correct_answer = correct_answer_in;

}

int Question::AskAndCheck() {
    cout << content << endl << answer_a << endl << answer_b << endl << answer_c << endl << answer_d << endl;
    cout << "\nWhich of these is correct? (a/b/c/d) \n";
    cin >> user_answer;
    if (user_answer == correct_answer) {
        cout << "Your answer is correct!\n\n";
        return 1;
    } else {
        cout << "Your answer is incorrect!\n\n";
        return 0;
    }
}

void BaseOfQuestions::LoadQuestions() {
    string input;
    cout << "Please enter path to the questions file: " << endl;
    cin >> input;

    fstream file;
    file.open(input,ios::in);

    if(file.good() == false){
        cout << "Could not open the file"; exit(0);
    } else { 

        int line_count=0;
        string line;

        string content_temp, a_temp, b_temp, c_temp, d_temp, correct_asnwer_temp;
        int question_number_temp;

        while (getline(file,line)) {
            line_count++;
            if (line_count % 6  == 1) content_temp = line;
            if (line_count % 6 == 2) a_temp = line;
            if (line_count % 6 == 3) b_temp = line;
            if (line_count % 6 == 4) c_temp = line;
            if (line_count % 6 == 5) d_temp = line;
            if (line_count % 6 == 0){
                correct_asnwer_temp = line;
                question_number_temp = line_count/6;
                questions.push_back(Question(content_temp, a_temp, b_temp, c_temp, d_temp, correct_asnwer_temp,question_number_temp)); 
            } 

        }

        file.close();
    }
}

void BaseOfQuestions::Play() {
    int run = 1;
    int test = questions.size();
    string next;
    points=0;
    system("cls");
    int history[questions.size()]; //declaring size of the draw history 
    for (int j=0; j<questions.size(); j++) { // initializing table with -1 to protect from checking for zeros
        history[j] = -1;
    }
    srand(time(NULL));
    for (int it=0; it<questions.size(); it++) { // main loop to overwrite every -1 in the history[] tab
        run = 1;
        do {
          int candidate = rand()%questions.size(); // picking a random candidate for an index
          bool found = false;
            for (int iter=0; iter<=it; iter++) {
                if (history[iter] == candidate) { // if a drawn candidate exists in the history, set found to true and dont look further
                    found = true;
                    break;
                }
          }
          if (found == false) { // if there were no repeats found, stop generating candidates for i index of a tab
            history[it] = candidate;
            run = 0; 
          }      
        } while (run == 1);
    } 
    
    for (int i=0; i<questions.size(); i++) {
        if (questions[history[i]].AskAndCheck() == 1) {
                points++;
        }
        cout << "Your points: " << points << endl;
        if (i < questions.size()-1){
            cout << endl << "Next question? (y/n)" << endl;
            cin >> next;  
            if (next == "y") {
                cout << endl; 
            } else {
                break;
            }
        } else {
            cout << "Ran out of questions :)" << endl;
        }
    }
    cout << "Good luck next time!" ; 
}

int main()
{ 
    BaseOfQuestions game;
    game.LoadQuestions();
    game.Play();

  return 0;
}