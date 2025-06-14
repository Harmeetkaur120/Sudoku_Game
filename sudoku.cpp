#include <unistd.h>
#include <cstdlib>  // for using rand and srand functions
#include <ctime>    // for using time function
#include <iomanip>
#include <iostream>
#include <limits>
#include <stack>
#include <thread>         // For multithreading
#include <unordered_set>  // for using unordered sets datatype
#include <utility>        // for using pairs

using namespace std;
int hours = 0;
int minutes = 0;
int seconds = 0;
bool running = true;

class Sudoku {
   private:
    struct Move {
        int row;
        int col;
        char value;
    };
    stack<Move> newmove;

    char arr[9][9];
    char dummy[9][9];

    pair<int, int> translate(int num) {
        return make_pair((num - 1) / 9, (num - 1) % 9);
    }

    //------------------For checking that the move is valid or
    //not---------------------

    bool is_valid_move(char num, pair<int, int> p) {
        int row = p.first;
        int col = p.second;
        // Check if the cell is already occupied
        if (arr[row][col] != ' ') {
            return false;
        }

        // Check row and column for duplicates
        for (int i = 0; i < 9; i++) {
            if (arr[row][i] == num || arr[i][col] == num) {
                return false;
            }
        }

        // Check the 3x3 subgrid for duplicates
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        return true;
    }
bool is_valid_movedummy(char num, pair<int, int> p) {
        int row = p.first;
        int col = p.second;
        // Check if the cell is already occupied
        if (arr[row][col] != ' ') {
            return false;
        }

        // Check row and column for duplicates
        for (int i = 0; i < 9; i++) {
            if (dummy[row][i] == num || dummy[i][col] == num) {
                return false;
            }
        }

        // Check the 3x3 subgrid for duplicates
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (dummy[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    //-------------------Sudoku
    //Solver--------------------------------------------------
    bool solver()
    {
        //if(count>81)return false;
       // display_boarddummy();
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(dummy[i][j]==' ')
                {
                    for(char num='1';num<='9';num++)
                    {
                        if(is_valid_movedummy(num,{i,j}))
                            {
                                dummy[i][j]=num;
                                if(!solver())
                                {
                                     dummy[i][j]=' ';

                                }
                                else{
                                   return true;
                                }
                            }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    //---------------------Function for displaying clock and
    //timer----------------------------------------
   public:
    void displayClock() {
        // system call to clear the screen

        cout << setfill(' ') << setw(55) << "         TIMER		 \n";
        cout << setfill(' ') << setw(55) << " --------------------------\n";
        cout << setfill(' ') << setw(29);
        cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
        cout << setfill('0') << setw(2) << minutes << " min | ";
        cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
        cout << setfill(' ') << setw(55) << " --------------------------\n";
    }
    void timer() {
        // infinite loop because timer will keep
        // counting. To kill the process press
        // Ctrl+D. If it does not work ask
        // ubuntu for other ways.
        while (running) {
            // sleep system call to sleep
            // for 1 second
            sleep(1);
            // increment seconds
            seconds++;

            // if seconds reaches 60
            if (seconds == 60) {
                // increment minutes
                minutes++;

                // if minutes reaches 60
                if (minutes == 60) {
                    // increment hours
                    hours++;
                    minutes = 0;
                }
                seconds = 0;
            }
        }
    }
    //------------------------------------------To input new values in the board
    //by the user-------------------------------
    void play() {


    h:
        while (!isboard_full()) {
            // Clear the screen
            // system("CLS");

            //Display the timer and board
            displayClock();   // Display the updated timer.
            display_board();  // Display the Sudoku board.

            int n;
            int c;
            pair<int, int> p;
            bool validInput = false;  // Flag to check if input is valid

            // Keep asking for valid input
            while (!validInput) {
                cout << "Enter number = ";
                cin >> n;

                if (n == -1) {
                    undo_last_move();
                    goto h;
                }

               if (cin.fail() || n < -1 || n > 9) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Try again." << endl;
    continue;
}

                cout << "Enter position = ";
                cin >> p.first >> p.second;
                if (cin.fail()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<std::streamsize>::max(),
                               '\n');  // Ignore invalid input
                    cout << "Enter values from 1-9." << endl;
                }
                //---------------------This method with place the input value on
                //the position specified by the user---------------------------

                // int m = n + 48;
                pair<int, int> p1(p.first - 1, p.second - 1);
                int row = p.first - 1;
                int col = p.second - 1;
                char m = n + '0';

                if (arr[p1.first][p1.second] == ' ') {
                    if (n > 0 && n < 10 && is_valid_move(m, p1))

                    {
                        arr[p1.first][p1.second] = m;
                        newmove.push({row, col, m});
                        validInput = true;  // Mark input as valid

                    } else {
                       system("echo \a");  // Triggers a beep
                       cout << "INVALID MOVE!" << endl;
                    }
                }

                else {
                    cout << "\a";  // Rings the system bell (if enabled)
                    cout << "INVALID MOVE POSITION OCCUPIED!" << endl;
                }
            }
            system("CLS");
        }
        running = false;  // Stop the timer

        cout << "Congratulations! You've completed the Sudoku puzzle!" << endl;
    }
    //--------------------------------For board initialization and displaying
    //-------------------------------------

    void initialize() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) arr[i][j] = ' ';
        }
    }
void display_board() {
        for (int i = 0; i < 9; ++i) {
            cout << "+---+---+---+---+---+---+---+---+---+\n";
            for (int j = 0; j < 9; ++j) {
                cout << "| " << arr[i][j] << " ";
            }
            cout << "|\n";
        }
        cout << "+---+---+---+---+---+---+---+---+---+\n";
    }
    void display_boarddummy() {

        for (int i = 0; i < 9; ++i) {
            cout << "+---+---+---+---+---+---+---+---+---+\n";
            for (int j = 0; j < 9; ++j) {
                cout << "| " << arr[i][j] << " ";
            }
            cout << "|\n";
        }
        cout << "+---+---+---+---+---+---+---+---+---+\n";

    }
    //-------------------------For generating the board according to the needed
    //difficulty------------------------------------

    void generate_board(int difficulty) {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                arr[i][j]=' ';
            }
        }
        unordered_set<int> positions;

