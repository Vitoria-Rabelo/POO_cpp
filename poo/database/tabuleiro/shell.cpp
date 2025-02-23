#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Player {
    int label;
    int pos;
    bool free;

public:
    Player(int label) : label(label), pos(0), free(true) {}

    int getLabel() {
        return this->label;
    }

    int getPos() {
        return this->pos;
    }

    bool isFree() {
        return this->free;
    }

    void setPos(int pos) {
        this->pos = pos;
    }

    void setFree(bool free) {
        this->free = free;
    }

    string str() const {
        stringstream ss;
        ss << "player" << this->label << ": " << this->pos << (free ? " (free)" : " (trapped)");
        return ss.str();
    }
};

class Board {
    vector<bool> traplist;  
    vector<Player> players; 
    int boardSize;          
    bool running;           
    int currentPlayerIndex;

public:
    
    Board(int nPlayers, int size) : boardSize(size), running(true), currentPlayerIndex(0) {
        traplist.resize(boardSize, false);  
        for (int i = 0; i < nPlayers; i++) {
            players.push_back(Player(i + 1)); 
        }
    }

   
    void addTrap(int pos) {
        if (pos < 0 || pos >= boardSize) {
            cout << "fail: posição inválida\n";
            return;
        }
        traplist[pos] = true;
    }

    void roll(int value) {
        if (!running) {
            cout << "O jogo já acabou.\n";
            return;
        }

        Player& player = players[currentPlayerIndex];
        
        if (!player.isFree() && value % 2 == 0) {
            player.setFree(true);
            cout << "player" << player.getLabel() << " se libertou\n";
        } else if (!player.isFree()) {
            cout << "player" << player.getLabel() << " continua preso\n";
        } else {
            int newPos = player.getPos() + value;
            
            if (newPos >= boardSize) {
                cout << "player" << player.getLabel() << " ganhou\n";
                running = false;
                return;
            }
            
            player.setPos(newPos);
            cout << "player" << player.getLabel() << " andou para " << newPos << "\n";
            
            if (traplist[newPos]) {
                player.setFree(false);
                cout << "player" << player.getLabel() << " caiu em uma armadilha\n";
            }
        }
        
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    void show() {
        for (size_t i = 0; i < players.size(); ++i) {
            cout << "player" << players[i].getLabel() << ": ";
            for (int j = 0; j < boardSize + 1; ++j) {
                if (j == players[i].getPos()) {
                    cout << players[i].getLabel();
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }

        cout << "traps__: ";
        for (int j = 0; j < boardSize + 1; ++j) {
            cout << (traplist[j] ? 'x' : '.');
        }
        cout << "\n";
    }
};

int main() {
    Board board(2, 10);
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int nPlayers, size;
            ss >> nPlayers >> size;
            board = Board(nPlayers, size);
        } else if (cmd == "addTrap") {
            int pos;
            ss >> pos;
            board.addTrap(pos);
        } else if (cmd == "roll") {
            int value;
            ss >> value;
            board.roll(value);
        } else if (cmd == "show") {
            board.show();
        } else {
            cout << "fail: command not found" << endl;
        }
    }
}