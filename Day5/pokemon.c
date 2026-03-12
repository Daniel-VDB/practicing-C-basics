#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PARTY_SIZE 6
#define STAB_BONUS 15
#define CRIT_BONUS 15
#define CRIT_CHANCE 24

// assigning names to types as integers
typedef enum {
    NON, NOR, FIR, WAT, ELE, GRA, ICE, FIG, POI, GRO, FLY, PSY, BUG, ROC, GHO, DRA, DAR, STE, FAI
} Type;

typedef enum {
    HP, ATT, DEF, SPA, SPD, SPE
} stats;

typedef struct {
    char name[50];
    int accuracy; // 1-100
    int power;
    int type;
    bool status;
    bool physical;
} move;


typedef struct {
    char name[50];
    int level;
    int stats[6];
    int buffs[6];
    int damage; // Track the damage they have taken
    int type1;
    int type2;
    move moves[4];
} pokemon;

// Zeroth type is NONE
int type_chart[19][19] = {
        {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  10,  10, 10, 10,  10, 10}, // None
        {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  5,  0, 10, 10,  5, 10}, // Normal
        {10, 10,  5,  5, 10, 20, 20, 10, 10, 10, 10, 10, 20,  5, 10, 10, 10, 20, 10}, // Fire
        {10, 10, 20,  5, 10,  5, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 10, 10}, // Water
        {10, 10, 10, 20,  5,  5, 10, 10, 10,  0, 20, 10, 10, 10, 10, 10, 10,  5, 10}, // Electric
        {10, 10,  5, 20, 10,  5, 10, 10,  5, 20,  5, 10,  5, 20, 10, 10, 10,  5, 10}, // Grass
        {10, 10,  5,  5, 10, 20,  5, 10, 10, 20, 20, 10, 10, 10, 10, 20, 10,  5, 10}, // Ice
        {10, 20, 10, 10, 10, 10, 20, 10,  5, 10,  5,  5,  5, 20,  0, 10, 20, 20,  5}, // Fighting
        {10, 10, 10, 10, 10, 20, 10, 10,  5,  5, 10, 10, 10,  5,  5, 10, 10,  0, 20}, // Poison
        {10, 10, 20, 10, 20,  5, 10, 10, 20, 10,  0, 10,  5, 20, 10, 10, 10, 20, 10}, // Ground
        {10, 10, 10, 10,  5, 20, 10, 20, 10, 10, 10, 10, 20,  5, 10, 10, 10,  5, 10}, // Flying
        {10, 10, 10, 10, 10, 10, 10, 20, 20, 10, 10,  5, 10, 10, 10, 10,  0,  5, 10}, // Psychic
        {10, 10,  5, 10, 10, 20, 10,  5,  5, 10,  5, 20, 10, 10,  5, 10, 20,  5,  5}, // Bug
        {10, 10, 20, 10, 10, 10, 20,  5, 10,  5, 20, 10, 20, 10, 10, 10, 10,  5, 10}, // Rock
        {10,  0, 10, 10, 10, 10, 10,  0, 10, 10, 10, 20, 10, 10, 20, 10,  5, 10,  5}, // Ghost
        {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 20, 10,  5,  0}, // Dragon
        {10, 10, 10, 10, 10, 10, 10,  5, 10, 10, 10, 20, 10, 10,  0, 10, 20,  5,  5}, // Dark
        {10, 10,  5, 10,  5, 10, 20, 10, 10, 10, 10, 10, 10, 20, 10, 10, 10,  5, 20}, // Steel
        {10, 10,  5, 10, 10, 10, 10, 20,  5, 10, 10, 10, 10, 10, 10, 20, 20,  5, 10}, // Fairy
    };

float stat_boost_calculator(int stage);
int damage_calculation(pokemon attacker, pokemon defender, int move_choice); // Returns the damage that should be dealt
int battle_loop(pokemon *player1, pokemon *player2);
int turn_logic(pokemon *player1, pokemon *player2);

int main(void){
    srand(time(NULL));
    
}

float stat_boost_multiplier(int stage){
    if (stage == 0){
        return 1;
    }
    else if (stage < 0)
    {
        return (2 / (2 - stage));
    }
    return ((2 + stage) / 2);
}

int damage_calculation(pokemon attacker, pokemon defender, int move_choice){
    move chosen_move = attacker.moves[move_choice];
    
    // Accuracy
    int hit = rand() % 100;
    if (hit > chosen_move.accuracy){
        printf("It missed!\n");
        return 0;
    }

    // Physical or special
    float attack;
    float defense;
    if (chosen_move.physical){
        attack = attacker.stats[ATT] * stat_boost_calculator(attacker.buffs[ATT]);
        defense = defender.stats[DEF] * stat_boost_calculator(defender.buffs[DEF]);
    } else{
        attack = attacker.stats[SPA] * stat_boost_calculator(attacker.buffs[SPA]);
        defense = defender.stats[SPD] * stat_boost_calculator(defender.buffs[SPD]);
    }

    // Final damage calculation (division delayed to mitigate floating point error)
    float damage;

    damage = ((((2 * attacker.level) + 10) * attacker.moves[move_choice].power * attack) + 100) * hit; // divide by 5 * defense * 50 * 100
    damage /= 5 * defense * 50 * 100;

    // STAB (same type attack bonus)
    if (chosen_move.type == attacker.type1 || chosen_move.type == attacker.type2){
        damage *= STAB_BONUS; // Divide by 10 later
    }

    // Resistances/weaknesses of defender
    int type1_effectivenesss = type_chart[chosen_move.type][defender.type1];
    int type2_effectivenesss = type_chart[chosen_move.type][defender.type2];

    switch (type1_effectivenesss * type2_effectivenesss){
        case 0:
        printf("%s does not affect %s!\n", chosen_move.name, defender.name);
        break;
        case 50:
        printf("It's not very effective\n");
        break;
        case 25:
        printf("It's barely effective\n");
        break;
        case 200:
        printf("It's super effective!\n");
        break;
        case 400:
        printf("It's incredibly effective!\n");
        break;
        default:
        break;
    }

    damage *= type1_effectivenesss; // Divide by 10 later
    damage *= type2_effectivenesss; // Divide by 10 later

    damage /= 10 * 10 * 10;

    // Damage roll
    int roll = (rand() % (80 - 100 + 1)) + 100; // random int between 80 and 100

    damage *= roll; // high or low roll (divided by 100 later)

    // Critical hits
    int crit = rand() * CRIT_CHANCE;

    if (crit = 7){
        damage *= CRIT_BONUS;
    }

    damage /= 10 * 100; // Adjusting for crits and rolls

    return (int) damage;
}