        int numCells;
        switch (difficulty) {
            case 1:
                numCells = 50;
                break;  // Easy
            case 2:
                numCells = 27;
                break;  // Medium
            case 3:
                numCells = 18;
                break;  // Hard
            default:
                numCells = 36;
                break;  // Default to Easy
        }

        while (positions.size() < numCells) {
            int pos = 1 + (rand() % 81);
            positions.insert(pos);
        }
      for (int pos : positions) {
            pair<int, int> p = translate(pos);
            char num = '1' + (rand() % 9);
            int attempts = 0;
            while (!is_valid_move(num, p) && attempts < 100) {
                num = '1' + (rand() % 9);
                attempts++;
            }
            if (attempts < 100)
                arr[p.first][p.second] = num;
        }

        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                dummy[i][j]=arr[i][j];
               // cout<<dummy[i][j]<<" ";
            }
            //cout<<endl;
        }
        //cout<<"\n\n\n\n\n\n";
        while(!solver())
        {
             generate_board(difficulty);
        }
       /*else{
            for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){

                cout<<dummy[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\n\n\n\n\n\n";
        }*/
    }
    //--------------------For doing undo of last
    //move----------------------------------------------
    void undo_last_move() {
        if (!newmove.empty()) {
            Move lastmove = newmove.top();
            newmove.pop();
            // clear last position
            arr[lastmove.row][lastmove.col] = ' ';
            cout << "Undo Successful:)";

        } else {
            cout << "Undo not possible!";
        }
    }
    //--------------------For checking is board full or
    //not-------------------------------
    bool isboard_full() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j)
                if (arr[i][j] == ' ') return 0;
        }
        return 1;
    }
    //--------------instruction display------------------

    void display_instructions() {
    cout << "\n---------------------- HOW TO PLAY ----------------------\n";
    cout << "1. You will be asked to enter a number and its position (row and column).\n";
    cout << "2. To enter a value, type a number between 1 and 9.\n";
    cout << "3. Then, enter the row and column positions (each between 1 and 9).\n";
    cout << "   Example: To place 5 at row 3 and column 4, input:\n";
    cout << "       Enter number = 5\n";
    cout << "       Enter position = 3 4\n";
    cout << "4. To undo your last move, enter -1 when prompted for the number.\n";
    cout << "5. Invalid moves (duplicate or out of bounds) will be rejected.\n";
    cout << "6. Game ends when you successfully fill all cells correctly.\n";
    cout << "---------------------------------------------------------\n\n";
}

};

int main() {
    Sudoku g1;
    int i;

    // Start the timer in a separate thread
    thread timerThread(&Sudoku::timer, &g1);
    sleep(1);

    g1.initialize();
    cout << "------------------------------------------------WELCOME TO "
            "SUDOKU----------------------------------------------------"
         << endl;
    cout << "Enter the difficulty level U want:\n 1.) Easy\n 2.) Medium\n 3.) "
            "Hard\n";
    cin >> i;

    g1.generate_board(i);
    g1.display_instructions();
    g1.play();

    // Stop the timer and join the thread
    running = false;
    timerThread.join();

    return 0;
}
