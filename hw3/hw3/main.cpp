
//Gorkem Kocamanoglu
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


bool isNotEmpty(char direction, int row_command, int column_command, vector<vector<char>> matrix){
    if (matrix[row_command][column_command] == '-'){
        return false;
    }
    else if (direction == 'r' && matrix[row_command][column_command+1] =='-'){
        return false;
    }
    else if (direction == 'l' && matrix[row_command][column_command-1] =='-'){
        return false;
    }
    return true;
}

bool isvalid(int row_count, int column_count, char direction, int row_command, int column_command,vector<vector<char>> matrix) {
    if (row_command < 0 || column_command < 0) {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    else if (row_command >= row_count || column_command >= column_count) {
        cout << "Invalid coordinates!" << endl;
        return false;
    }
    if (direction == 'r') {
        if (column_command + 1 >= column_count) {
            cout << "Move out of bounds!" << endl;
            return false;
        }
    }
    else if (direction == 'l') {
        if (column_command == 0) {
            cout << "Move out of bounds!" << endl;
            return false;
        }
    }
    else if (direction == 'u') {
        if (row_command == 0) {
            cout << "Move out of bounds!" << endl;
            return false;
        }
    }
    else if (direction == 'd') {
        if (row_command + 1 >= row_count) {
            cout << "Move out of bounds!" << endl;
            return false;
        }
    }
    if (direction != 'r' && direction != 'l' && direction != 'u' && direction != 'd') {
        cout << "Invalid input. Try again." << endl;
        return false;
    }
    if (matrix[row_command][column_command] == '-'){
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    else if (direction == 'r' && matrix[row_command][column_command+1] =='-'){
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    else if (direction == 'l' && matrix[row_command][column_command-1] =='-'){
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    else if (direction == 'u' && matrix[row_command-1][column_command] =='-'){
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    else if (direction == 'd' && matrix[row_command+1][column_command] =='-'){
        cout << "Cannot swap with an empty cell!" << endl;
        return false;
    }
    return true;
}

bool isGravityAppliable(vector<vector<char>> matrix){
    for(int i = 0; i < matrix.size()-1;i++){
        for(int j = 0; j < matrix[0].size();j++ ){
            if(matrix[i][j] != '-' && matrix[i+1][j] == '-' ){
                return true;
            }
        }
    }
    return false;
}

bool BingoChecker(vector<vector<char>> matrix){
    for(int j=0; j<matrix.size(); j++){ //horizontal check
        for(int g=0; g<matrix[0].size()-2;g++){
            if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                return true;
            }
        }
    }
    for(int a=0;a<matrix[0].size(); a++){ //vertical check
        for(int b=0;b<matrix.size()-2;b++){
            if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                return true;
            }
        }
    }
    return false;
}





bool checkerFunction(vector<vector<char>> &matrix){
    for(int j=0; j<matrix.size(); j++){ //horizontal check
        for(int g=0; g<matrix[0].size()-2;g++){
            if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                return true;
            }
        }
    }
    for(int a=0;a<matrix[0].size(); a++){ //vertical check
        for(int b=0;b<matrix.size()-2;b++){
            if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                return true;
            }
        }
    }
    return false;
}
int main() {
    char ch;  //defining ch for our characters in game
    string filename1, line, input;
    ifstream file1;
    vector<vector<char>> matrix;
    cout << "Please enter the file name: " << endl;
    bool file_opened = false;
    while(!file_opened){   //while the file is not opened, keep trying
        file_opened=true;   // assume it is opened until it fails
        cin >> filename1;
        file1.open(filename1);
        if (file1.fail()) {
            cout << "The file couldn't be opened. " << endl;
            file_opened = false;
            cout << "Please enter a valid file name: " << endl;
        }
    }
    cin.ignore(); //we clear the input buffer after cin operation(we will use getline)
    // Now we read the matrix from the file
    while (getline(file1, line)) {
        stringstream s(line);
        vector<char> row;
        while (s >> ch) {
            if (ch != 'O' && ch != 'S' && ch != 'X') {
                cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
                cout << "Exiting the game. Bye bye." << endl;
                return 0;
            }
            row.push_back(ch);  //we start reading and forming rows
        }
        matrix.push_back(row); // we add the whole row to matrix
    }

    // Now we check if all rows have the same length
    int row_count = matrix.size();
    int column_count = matrix[0].size();
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i].size() != column_count) {
            cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
            cout << "Exiting the game. Bye bye." << endl;
            return 0;
        }
    }

    // Display the matrix
    cout << "The content of the matrix is:" << endl;
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < column_count; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // Game loop
    cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl;
    while (true) {
        cout << "Move: " << endl;
        getline(cin, input); // Read the entire input line
        
        // Use a stringstream to parse the input
        stringstream ss(input);
        int row, column;
        char direction;
        ss >> row >> column >> direction;
        
        // Check for exit condition
        if (row == 0 && column == 0 && direction == 'q') {
            cout << "Exiting the game. Bye bye." << endl;
            return 0;
        }
        
        // Validate the input
        if (isvalid(row_count, column_count, direction, row, column, matrix)) {
            char temp = matrix[row][column];  //We get ready to swap places
            bool success = false;          //success is to determine if the swapping ended in 3 or more adjacent identical symbols
            if(direction == 'd'){
                matrix[row][column]= matrix[row+1][column];
                matrix[row+1][column] = temp;
                success = BingoChecker(matrix);
                if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                    cout << "Invalid move: No match found!" << endl;
                    char temporary = matrix[row][column];
                    matrix[row][column] = matrix[row+1][column];
                    matrix[row+1][column] = temporary;
                }
            }
            if(direction == 'u'){
                matrix[row][column]= matrix[row-1][column];
                matrix[row-1][column] = temp;
                success = BingoChecker(matrix);
                if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                    cout << "Invalid move: No match found!" << endl;
                    char temporary = matrix[row][column];
                    matrix[row][column] = matrix[row-1][column];
                    matrix[row-1][column] = temporary;
                }
            }
            if(direction == 'l'){ //we write these for all directions
                matrix[row][column]= matrix[row][column-1];
                matrix[row][column-1] = temp;
                success = BingoChecker(matrix);
                if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                    cout << "Invalid move: No match found!" << endl;
                    char temporary = matrix[row][column];
                    matrix[row][column] = matrix[row][column-1];
                    matrix[row][column-1] = temporary;
                }
            }
            if(direction == 'r'){
                matrix[row][column]= matrix[row][column+1];
                matrix[row][column+1] = temp;
                success = BingoChecker(matrix);
                if(success == false){
                    cout << "Invalid move: No match found!" << endl;
                    char temporary = matrix[row][column];
                    matrix[row][column] = matrix[row][column+1];
                    matrix[row][column+1] = temporary;
                }
            }
            if(success){
                cout << "After swap: " << endl;
                for (int i = 0; i < row_count; i++) {
                    for (int j = 0; j < column_count; j++) {
                        cout << matrix[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
                cout << "Move successful. Clearing matches..." << endl;
                cout << "After clearing matches:" <<endl;
                for(int j=0; j<matrix.size(); j++){ //horizontal clearing
                    for(int g=0; g<matrix[0].size()-2;g++){
                        if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                            int counter = 0; //counter for how many symbols are adjacent
                            char symbol = matrix[j][g];
                            bool still_identical = true;    //we create a boolean for while loop
                            while(still_identical && (g+counter)<column_count){     //we use while loop since we dont know how many adjacent symbols there will be
                                if(matrix[j][g+counter] == symbol){
                                    matrix[j][g+counter] = '-';
                                    counter ++;
                                }
                                else{
                                    still_identical = false;
                                }
                            }
                        }
                    }
                }
                for(int a=0;a<matrix[0].size(); a++){ //vertical clearing
                    for(int b=0;b<matrix.size()-2;b++){
                        if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                            int counter2 = 0;
                            char symbol2 = matrix[b][a];
                            bool still_identical2 = true;
                            while (still_identical2 && (b+counter2)<row_count){
                                if(matrix[b+counter2][a] == symbol2){
                                    matrix[b+counter2][a] = '-';
                                    counter2 ++;
                                }
                                else{
                                    still_identical2 = false;
                                }
                            }
                        }
                    }
                }
                
                for (int i = 0; i < row_count; i++) {
                    for (int j = 0; j < column_count; j++) {
                        cout << matrix[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
                do {
                    cout << "After applying gravity: " << endl;
                    bool gravityContinue = true; // I created a boolean because when i apply gravity I want to check the whole board multiple times since i am reading from top left to bottom right and i can miss applying gravity to the first rows after the character below them falls just after they get checked and they will be floating in the air
                    while(gravityContinue){
                        gravityContinue = false;
                        for(int i=0;i<row_count-1;i++ ){
                            for(int j=0;j<column_count; j++){
                                if(matrix[i][j] != '-'){
                                    if(matrix[i+1][j] == '-'){
                                        matrix[i+1][j] = matrix[i][j];
                                        matrix[i][j] = '-';
                                        gravityContinue=true; // as long as a character falls i need to repeat checking the upper rows to see if anything is floating
                                    }
                                }
                            }
                        }
                    }
                    for (int i = 0; i < row_count; i++) {
                        for (int j = 0; j < column_count; j++) {
                            cout << matrix[i][j];
                        }
                        cout << endl;
                    }
                    cout << endl;
                    if(checkerFunction(matrix)){
                        cout << "After clearing matches:" <<endl;
                        for(int j=0; j<matrix.size(); j++){ //horizontal clearing
                            for(int g=0; g<matrix[0].size()-2;g++){
                                if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                                    int counter = 0; //counter for how many symbols are adjacent
                                    char symbol = matrix[j][g];
                                    bool still_identical = true;    //we create a boolean for while loop
                                    while(still_identical&& (g+counter) < column_count){     //we use while loop since we dont know how many adjacent symbols there will be
                                        if(matrix[j][g+counter] == symbol){
                                            matrix[j][g+counter] = '-';
                                            counter ++;
                                        }
                                        else{
                                            still_identical = false;
                                        }
                                    }
                                }
                            }
                        }
                        for(int a=0;a<matrix[0].size(); a++){ //vertical clearing
                            for(int b=0;b<matrix.size()-2;b++){
                                if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                                    int counter2 = 0;
                                    char symbol2 = matrix[b][a];
                                    bool still_identical2 = true;
                                    while (still_identical2 && (b+counter2)<row_count){
                                        if(matrix[b+counter2][a] == symbol2){
                                            matrix[b+counter2][a] = '-';
                                            counter2 ++;
                                        }
                                        else{
                                            still_identical2 = false;
                                        }
                                    }
                                }
                            }
                        }
                        for (int i = 0; i < row_count; i++) {
                            for (int j = 0; j < column_count; j++) {
                                cout << matrix[i][j];
                            }
                            cout << endl;
                        }
                        cout << endl;

                        
                    }
                } while (isGravityAppliable(matrix));
            }
        }
    }
    return 0;
}
// 0 13 l       5 10 l      5 2 u            1 8 l            2 7 d             



