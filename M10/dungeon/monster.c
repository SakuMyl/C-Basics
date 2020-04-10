/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"
#ifndef ABS
#define ABS(x) ((x) >= 0 ? x : -(x))
#endif

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20},
    { "", 0, 0, 0 }
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}



/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */

void move(const Game *game, Creature *monst, int towards)
{
    Point mPos = monst->pos;
    Point pPos = game->position;
    int xDiff = pPos.x - mPos.x;
    int yDiff = pPos.y - mPos.y;
    int xDir = xDiff > 0 ? 1 : -1;
    int yDir = yDiff > 0 ? 1 : -1;
    if (!towards) {
        xDir = -xDir;
        yDir = -yDir;
    }
    int xBlocked = isBlocked(game, mPos.x + xDir, mPos.y);
    int yBlocked = isBlocked(game, mPos.x, mPos.y + yDir);
    if (((ABS(xDiff) > ABS(yDiff)) || yBlocked) && !xBlocked) monst->pos.x += xDir;
    else if (!yBlocked) monst->pos.y += yDir;
}

void moveTowards(const Game *game, Creature *monst) {
    move(game, monst, 1);
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(const Game *game, Creature *monst) {
	move(game, monst, 0);
}


int nextToPlayer(Game *game, Creature *monster)
{
    Point *pPos = &game->position;
    Point *mPos = &monster->pos;
    return ABS(mPos->x - pPos->x) + ABS(mPos->y - pPos->y) == 1;
}

/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
    Creature *m = game->monsters;
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        if (m[i].hp > 0) {
            if (nextToPlayer(game, &m[i]) && m[i].attack) m[i].attack(game, &m[i]);
            else if (m[i].move) m[i].move(game, &m[i]);
        }
    }       
}



/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
    Options *opts = &game->opts;
    unsigned int numMonsters = opts->numMonsters;
    Creature *monsters = malloc(numMonsters * sizeof(Creature));
    if (!monsters) return;
    unsigned int width = opts->mapWidth;
    unsigned int height = opts->mapHeight;
    unsigned int size = width * height;
    // Indices of valid positions in the map
    int validSpots[size];
    unsigned int validSpotCount = 0;
    for (unsigned int i = 0; i < size; i++) {
        Point pos = { i % width, i / width };
        if (game->map.tile[pos.y][pos.x] != TILE_WALL && !cmpPos(game->position, pos)) {
            validSpots[validSpotCount++] = i;
        }
    }
    if (validSpotCount < numMonsters) return;
    // Get random indices for the monsters' locations from the set of valid indices
    for (unsigned int i = 0; i < validSpotCount; i++) {
        unsigned int index = rand() % (validSpotCount - i) + i;
        unsigned int temp = validSpots[index];
        validSpots[index] = validSpots[i];
        validSpots[i] = temp;
    }
    int nofTypes = 0;
    for (; types[nofTypes].name[0] != 0; nofTypes++);
    for (unsigned int i = 0; i < numMonsters; i++) {
        MonstType m = types[rand() % nofTypes];
        Creature c;
        strcpy(c.name, m.name);
        c.sign = m.sign;
        Point p = { validSpots[i] % width, validSpots[i] / width };
        c.pos = p; 
        c.maxhp = m.hplow + rand() % (m.hphigh - m.hplow + 1);
        c.hp = c.maxhp;
        c.attack = attackPunch;
        c.move = NULL;
        monsters[i] = c;
    }
    game->numMonsters = numMonsters;
    game->monsters = monsters;
    printMap(game);
}
/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
