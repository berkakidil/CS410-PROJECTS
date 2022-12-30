#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// Structure to represent a state in the Turing machine
struct State {
  char Write;
  char Move;
  string Next;
};

int main() {
  // Read in the input file
  ifstream InputFile("Input_BERK_AKIDIL_S010041.txt");
  int InputAlphabetSize;
  InputFile >> InputAlphabetSize;
  string InputAlphabet;
  InputFile >> InputAlphabet;
  int TapeAlphabetSize;
  InputFile >> TapeAlphabetSize;
  string TapeAlphabet;
  InputFile >> TapeAlphabet;
  char BlankSymbol;
  InputFile >> BlankSymbol;
  int NumStates;
  InputFile >> NumStates;
  string States[NumStates];
  for (int i = 1; i <= NumStates; i++) {
    InputFile >> States[i-1];
  }
  string StartState;
  InputFile >> StartState;
  string AcceptState;
  InputFile >> AcceptState;
  string RejectState;
  InputFile >> RejectState;

  // Initialize the state diagram
  map<string, State> StateDiagram;
  string CurrentState;
  char CurrentSymbol;
  while (InputFile >> CurrentState >> CurrentSymbol) {
    State Current;
    InputFile >> Current.Write >> Current.Move >> Current.Next;
    StateDiagram[CurrentState + CurrentSymbol] = Current;
  }

// Simulate the Turing machine
  string Tape;
  InputFile >> Tape;
  string VisitedStates;
  string Current = StartState;
  int TapePos = 0;
  while (Current != AcceptState && Current != RejectState) {
    // Process the current state
    VisitedStates += Current + " ";
    State Next = StateDiagram[Current + Tape[TapePos]];
    Tape[TapePos] = Next.Write;
    if (Next.Move == 'L') {
      TapePos--;
      if (0 > TapePos) {
        // Add a blank symbol to the left of the tape if we move left past the beginning of the tape
        Tape = BlankSymbol + Tape;
        TapePos = 0;
      }
    }
    else if (Next.Move == 'R') {
      TapePos++;
      if (Tape.length() <= TapePos) {
        // Add a blank symbol to the right of the tape if we move right past the end of the tape
        Tape += BlankSymbol;
      }
    }
    Current = Next.Next;
  }

  // Output the result
  cout << "ROUT: " << VisitedStates << endl;
  if (Current == AcceptState) {
    cout << "RESULT: accepted" << endl;
  }
  else
  {
    cout << "RESULT: rejected" << endl;
  }

  return 0;
}