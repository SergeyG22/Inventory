#ifndef STOPGAMECOMMAND_H
#define STOPGAMECOMMAND_H
#include <command.h>

class StopGameCommand : public Command {

public:
    StopGameCommand(Game* game):Command(game){ };
    void execute()override {
        game->stopGame();
    }
};

#endif // STOPGAMECOMMAND_H
