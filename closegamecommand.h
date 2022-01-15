#ifndef CLOSEGAMECOMMAND_H
#define CLOSEGAMECOMMAND_H
#include <command.h>

class CloseGameCommand: public Command {

public:
    CloseGameCommand(Game* game):Command(game){ };
    void execute() override{
        game->closeGame();
    }
};

#endif // CLOSEGAMECOMMAND_H
