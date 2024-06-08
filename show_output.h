#include "study_in_pink2.h"

    static void tc_1278() {
        cout << "----- Testcase 278 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = { Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5) };
        int num_fake_walls = 2;
        Position arr_fake_walls[] = { Position(2, 0), Position(4,0) };

        Map* map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock* sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);

        Watson* watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

        Criminal* criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        BaseItem* excemptionCard = new ExcemptionCard();

        cout << excemptionCard->canUse(criminal, NULL);

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete excemptionCard;
    }

    static void tc_1297() {
        ::tc_1297;
    }
    static void tc_1323() {
        ::tc_1323;
    }
    static void tc_1286() {
        cout << "----- Testcase 286 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = { Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5) };
        int num_fake_walls = 2;
        Position arr_fake_walls[] = { Position(2, 0), Position(4,0) };

        Map* map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock* sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);

        Watson* watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);

        Criminal* criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        BaseItem* passingCard = new PassingCard("all");

        cout << passingCard->canUse(criminal, NULL);

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete passingCard;
    }
    static void tc_1194() {
        cout << "----- Testcase 194 -----" << endl;

        Configuration* config = new Configuration("185.txt");
        cout << "Map Num Rows: " << config->map_num_rows << endl;
        cout << "Map Num Cols: " << config->map_num_cols << endl;
        cout << "Max Num Moving Objects: " << config->max_num_moving_objects << endl;
        cout << "Num Wall: " << config->num_walls << endl;
        if (config->num_walls != 0) {
            cout << "Array Wall: " << config->arr_walls->str() << endl;
        }
        cout << "Num Fake Wall: " << config->num_fake_walls << endl;
        if (config->num_fake_walls != 0) {
            cout << "Array Fake Wall: " << config->arr_fake_walls->str() << endl;
        }
        cout << "Shelock Moving Rule: " << config->sherlock_moving_rule << endl;
        cout << "Sherlock init position: " << config->sherlock_init_pos.str() << endl;
        cout << "Sherlock init hp: " << config->sherlock_init_hp << endl;
        cout << "Sherlock init exp: " << config->sherlock_init_exp << endl;
        cout << "Watson Moving Rule: " << config->watson_moving_rule << endl;
        cout << "Watson init position: " << config->watson_init_pos.str() << endl;
        cout << "Watson init hp: " << config->watson_init_hp << endl;
        cout << "Watson init exp: " << config->watson_init_exp << endl;
        cout << "Criminal init position: " << config->criminal_init_pos.str() << endl;
        cout << "Number step: " << config->num_steps << endl;
        delete config;
    }
    static void tc_1253() {
        cout << "----- Testcase 253 -----" << endl;
        BaseItem* magicBook = new MagicBook();

        delete magicBook;
    }
    static void tc_1354() {
        cout << "----- Testcase 354 -----" << endl;
        int num_walls = 4;
        Position arr_walls[] = { Position(1, 2), Position(2, 3), Position(3, 4), Position(4,5) };
        int num_fake_walls = 2;
        Position arr_fake_walls[] = { Position(2, 0), Position(4,0) };

        Map* map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock* sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 290, 520);

        Watson* watson = new Watson(2, "LU", Position(2, 1), map, 320, 350);

        Criminal* criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        RobotC* robotC = new RobotC(3, Position(1, 4), map, criminal);

        sherlock->move();

        cout << sherlock->str() << endl;

        delete map;
        delete sherlock;
        delete watson;
        delete criminal;
        delete robotC;
    }
};