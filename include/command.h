#ifndef COMMAND_H
#define COMMAND_H
#include <game.h>

class Command {       //template command

public:
    Command() { };
    virtual ~Command() { };
    virtual void execute() = 0;
protected:
    Command(Game* ptr):game(ptr) { };
    Game* game;
};

#endif // COMMAND_H
