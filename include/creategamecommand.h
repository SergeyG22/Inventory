#ifndef CREATEGAMECOMMAND_H
#define CREATEGAMECOMMAND_H
#include <command.h>

class CreateGameCommand: public Command {

public:
    CreateGameCommand(Game *game) : Command(game) { }
    void execute()override {
      game->createGame();
    }    
};

#endif // CREATEGAMECOMMAND_H
