//
// Created by zacky on 9/3/2021.
//

#ifndef CHESS_UCI_H
#define CHESS_UCI_H

#include "vector"
#include "ai.h"


struct uci{
private:
    // constants that are useful such as fen strings and such
    std::string Default = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    const int posX =450, posY = 30, width = 1000, height = 1000;
public:
    uci();

    /*
     * the main loop that checks for something to be inputed
     */
    void mainloop();

    /*
     * takes the string and then checks what it is and does its intended function
     * @param str, the string that is being inputed
     */
    void processCommand(std::string str);

    /*
     * seperates a string so it can be used
     * @param str, the string that is being inputed
     */
    std::vector<std::string> getSeperate(std::string str);

    void isReady();

    void stop();
    static void Uci();

    void position_fen(std::string fen);
    void moves(std::string moves);

    void go(int depth, int timeLimit);

    void print();

    void set_option(std::string& name, std::string& value);

    board Board;
};
#endif //CHESS_UCI_H
