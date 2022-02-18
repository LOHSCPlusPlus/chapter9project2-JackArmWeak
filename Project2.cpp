#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Struct creation for video games
struct VideoGame {
  enum {MAX_CHAR_LEN = 100};
  char Title[MAX_CHAR_LEN];
  double Sales;
  char Platform[MAX_CHAR_LEN];
  char ReleaseDate[MAX_CHAR_LEN];
  char Developer[MAX_CHAR_LEN];
  char Publisher[MAX_CHAR_LEN];
  VideoGame();
};

//Sets Everything to 0
VideoGame::VideoGame() {
  for (int i = 0; i < MAX_CHAR_LEN; i++) {
        Title[i] = '\0';
        Platform[i] = '\0';
        ReleaseDate[i] = '\0';
        Developer[i] = '\0';
        Publisher[i] = '\0';
    }
  Sales = 0.0;
}

//Global const int to define # of video games that can be held.
const int MAX_GAMES = 100;

//Function reads videogames.txt into game and returns it
VideoGame readVideoGame(ifstream &inFile) {
    VideoGame game; 
    inFile.get(game.Title, VideoGame::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> game.Sales;
    inFile.ignore(100,';');
    inFile.get(game.Platform, VideoGame::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile.get(game.ReleaseDate, VideoGame::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile.get(game.Developer, VideoGame::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile.get(game.Publisher, VideoGame::MAX_CHAR_LEN, '\n');
    //Why does this make my program work?
    inFile.ignore(100,'\n');
    return game;
}

//Validates Doubles
double readDouble(const char prompt[]){
    double temp = 0.0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "\nInvalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

//Prints individual games to either screen or file
void printGame(ostream &out, VideoGame gameList){
    out << gameList.Title << ";";
    out << gameList.Sales << ";";
    out << gameList.Platform << ";";
    out << gameList.ReleaseDate << ";";
    out << gameList.Developer << ";";
    out << gameList.Publisher << endl;
}

//Reloads Database
int reload(VideoGame gameList[]) {
  ifstream gameFile("videogames.txt");
  VideoGame tempList[100];
  int temp = 0;
  while(gameFile.peek() != EOF) {
    tempList[temp] = readVideoGame(gameFile);
    temp++;
    }  
  //Resetting list  
  for(int i = 0; i < MAX_GAMES; i++) {
    gameList[i] = tempList[i];
  }
  return temp;
}

//Prints data of all video games to screen
void printAllGames(VideoGame gameList[], int listLength) {
    for(int i = 0; i < listLength; i++) {
      cout << "Index " << i << ": ";
      printGame(cout, gameList[i]);
      cout << endl;
    }
}

//Adds Games
void addGame(VideoGame gameList[], int gameSize) {
  bool isGameAdded = false;
  for(int i = 0; i < MAX_GAMES; i++) {
    double tempDouble = 0.0;
    //Looping until it finds an empty slot for game (should always be at the end of the array)
    if(strcmp(gameList[i].Title,"") == 0) {
      cout << "You are creating game #" << i << endl;

      cout << "Title: ";
      cin.ignore(100,'\n');
      cin.getline(gameList[i].Title,gameSize);

      tempDouble = readDouble("\nSales: ");
      gameList[i].Sales = tempDouble;

      cout << "\nPlatform: ";
      cin.ignore(100,'\n');
      cin.getline(gameList[i].Title,gameSize);

      cout << "\nRelease Date: ";
      cin.getline(gameList[i].ReleaseDate,gameSize);

      cout << "\nDeveloper: ";
      cin.getline(gameList[i].Developer,gameSize);

      cout << "\nPublisher: ";
      cin.getline(gameList[i].Publisher,gameSize);

      cout << endl;

      isGameAdded = true;

      break;
    }
  }
  if(isGameAdded == false) {
    cout << "Sorry! The array is full already" << endl;
  }
}

//Removes Games
void removeGame(VideoGame gameList[], int size) {
  int deleteindex = 0;
  cout << "Which game would you like to delete (0-" << size-1 << "): ";
  cin >> deleteindex;
  for(int i = deleteindex; i < size; i++) {
    gameList[i] = gameList[i+1];
  }
  cout << endl;
  cout << "Sucess! Game " << deleteindex << " has been removed.\n" << endl;
}

//Prints data of specific video games to screen
void printDSGames(VideoGame gameList[], int listLength) {
    for(int i = 0; i < listLength; i++) {
      if(strcmp(gameList[i].Platform,"Nintendo DS") == 0) {
        cout << "Index " << i << ": ";
        printGame(cout, gameList[i]);
        cout << endl;
      }
    }
}

//Prints data of Database to the videogames.txt file
void gameListToFile(const char fileName[], VideoGame gameList[], int listLength) {
    ofstream outFile(fileName);
    for(int i = 0; i < listLength; i++) {
        printGame(outFile, gameList[i]);
    }
}

//Resets videogames.txt
void resetFile(const char fileName[]) {
  ifstream masterFile("mastervideogame.txt");
  ofstream outFile(fileName);
  //Loading mastervideogames.txt into tempList
  int counter = 0;
  VideoGame tempList[MAX_GAMES];
  while(masterFile.peek() != EOF) {
    tempList[counter] = readVideoGame(masterFile);
    counter++;
  }
  //Should print every line of mastervideogames.txt into videogames.txt
  for(int i = 0; i < counter; i++) {
    printGame(outFile, tempList[i]);
  }
}

//Menu function
int menu() {
  int menuChoice = 0;
  int temp = 0;
  cout << "Welcome to our Video Game Database!" << endl;
  cout << "Please choose from the following options: (1, 2, etc)" << endl;
  cout << "1) Reload database from the file" << endl;
  cout << "2) Print database" << endl;
  cout << "3) Add new entry" << endl;
  cout << "4) Remove entry" << endl;
  cout << "5) Print all video games for the Nintendo DS" << endl;
  cout << "6) Save database to the file" << endl;
  cout << "7) Reset file (videogames.txt)" << endl;
  cout << "8) Quit" << endl;
  temp = readDouble("\nInput: ");
  menuChoice = temp;
  cout << endl;
  //Return user choice 
  return menuChoice;
}

int main() {
  //Delcaring Variables
  ifstream gameFile("videogames.txt");
  VideoGame gameList[MAX_GAMES];
  int menuSelect = 0;
  int counter = 0;
  int constantCount = 0;
  //Reading data into gameList from the videogames.txt file
  while(gameFile.peek() != EOF) {
    gameList[counter] = readVideoGame(gameFile);
    counter++;
  }  
  
  menuSelect = menu();

  //Menu Select Tree
  while(menuSelect != 8) {
    switch(menuSelect) {
      //Reload Database
      case 1:
        //redefines counter since Database is being reset
        constantCount = reload(gameList);
        counter = constantCount;
        cout << "Success! Database has been reloaded.\n" << endl;
        break;
      //Print Database
      case 2:
        printAllGames(gameList,counter);
        break;
      //Adding new entry
      case 3:
        addGame(gameList,counter);
        counter++;
        break;
      //Removing entry
      case 4:
        removeGame(gameList,counter);
        counter--;
        break;
      //Print all games for DS
      case 5:
        printDSGames(gameList,counter);
        break;
      //Save current Database back to file
      case 6:
        gameListToFile("videogames.txt", gameList, counter);
        cout << "\nSuccess! The current Database has been transfered to the videogames.txt file.\n" << endl;
        break;
      //Reset videogames.txt file
      case 7:
        resetFile("videogames.txt");
      //Quit
      case 8:
        break;
      //Safety
      default :
        cout << "Invalid Selection! Please Try Again" << endl;
        break;
  }
  menuSelect = menu();
}
}