/*
 //Gorkem Kocamanoglu

 #include <iomanip>
 #include <iostream>
 #include <string>
 #include <fstream>
 #include <vector>
 #include <sstream>
 #include <cmath>
 using namespace std;


 bool isNotEmpty(char direction, int row_command, int column_command, vector<vector<char>> matrix){
     if (matrix[row_command][column_command] == '-'){
         return false;
     }
     else if (direction == 'r' && matrix[row_command][column_command+1] =='-'){
         return false;
     }
     else if (direction == 'l' && matrix[row_command][column_command-1] =='-'){
         return false;
     }
     return true;
 }

 bool isvalid(int row_count, int column_count, char direction, int row_command, int column_command,vector<vector<char>> matrix) {
     if (row_command < 0 || column_command < 0) {
         cout << "Invalid input. Try again." << endl;
         return false;
     }
     else if (row_command >= row_count || column_command >= column_count) {
         cout << "Invalid coordinates!" << endl;
         return false;
     }
     if (direction == 'r') {
         if (column_command + 1 >= column_count) {
             cout << "Move out of bounds!" << endl;
             return false;
         }
     }
     else if (direction == 'l') {
         if (column_command == 0) {
             cout << "Move out of bounds!" << endl;
             return false;
         }
     }
     else if (direction == 'u') {
         if (row_command == 0) {
             cout << "Move out of bounds!" << endl;
             return false;
         }
     }
     else if (direction == 'd') {
         if (row_command + 1 >= row_count) {
             cout << "Move out of bounds!" << endl;
             return false;
         }
     }
     if (direction != 'r' && direction != 'l' && direction != 'u' && direction != 'd') {
         cout << "Invalid input. Try again." << endl;
         return false;
     }
     if (matrix[row_command][column_command] == '-'){
         cout << "Cannot swap with an empty cell!" << endl;
         return false;
     }
     else if (direction == 'r' && matrix[row_command][column_command+1] =='-'){
         cout << "Cannot swap with an empty cell!" << endl;
         return false;
     }
     else if (direction == 'l' && matrix[row_command][column_command-1] =='-'){
         cout << "Cannot swap with an empty cell!" << endl;
         return false;
     }
     else if (direction == 'u' && matrix[row_command-1][column_command] =='-'){
         cout << "Cannot swap with an empty cell!" << endl;
         return false;
     }
     else if (direction == 'd' && matrix[row_command+1][column_command] =='-'){
         cout << "Cannot swap with an empty cell!" << endl;
         return false;
     }
     return true;
 }

 bool isGravityAppliable(vector<vector<char>> matrix){
     for(int i = 0; i < matrix.size()-1;i++){
         for(int j = 0; j < matrix[0].size();j++ ){
             if(matrix[i][j] != '-' && matrix[i+1][j] == '-' ){
                 return true;
             }
         }
     }
     return false;
 }







 bool checkerFunction(vector<vector<char>> &matrix){
     for(int j=0; j<matrix.size(); j++){ //horizontal check
         for(int g=0; g<matrix[0].size()-2;g++){
             if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                 return true;
             }
         }
     }
     for(int a=0;a<matrix[0].size(); a++){ //vertical check
         for(int b=0;b<matrix.size()-2;b++){
             if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                 return true;
             }
         }
     }
     return false;
 }










 int main() {
     char ch;  //defining ch for our characters in game
     string filename1, line, input;
     ifstream file1;
     vector<vector<char>> matrix;
     cout << "Please enter the file name: " << endl;
     bool file_opened = false;
     while(!file_opened){   //while the file is not opened, keep trying
         file_opened=true;   // assume it is opened until it fails
         cin >> filename1;
         file1.open(filename1);
         if (file1.fail()) {
             cout << "The file couldn't be opened. " << endl;
             file_opened = false;
             cout << "Please enter a valid file name: " << endl;
         }
     }
     cin.ignore(numeric_limits<streamsize>::max(), '\n'); //we clear the input buffer after cin operation(we will use getline)
     // Now we read the matrix from the file
     while (getline(file1, line)) {
         stringstream s(line);
         vector<char> row;
         while (s >> ch) {
             if (ch != 'O' && ch != 'S' && ch != 'X') {
                 cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
                 cout << "Exiting the game. Bye bye." << endl;
                 return 0;
             }
             row.push_back(ch);  //we start reading and forming rows
         }
         matrix.push_back(row); // we add the whole row to matrix
     }

     // Now we check if all rows have the same length
     int row_count = matrix.size();
     int column_count = matrix[0].size();
     for (int i = 0; i < matrix.size(); i++) {
         if (matrix[i].size() != column_count) {
             cout << "The matrix either has invalid dimensions or contains invalid characters." << endl;
             cout << "Exiting the game. Bye bye." << endl;
             return 0;
         }
     }

     // Display the matrix
     cout << "The content of the matrix is:" << endl;
     for (int i = 0; i < row_count; i++) {
         for (int j = 0; j < column_count; j++) {
             cout << matrix[i][j];
         }
         cout << endl;
     }
     cout << endl;

     // Game loop
     cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << endl;
     while (true) {
         cout << "Move: " << endl;
         getline(cin, input); // Read the entire input line
         
         // Use a stringstream to parse the input
         stringstream ss(input);
         int row, column;
         char direction;
         ss >> row >> column >> direction;
         
         // Check for exit condition
         if (row == 0 && column == 0 && direction == 'q') {
             cout << "Exiting the game. Bye bye." << endl;
             return 0;
         }
         
         // Validate the input
         if (isvalid(row_count, column_count, direction, row, column, matrix)) {
             char temp = matrix[row][column];//type the exchange
             bool success = false;
             if(direction == 'd'){
                 matrix[row][column]= matrix[row+1][column];
                 matrix[row+1][column] = temp;
                 for(int j=0; j<matrix.size(); j++){ //horizontal check
                     for(int g=0; g<matrix[0].size()-2;g++){
                         if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                             success = true;
                         }
                     }
                 }
                 for(int a=0;a<matrix[0].size(); a++){ //vertical check
                     for(int b=0;b<matrix.size()-2;b++){
                         if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                             success = true;
                         }
                     }
                 }
                 if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                     cout << "Invalid move: No match found!" << endl;
                     char temporary = matrix[row][column];
                     matrix[row][column] = matrix[row+1][column];
                     matrix[row+1][column] = temporary;
                 }
             }
             if(direction == 'u'){
                 matrix[row][column]= matrix[row-1][column];
                 matrix[row-1][column] = temp;
                 for(int j=0; j<matrix.size(); j++){ //horizontal check
                     for(int g=0; g<matrix[0].size()-2;g++){
                         if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                             success = true;
                         }
                     }
                 }
                 for(int a=0;a<matrix[0].size(); a++){ //vertical check
                     for(int b=0;b<matrix.size()-2;b++){
                         if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                             success = true;
                         }
                     }
                 }
                 if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                     cout << "Invalid move: No match found!" << endl;
                     char temporary = matrix[row][column];
                     matrix[row][column] = matrix[row-1][column];
                     matrix[row-1][column] = temporary;
                 }
             }
             if(direction == 'l'){
                 matrix[row][column]= matrix[row][column-1];
                 matrix[row][column-1] = temp;
                 for(int j=0; j<matrix.size(); j++){ //horizontal check
                     for(int g=0; g<matrix[0].size()-2;g++){
                         if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                             success = true;
                         }
                     }
                 }
                 for(int a=0;a<matrix[0].size(); a++){ //vertical check
                     for(int b=0;b<matrix.size()-2;b++){
                         if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                             success = true;
                         }
                     }
                 }
                 if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                     cout << "Invalid move: No match found!" << endl;
                     char temporary = matrix[row][column];
                     matrix[row][column] = matrix[row][column-1];
                     matrix[row][column-1] = temporary;
                 }
             }
             if(direction == 'r'){
                 matrix[row][column]= matrix[row][column+1];
                 matrix[row][column+1] = temp;
                 for(int j=0; j<matrix.size(); j++){ //horizontal check
                     for(int g=0; g<matrix[0].size()-2;g++){
                         if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                             success = true;
                         }
                     }
                 }
                 for(int a=0;a<matrix[0].size(); a++){ //vertical check
                     for(int b=0;b<matrix.size()-2;b++){
                         if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                             success = true;
                         }
                     }
                 }
                 if(success == false){ //if there are no changes on the game after move is played, revert back to starting position
                     cout << "Invalid move: No match found!" << endl;
                     char temporary = matrix[row][column];
                     matrix[row][column] = matrix[row][column+1];
                     matrix[row][column+1] = temporary;
                 }
             }
             if(success){
                 cout << "After swap: " << endl;
                 for (int i = 0; i < row_count; i++) {
                     for (int j = 0; j < column_count; j++) {
                         cout << matrix[i][j];
                     }
                     cout << endl;
                 }
                 cout << endl;
                 cout << "Move successful. Clearing matches..." << endl;
                 cout << "After clearing matches:" <<endl;
                 for(int j=0; j<matrix.size(); j++){ //horizontal clearing
                     for(int g=0; g<matrix[0].size()-2;g++){
                         if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                             int counter = 0; //counter for how many symbols are adjacent
                             char symbol = matrix[j][g];
                             bool still_identical = true;    //we create a boolean for while loop
                             while(still_identical && g+counter<column_count){     //we use wihile loop since we dont know how many adjacent symbols there will be
                                 if(matrix[j][g+counter] == symbol){
                                     matrix[j][g+counter] = '-';
                                     counter ++;
                                 }
                                 else{
                                     still_identical = false;
                                 }
                             }
                         }
                     }
                 }
                 for(int a=0;a<matrix[0].size(); a++){ //vertical clearing
                     for(int b=0;b<matrix.size()-2;b++){
                         if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                             int counter2 = 0;
                             char symbol2 = matrix[b][a];
                             bool still_identical2 = true;
                             while (still_identical2 && (b+counter2)<row_count){
                                 if(matrix[b+counter2][a] == symbol2){
                                     matrix[b+counter2][a] = '-';
                                     counter2 ++;
                                 }
                                 else{
                                     still_identical2 = false;
                                 }
                             }
                         }
                     }
                 }
                 
                 for (int i = 0; i < row_count; i++) {
                     for (int j = 0; j < column_count; j++) {
                         cout << matrix[i][j];
                     }
                     cout << endl;
                 }
                 cout << endl;
                 do {
                     cout << "After applying gravity: " << endl;
                     bool gravityContinue = true; // I created a boolean because when i apply gravity I want to check the whole board multiple times since i am reading from top left to bottom right and i can miss applying gravity to the first rows after the character below them falls just after they get checked and they will be floating in the air
                     while(gravityContinue){
                         gravityContinue = false;
                         for(int i=0;i<row_count-1;i++ ){
                             for(int j=0;j<column_count; j++){
                                 if(matrix[i][j] != '-'){
                                     if(matrix[i+1][j] == '-'){
                                         matrix[i+1][j] = matrix[i][j];
                                         matrix[i][j] = '-';
                                         gravityContinue=true; // as long as a character falls i need to repeat checking the upper rows to see if anything is floating
                                     }
                                 }
                             }
                         }
                     }
                     for (int i = 0; i < row_count; i++) {
                         for (int j = 0; j < column_count; j++) {
                             cout << matrix[i][j];
                         }
                         cout << endl;
                     }
                     cout << endl;
                     if(checkerFunction(matrix)){
                         cout << "After clearing matches:" <<endl;
                         for(int j=0; j<matrix.size(); j++){ //horizontal clearing
                             for(int g=0; g<matrix[0].size()-2;g++){
                                 if(matrix[j][g] == matrix[j][g+1] && matrix[j][g+1] == matrix[j][g+2] && matrix[j][g] != '-'){
                                     int counter = 0; //counter for how many symbols are adjacent
                                     char symbol = matrix[j][g];
                                     bool still_identical = true;    //we create a boolean for while loop
                                     while(still_identical){     //we use while loop since we dont know how many adjacent symbols there will be
                                         if(matrix[j][g+counter] == symbol){
                                             matrix[j][g+counter] = '-';
                                             counter ++;
                                         }
                                         else{
                                             still_identical = false;
                                         }
                                     }
                                 }
                             }
                         }
                         for(int a=0;a<matrix[0].size(); a++){ //vertical clearing
                             for(int b=0;b<matrix.size()-2;b++){
                                 if(matrix[b][a] == matrix[b+1][a] && matrix[b+1][a] == matrix[b+2][a] && matrix[b][a] != '-'){
                                     int counter2 = 0;
                                     char symbol2 = matrix[b][a];
                                     bool still_identical2 = true;
                                     while (still_identical2){
                                         if(matrix[b+counter2][a] == symbol2){
                                             matrix[b+counter2][a] = '-';
                                             counter2 ++;
                                         }
                                         else{
                                             still_identical2 = false;
                                         }
                                     }
                                 }
                             }
                         }
                         for (int i = 0; i < row_count; i++) {
                             for (int j = 0; j < column_count; j++) {
                                 cout << matrix[i][j];
                             }
                             cout << endl;
                         }
                         cout << endl;

                         
                     }
                 } while (isGravityAppliable(matrix));
             }
         }
     }
     return 0;
 }
 // 1 1 r         2 2 r         2 1 r              2 1 l              5 2 r



*/
