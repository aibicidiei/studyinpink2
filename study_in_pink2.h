// /*
//  * Ho Chi Minh City University of Technology
//  * Faculty of Computer Science and Engineering
//  * Initial code for Assignment 1
//  * Programming Fundamentals Spring 2023
//  * Author: Vu Van Tien
//  * Date: 02.02.2023
//  */

// // The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

// ////////////////////////////////////////////////////////////////////////
// /// STUDENT'S ANSWER BEGINS HERE
// /// Complete the following functions
// /// DO NOT modify any parameters in the functions.
// ////////////////////////////////////////////////////////////////////////

using namespace std;
// // Forward declaration
class MovingObject;
class Position;
// class Configuration;
class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
 class SherlockBag;
 class WatsonBag;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};
class MapElement
{
protected:
    ElementType type;

public:
    MapElement(ElementType in_type) : type(in_type) {}
    virtual ~MapElement() {}
    virtual ElementType getType() const { return type; }
    virtual bool isPassable() const { return true; } 
};
class Path : public MapElement
{
public:
    Path() : MapElement(ElementType::PATH) {}
    bool isPassable() const override { return true; }
};
class Wall : public MapElement
{
public:
    Wall() : MapElement(ElementType::WALL) {}
    bool isPassable() const override { return false; } 
};
class FakeWall : public MapElement
{
private:
    int req_exp;

public:
    FakeWall(int r, int c) : MapElement(FAKE_WALL)
    {
        req_exp = (r * 257 + c * 139 + 89) % 900 + 1;
    }
    int getReqExp() const { return req_exp; }
    bool isPassable() const override { return false; }
};
class Position
{
private:
    int r;
    int c;

public:
   
    Position(int r = 0, int c = 0) : r(r), c(c) {}

  
    Position(const std::string &str_pos)
    {
        
        std::stringstream ss(str_pos);
        char ignore;
        ss >> ignore >> r >> ignore >> c >> ignore;
    }

    int getRow() const
    {
        return r;
    }

 
    int getCol() const
    {
        return c;
    }


    void setRow(int r)
    {
        this->r = r;
    }


    void setCol(int c)
    {
        this->c = c;
    }

 
    std::string str() const
    {
        std::stringstream ss;
        ss << "(" << r << "," << c << ")";
        return ss.str();
    }

   
    bool isEqual(int in_r, int in_c) const
    {
        return r == in_r && c == in_c;
    }


    static const Position npos;

    bool operator==(const Position &other) const
    {
        return r == other.r && c == other.c;
    }

    bool operator!=(const Position &other) const
    {
        return !(*this == other);
    }
};
class Map {
private:
    int num_rows;
    int num_cols;
    MapElement*** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols) {

        map = new MapElement * *[num_rows];
        for (int i = 0; i < num_rows; ++i) {
            map[i] = new MapElement * [num_cols];
            for (int j = 0; j < num_cols; ++j) {
                map[i][j] = new Path();
            }
        }

        for (int i = 0; i < num_walls; ++i) {
            int r = array_walls[i].getRow();
            int c = array_walls[i].getCol();
            if (r >= 0 && r < num_rows && c >= 0 && c < num_cols) {
                delete map[r][c];
                map[r][c] = new Wall();
            }
        }

        for (int i = 0; i < num_fake_walls; ++i) {
            int r = array_fake_walls[i].getRow();
            int c = array_fake_walls[i].getCol();
            if (r >= 0 && r < num_rows && c >= 0 && c < num_cols) {
                delete map[r][c];
                map[r][c] = new FakeWall(r, c);
            }
        }
    }

    ~Map() {
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }

    bool isValid(const Position& pos, const void* character) const {
        int r = pos.getRow();
        int c = pos.getCol();

        if (r < 0 || r >= num_rows || c < 0 || c >= num_cols) {
            return false;
        }
        return map[r][c]->isPassable();
    }
};
class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    std::string name;

public:
    MovingObject(int index, const Position pos, Map *map, const std::string &name = "")
        : index(index), pos(pos), map(map), name(name) {}

    virtual ~MovingObject() {}

    virtual Position getNextPosition() = 0;

    Position getCurrentPosition() const
    {
        return pos;
    }

    virtual void move() = 0;

    virtual std::string str() const = 0;
};
class Character : public MovingObject {
protected:
    int hp;
    int exp;
    int maxHp;
    string name;
public:
    Character(int index, const Position pos, Map* map, const std::string& name = "")
        : MovingObject(index, pos, map, name), hp(0), exp(0) {}
    virtual Position getNextPosition() override = 0;
    virtual void move() override = 0;
    virtual string str() const override = 0;

    void increaseHp(int amount) { hp = std::min(hp + amount, 500); }
    void increaseExp(int amount) { exp = std::min(exp + amount, 900); }
    void decreaseExp(int amount) { exp = std::max(exp - amount, 0); }

    int getHp() const { return hp; }
    int getExp() const { return exp; }
    string getName() const { return name; }
    void setExp(int exp) { this->exp = exp; }
    void setHp(int hp) { this->hp = hp; }
}; 
class Sherlock : public Character
{
private:
    string moving_rule;
    int hp;
    int exp;
    int current_step;
public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), current_step(0)
    {
       
        hp = max(0, min(hp, 500));
        exp = max(0, min(exp, 900));
    }

    static const Position npos;

    virtual Position getNextPosition() override {
        if (moving_rule.empty())
            return npos;

        Position next_pos = pos;
        char direction = moving_rule[current_step % moving_rule.size()]; // Cycle through the moving rule
        switch (direction) {
        case 'L':
            next_pos.setCol(next_pos.getCol() - 1);
            break;
        case 'R':
            next_pos.setCol(next_pos.getCol() + 1);
            break;
        case 'U':
            next_pos.setRow(next_pos.getRow() - 1);
            break;
        case 'D':
            next_pos.setRow(next_pos.getRow() + 1);
            break;
        }

        current_step++; // Move to the next step

        if (!map->isValid(next_pos, this))
            return npos;
        return next_pos;
    }

    
    virtual void move() override
    {
        Position next_pos = getNextPosition(); 
        if (next_pos != npos)
        {                   
            pos = next_pos; 
        }
    }

    
    virtual string str() const override
    {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Sherlock() = default ;
   
};
class Watson : public Character {
private:
    string moving_rule;
    int hp;
    int exp;
    int current_step;

public:
    Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), current_step(0)
    {

        hp = max(0, min(hp, 500));
        exp = max(0, min(exp, 900));
    }

    static const Position npos;

    virtual Position getNextPosition() override {
        if (moving_rule.empty())
            return npos;

        Position next_pos = pos;
        char direction = moving_rule[current_step % moving_rule.size()];
        switch (direction) {
        case 'L':
            next_pos.setCol(next_pos.getCol() - 1);
            break;
        case 'R':
            next_pos.setCol(next_pos.getCol() + 1);
            break;
        case 'U':
            next_pos.setRow(next_pos.getRow() - 1);
            break;
        case 'D':
            next_pos.setRow(next_pos.getRow() + 1);
            break;
        }

        current_step++; // Move to the next step

        if (!map->isValid(next_pos, this))
            return npos;
        return next_pos;
    }


    virtual void move() override
    {
        Position next_pos = getNextPosition();
        if (next_pos != npos)
        {
            pos = next_pos;
        }
    }

    virtual string str() const override {
        return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }
    ~Watson() = default;
};
class Criminal : public Character
{
private:
    Sherlock *sherlock;
    Watson *watson;
    static const int NUM_DIRECTIONS = 4;
    
public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
        : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson) {}

    static const Position directions[NUM_DIRECTIONS];
    static const Position npos;
    virtual Position getNextPosition() override
    {
        Position best_pos = npos;
        int max_distance = -1;

        for (int i = 0; i < NUM_DIRECTIONS; ++i)
        {
            Position next_pos(pos.getRow() + directions[i].getRow(), pos.getCol() + directions[i].getCol());
            if (map->isValid(next_pos, this))
            {
                int distance =
                    abs(next_pos.getRow() - sherlock->getCurrentPosition().getRow()) +
                    abs(next_pos.getCol() - sherlock->getCurrentPosition().getCol()) +
                    abs(next_pos.getRow() - watson->getCurrentPosition().getRow()) +
                    abs(next_pos.getCol() - watson->getCurrentPosition().getCol());
                if (distance > max_distance)
                {
                    max_distance = distance;
                    best_pos = next_pos;
                }
            }
        }

        return best_pos;
    }

    virtual void move() override
    {
        Position next_pos = getNextPosition(); 
        if (next_pos != npos)
        {                   
            pos = next_pos; 
        }
    }

    virtual string str() const override
    {
        return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
    }
    ~Criminal() = default;
};
class ArrayMovingObject
{
private:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
   
    ArrayMovingObject(int capacity) : count(0), capacity(capacity)
    {
        arr_mv_objs = new MovingObject *[capacity];
    }

   
    ~ArrayMovingObject() = default;
   
    bool isFull() const
    {
        return count == capacity;
    }

    bool add(MovingObject *mv_obj)
    {
        if (isFull())
        {
            return false;
        }
        arr_mv_objs[count++] = mv_obj;
        return true;
    }


    std::string str() const
    {
        std::string result = "ArrayMovingObject[count=" + std::to_string(count) +
                             ";capacity=" + std::to_string(capacity) + ";";
        for (int i = 0; i < count; ++i)
        {
            result += arr_mv_objs[i]->str(); 
            if (i != count - 1)
            {
                result += ";";
            }
        }
        result += "]";
        return result;
    }
};
class Configuration
{
friend class StudyPinkProgram;
private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int walls_capacity; 
    int num_fake_walls;
    Position *arr_fake_walls;
    int fake_walls_capacity; 
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;
    string map_file_path;

    void addWall(const Position &pos)
    {
        if (num_walls >= walls_capacity)
        {
            walls_capacity *= 2;
            Position *new_arr = new Position[walls_capacity];
            for (int i = 0; i < num_walls; ++i)
            {
                new_arr[i] = arr_walls[i];
            }
            delete[] arr_walls;
            arr_walls = new_arr;
        }
        arr_walls[num_walls++] = pos;
    }

    void addFakeWall(const Position &pos)
    {
        if (num_fake_walls >= fake_walls_capacity)
        {
            fake_walls_capacity *= 2;
            Position *new_arr = new Position[fake_walls_capacity];
            for (int i = 0; i < num_fake_walls; ++i)
            {
                new_arr[i] = arr_fake_walls[i];
            }
            delete[] arr_fake_walls;
            arr_fake_walls = new_arr;
        }
        arr_fake_walls[num_fake_walls++] = pos;
    }

public:
    Configuration(const std::string& filepath)
        : map_num_rows(0), map_num_cols(0), max_num_moving_objects(0),
        num_walls(0), arr_walls(nullptr), walls_capacity(10), num_fake_walls(0), arr_fake_walls(nullptr), fake_walls_capacity(10),
        sherlock_moving_rule(""), sherlock_init_pos(), sherlock_init_hp(0), sherlock_init_exp(0),
        watson_moving_rule(""), watson_init_pos(), watson_init_hp(0), watson_init_exp(0),
        criminal_init_pos(), num_steps(0), map_file_path("")
    {

        arr_walls = new Position[walls_capacity];
        arr_fake_walls = new Position[fake_walls_capacity];

        ifstream file(filepath);
        if (!file.is_open())
        {
            throw runtime_error("Cannot open configuration file.");
        }

        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string key;
            if (getline(iss, key, '='))
            {
                string value;
                if (getline(iss, value))
                {
                    if (key == "MAP_NUM_ROWS")
                    {
                        map_num_rows = stoi(value);
                    }
                    else if (key == "MAP_NUM_COLS")
                    {
                        map_num_cols = stoi(value);
                    }
                    else if (key == "MAX_NUM_MOVING_OBJECTS")
                    {
                        max_num_moving_objects = stoi(value);
                    }
                    else if (key == "ARRAY_WALLS")
                    {
                        value = value.substr(1, value.size() - 2); // Remove the square brackets
                        istringstream wallStream(value);
                        string position;
                        while (getline(wallStream, position, ';'))
                        {
                            position = position.substr(1, position.size() - 2); // Remove the parentheses
                            int row, col;
                            sscanf(position.c_str(), "%d,%d", &row, &col);
                            addWall(Position(row, col));
                        }
                    }
                    else if (key == "ARRAY_FAKE_WALLS")
                    {
                        value = value.substr(1, value.size() - 2); // Remove the square brackets
                        istringstream fakeWallStream(value);
                        string position;
                        while (getline(fakeWallStream, position, ';'))
                        {
                            position = position.substr(1, position.size() - 2); // Remove the parentheses
                            int row, col;
                            sscanf(position.c_str(), "%d,%d", &row, &col);
                            addFakeWall(Position(row, col));
                        }
                    }
                    else if (key == "SHERLOCK_MOVING_RULE")
                    {
                        sherlock_moving_rule = value;
                    }
                    else if (key == "SHERLOCK_INIT_POS")
                    {
                        int row, col;
                        sscanf(value.c_str(), "(%d,%d)", &row, &col);
                        sherlock_init_pos = Position(row, col);
                    }
                    else if (key == "SHERLOCK_INIT_HP")
                    {
                        sherlock_init_hp = stoi(value);
                    }
                    else if (key == "SHERLOCK_INIT_EXP")
                    {
                        sherlock_init_exp = stoi(value);
                    }
                    else if (key == "WATSON_MOVING_RULE")
                    {
                        watson_moving_rule = value;
                    }
                    else if (key == "WATSON_INIT_POS")
                    {
                        int row, col;
                        sscanf(value.c_str(), "(%d,%d)", &row, &col);
                        watson_init_pos = Position(row, col);
                    }
                    else if (key == "WATSON_INIT_HP")
                    {
                        watson_init_hp = stoi(value);
                    }
                    else if (key == "WATSON_INIT_EXP")
                    {
                        watson_init_exp = stoi(value);
                    }
                    else if (key == "CRIMINAL_INIT_POS")
                    {
                        int row, col;
                        sscanf(value.c_str(), "(%d,%d)", &row, &col);
                        criminal_init_pos = Position(row, col);
                    }
                    else if (key == "NUM_STEPS")
                    {
                        num_steps = stoi(value);
                    }
                    else if (key == "MAP_FILE_PATH")
                    {
                        map_file_path = value;
                    }
					
                }
            }
        }

        file.close();
    }
    string getMapFilePath() const {
        return map_file_path;
    }
    ~Configuration()
    {
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

    int getMapNumRows() const { return map_num_rows; }
    int getMapNumCols() const { return map_num_cols; }
    int getMaxNumMovingObjects() const { return max_num_moving_objects; }
    int getNumWalls() const { return num_walls; }
    const Position *getArrWalls() const { return arr_walls; }
    int getNumFakeWalls() const { return num_fake_walls; }
    const Position *getArrFakeWalls() const { return arr_fake_walls; }
    string getSherlockMovingRule() const { return sherlock_moving_rule; }
    Position getSherlockInitPos() const { return sherlock_init_pos; }
    int getSherlockInitHp() const { return sherlock_init_hp; }
    int getSherlockInitExp() const { return sherlock_init_exp; }
    string getWatsonMovingRule() const { return watson_moving_rule; }
    Position getWatsonInitPos() const { return watson_init_pos; }
    int getWatsonInitHp() const { return watson_init_hp; }
    int getWatsonInitExp() const { return watson_init_exp; }
    Position getCriminalInitPos() const { return criminal_init_pos; }
    int getNumSteps() const { return num_steps; }

    string str() const
    {
        ostringstream oss;
        oss << "Configuration[" << endl;
        oss << "MAP_NUM_ROWS=" << map_num_rows << endl;
        oss << "MAP_NUM_COLS=" << map_num_cols << endl;
        oss << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << endl;
        oss << "NUM_WALLS=" << num_walls << endl;
        oss << "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; ++i)
        {
            if (i > 0)
                oss << ";";
            oss << arr_walls[i].str();
        }
        oss << "]" << endl;
        oss << "NUM_FAKE_WALLS=" << num_fake_walls << endl;
        oss << "ARRAY_FAKE_WALLS=[";
        for (int i = 0; i < num_fake_walls; ++i)
        {
            if (i > 0)
                oss << ";";
            oss << arr_fake_walls[i].str();
        }
        oss << "]" << endl;
        oss << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << endl;
        oss << "SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << endl;
        oss << "SHERLOCK_INIT_HP=" << sherlock_init_hp << endl;
        oss << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << endl;
        oss << "WATSON_MOVING_RULE=" << watson_moving_rule << endl;
        oss << "WATSON_INIT_POS=" << watson_init_pos.str() << endl;
        oss << "WATSON_INIT_HP=" << watson_init_hp << endl;
        oss << "WATSON_INIT_EXP=" << watson_init_exp << endl;
        oss << "CRIMINAL_INIT_POS=" << criminal_init_pos.str() << endl;
        oss << "NUM_STEPS=" << num_steps << endl;
        oss << "]";
        return oss.str();
    }
};
class Robot : public MovingObject {
public:
    Robot(int index,const Position& init_pos, Map* map, Criminal* criminal)
        : MovingObject(index, init_pos, map, "Robot"), criminal(criminal) {}

    virtual Position getNextPosition() override = 0;  // Pure virtual function making Robot an abstract class

    virtual void move() override {
        Position next_pos = getNextPosition();
        if (next_pos != Position::npos) {
            pos = next_pos;
        }
    }
    string getCurrentChallenge() const {
        return currentChallenge;
    }
    void setCurrentChallenge(const string& challenge) {
        currentChallenge = challenge;
        challengeBypassed = false; 
    }
    void bypassChallenge() {
        challengeBypassed = true;
        currentChallenge.clear();
    } 
    bool isChallengeBypassed() const {
		return challengeBypassed;
	}
    virtual string str() const override {
        return "Robot[index=" + std::to_string(index) + ";pos=" + pos.str() + "]";
    }
    int getChallengeHpPenalty() const {
        return challengeHpPenalty;
    }

    int getChallengeExpPenalty() const {
        return challengeExpPenalty;
    }


protected:
    virtual int getDistanceToSherlock(Sherlock* sherlock) const {
        return calculateDistance(this->pos, sherlock->getCurrentPosition());
    }

    virtual int getDistanceToWatson(Watson* watson) const {
        return calculateDistance(this->pos, watson->getCurrentPosition());
    }

    Criminal* criminal;  

private:
    virtual int calculateDistance(const Position& pos1, const Position& pos2) const {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
    string currentChallenge;
    bool challengeBypassed;
    int challengeHpPenalty;
    int challengeExpPenalty;
};
class RobotC : public Robot {
public:
    RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal)
        : Robot(index, init_pos, map, criminal) {}

    ~RobotC() = default;

    Position getNextPosition() override {
        Position next_pos = pos; 

        // Example: Move towards the criminal
        if (criminal->getCurrentPosition().getRow() > pos.getRow()) {
            next_pos.setRow(pos.getRow() + 1);
        }
        else if (criminal->getCurrentPosition().getRow() < pos.getRow()) {
            next_pos.setRow(pos.getRow() - 1);
        }
        else if (criminal->getCurrentPosition().getCol() > pos.getCol()) {
            next_pos.setCol(pos.getCol() + 1);
        }
        else if (criminal->getCurrentPosition().getCol() < pos.getCol()) {
            next_pos.setCol(pos.getCol() - 1);
        }

        // Ensure the next position is valid
        if (map->isValid(next_pos, this)) {
            return next_pos;
        }
        return Position::npos;  // Return an invalid position if no valid move is found
    }
    string str() const override {
        return "Robot[pos=" + pos.str() + ";type=C;dist=]";
    }
protected:
    int getDistanceToSherlock(Sherlock* sherlock) const override {
        return calculateDistance(this->pos, sherlock->getCurrentPosition());
    }

    int getDistanceToWatson(Watson* watson) const override {
        return calculateDistance(this->pos, watson->getCurrentPosition());
    }

private:
    Sherlock* sherlock;
    Watson* watson;

    int calculateDistance(const Position& pos1, const Position& pos2) const {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
};
class RobotS : public Robot {
public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
        : Robot(index, init_pos, map, criminal), sherlock(sherlock) {}

    ~RobotS() = default;

    Position getNextPosition() override {
        Position sherlock_pos = sherlock->getCurrentPosition();
        int row_diff = sherlock_pos.getRow() - pos.getRow();
        int col_diff = sherlock_pos.getCol() - pos.getCol();

        if (abs(row_diff) > abs(col_diff)) {
            return Position(pos.getRow() + (row_diff > 0 ? 1 : -1), pos.getCol());
        }
        else {
            return Position(pos.getRow(), pos.getCol() + (col_diff > 0 ? 1 : -1));
        }
    }

    int getDistanceToSherlock(Sherlock* sherlock) const override {
        return calculateDistance(pos, sherlock->getCurrentPosition());
    }

    string str() const override {
        int distanceToSherlock = calculateDistance(pos, sherlock->getCurrentPosition());
        return "Robot[pos=" + pos.str() + ";type=S;dist=" + std::to_string(distanceToSherlock) + "]";
    }

private:
    Sherlock* sherlock;

    int calculateDistance(const Position& pos1, const Position& pos2) const {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
};
class RobotW : public Robot {
public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
        : Robot(index, init_pos, map, criminal), watson(watson) {}

    ~RobotW() = default;

    Position getNextPosition() override {
        
        Position watson_pos = watson->getCurrentPosition();
        int row_diff = watson_pos.getRow() - pos.getRow();
        int col_diff = watson_pos.getCol() - pos.getCol();

        if (abs(row_diff) > abs(col_diff)) {
            return Position(pos.getRow() + (row_diff > 0 ? 1 : -1), pos.getCol());
        }
        else {
            return Position(pos.getRow(), pos.getCol() + (col_diff > 0 ? 1 : -1));
        }
    }

    int getDistanceToWatson(Watson* watson) const {
        return calculateDistance(pos, watson->getCurrentPosition());
    }

    string str() const override {
        int distanceToWatson = calculateDistance(pos, watson->getCurrentPosition());
        return "Robot[pos=" + pos.str() + ";type=W;dist=" + std::to_string(distanceToWatson) + "]";
    }

private:
    Watson* watson;

    int calculateDistance(const Position& pos1, const Position& pos2) const {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
};
class RobotSW : public Robot {
public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)
        : Robot(index, init_pos, map, criminal), sherlock(sherlock), watson(watson) {}
    ~RobotSW() = default;

    Position getNextPosition() override {
        Position sherlock_pos = sherlock->getCurrentPosition();
        Position watson_pos = watson->getCurrentPosition();

        int avg_row = (sherlock_pos.getRow() + watson_pos.getRow()) / 2;
        int avg_col = (sherlock_pos.getCol() + watson_pos.getCol()) / 2;

        int row_diff = avg_row - pos.getRow();
        int col_diff = avg_col - pos.getCol();

        if (abs(row_diff) > abs(col_diff)) {
            return Position(pos.getRow() + (row_diff > 0 ? 1 : -1), pos.getCol());
        }
        else {
            return Position(pos.getRow(), pos.getCol() + (col_diff > 0 ? 1 : -1));
        }
    }

    int getDistanceToSherlock() const {
        return calculateDistance(pos, sherlock->getCurrentPosition());
    }

    int getDistanceToWatson() const {
        return calculateDistance(pos, watson->getCurrentPosition());
    }

    int getTotalDistance() const {
        return getDistanceToSherlock() + getDistanceToWatson();
    }

    std::string str() const override {
        int totalDistance = getTotalDistance();
        return "Robot[pos=" + pos.str() + ";type=SW;dist=" + std::to_string(totalDistance) + "]";
    }

private:
    Sherlock* sherlock;
    Watson* watson;

    int calculateDistance(const Position& pos1, const Position& pos2) const {
        return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    }
};
class BaseItem {
public:
    BaseItem(int id, const string& name): id(id), name(name) {}
    virtual ~BaseItem() = default;
    virtual int getId() const {return id; }
    virtual string getName() const { return name; }
    virtual void setId(int newId) {id = newId;}
    virtual void setName(const string& newName) { name = newName;}
    virtual string str() const { return "BaseItem[id=" + std::to_string(id) + ";name=" + name + "]";}
    virtual bool canUse(Character* obj, Robot* robot) = 0;
    virtual void use(Character* obj, Robot* robot) = 0;
    virtual ItemType getItemType() const = 0;
    virtual string getItemName() const = 0;
private:
    int id;
    string name;
};
class MagicBook : public BaseItem {
public:
    MagicBook(int id, const string& name): BaseItem(id, name) {}

    bool canUse(Character* obj, Robot* robot) override {
        return robot == nullptr && obj->getExp() <= 350;
    }

    void use(Character* obj, Robot* robot) override {
        if (robot == nullptr && obj->getExp() <= 350) {
            obj->increaseExp(obj->getExp() * 0.25); // Increase exp by 25%
        }
    }
    ~MagicBook() = default;
    string getName() const  { return "MagicBook";}
};
class EnergyDrink : public BaseItem {
public:
    bool canUse(Character* obj, Robot* robot)  {
       return obj->getHp() <= 100;
   }

   void use(Character* obj, Robot* robot)  {
        obj->increaseHp(obj->getHp() * 0.2);
    }

   ~EnergyDrink() = default;

   string getName() const  {
        return "EnergyDrink";
    }
};
class FirstAid : public BaseItem {
public:
   bool canUse(Character* obj, Robot* robot)  {
       return obj->getHp() <= 100 || obj->getExp() <= 350;
   }
   void use(Character* obj, Robot* robot)  {
       obj->increaseHp(obj->getHp() * 0.5);    }
   string getName() const override {
       return "FirstAid";}
   ~FirstAid() = default;
};
class ExcemptionCard : public BaseItem {
public:
    ExcemptionCard(int id, const string& name) : BaseItem(id, name) {}

    virtual bool canUse(Character* obj, Robot* robot) override {
        return obj->getName() == "Sherlock" && (obj->getHp() % 2 != 0);
    }
    virtual void use(Character* obj, Robot* robot) override {
        if (canUse(obj, robot)) {
            obj->setHp(obj->getHp() + robot->getChallengeHpPenalty());
            obj->setExp(obj->getExp() + robot->getChallengeExpPenalty());
            robot->bypassChallenge();
        }
    }
    ~ExcemptionCard() = default;
    string getName() const override {
           return "ExemptionCard";}

};
class PassingCard : public BaseItem {
private:
    string challenge;
public:
    PassingCard(int id, const string& name, const string& challenge)
        : BaseItem(id, name), challenge(challenge) {}
 
    bool canUse(Character* obj, Robot* robot) {
        return obj->getName() == "Watson" && (obj->getHp() % 2 == 0);
    }
    virtual void use(Character* obj, Robot* robot) override {
        if (canUse(obj, robot)) {
            string currentChallenge = robot->getCurrentChallenge();  // Assuming Robot has a method to get the current challenge
            if (challenge != "all" && challenge != currentChallenge) {
                // Apply a penalty of 50 EXP to the character if the challenge types do not match
                obj->setExp(obj->getExp() - 50);
            }
            // Bypass the challenge regardless of the match
            // Assuming there's a method to mark the challenge as bypassed
            robot->bypassChallenge();
        }
    }
    string getChallenge() const {
        return challenge;
    }

    string str() const {
        return "PassingCard[id=" + std::to_string(getId()) + ";name=" + getName() + ";challenge=" + challenge + "]";
    }
    ~PassingCard() = default;
 
};
int calculateDigitSum(int n);
string createItem(int i, int j);
const ItemType PassingCardType = ItemType::PASSING_CARD;
const ItemType ExceptionCardType = ItemType::EXCEMPTION_CARD;
class Node {
 public:
    BaseItem* data;
    Node* next;
    Node(BaseItem* item) : data(item), next(nullptr) {}
};
class BaseBag {
protected:
    Character* owner;
    Node* head;  // Head of the linked list
    int itemCount;  // Count of items in the bag

public:
    BaseBag(Character* owner) : owner(owner), head(nullptr), itemCount(0) {}
    
    virtual bool insert(BaseItem* item) {
        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        itemCount++;
        return true;
    }

    virtual BaseItem* get() {
        if (!head) return nullptr;

        Node* current = head;
        Node* previous = nullptr;

        while (current && !canUse(current->data)) {
            previous = current;
            current = current->next;
        }

        if (!current) return nullptr;

        BaseItem* itemToUse = current->data;

        if (previous) {
            previous->next = current->next;
        }
        else {
            head = current->next;
        }

        delete current;
        itemCount--;
        return itemToUse;
    }

    virtual BaseItem* get(ItemType itemType) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data->getItemType() == itemType) {
                BaseItem* itemToUse = current->data;

                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }

                delete current;
                itemCount--;
                return itemToUse;
            }
            previous = current;
            current = current->next;
        }

        return nullptr;
    }

    virtual std::string str() const {
        std::string result = "Bag[count=" + std::to_string(itemCount) + ";";
        Node* current = head;
        while (current) {
            result += current->data->getItemName() + ",";
            current = current->next;
        }
        if (itemCount > 0) result.pop_back();
        result += "]";
        return result;
    }

    virtual bool canUse(BaseItem* item) {
       
        return true;
    }

    
    virtual ~BaseBag() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};
class SherlockBag : public BaseBag {
public:
    SherlockBag(Character* owner) : BaseBag(owner) {}
    ~SherlockBag() = default;
    // Override insert method to add an item to the bag (add to the head of the linked list)
    virtual bool insert(BaseItem* item) override {
        if (itemCount >= 13) {
            // Bag is full
            return false;
        }

        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        itemCount++;
        return true;
    }

    // Override get method to find and use any usable item in the bag
    virtual BaseItem* get() override {
        if (!head) return nullptr;

        Node* current = head;
        Node* previous = nullptr;

        while (current && !canUse(current->data)) {
            previous = current;
            current = current->next;
        }

        if (!current) return nullptr;

        BaseItem* itemToUse = current->data;

        if (previous) {
            previous->next = current->next;
        }
        else {
            head = current->next;
        }

        // Move the used item to the head of the list
        current->next = head;
        head = current;

        return itemToUse;
    }

    // Override get method to find and use a specific type of item in the bag
    virtual BaseItem* get(ItemType itemType) override {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data->getItemType() == itemType && canUse(current->data)) {
                BaseItem* itemToUse = current->data;

                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }

                // Move the used item to the head of the list
                current->next = head;
                head = current;

                return itemToUse;
            }
            previous = current;
            current = current->next;
        }

        return nullptr;
    }
private:
    Node* head = nullptr;
    int itemCount = 0;
};
class WatsonBag : public BaseBag {
public:
    WatsonBag(Character* owner) : BaseBag(owner) {}
    ~WatsonBag() = default;
    // Override insert method to add an item to the bag (add to the head of the linked list)
    virtual bool insert(BaseItem* item) override {
        if (itemCount >= 15) {
            // Bag is full
            return false;
        }

        Node* newNode = new Node(item);
        newNode->next = head;
        head = newNode;
        itemCount++;
        return true;
    }

    // Override get method to find and use any usable item in the bag
    virtual BaseItem* get() override {
        if (!head) return nullptr;

        Node* current = head;
        Node* previous = nullptr;

        while (current && !canUse(current->data)) {
            previous = current;
            current = current->next;
        }

        if (!current) return nullptr;

        BaseItem* itemToUse = current->data;

        if (previous) {
            previous->next = current->next;
        }
        else {
            head = current->next;
        }

        // Move the used item to the head of the list
        current->next = head;
        head = current;

        return itemToUse;
    }

    // Override get method to find and use a specific type of item in the bag
    virtual BaseItem* get(ItemType itemType) override {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data->getItemType() == itemType && canUse(current->data)) {
                BaseItem* itemToUse = current->data;

                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }

                // Move the used item to the head of the list
                current->next = head;
                head = current;

                return itemToUse;
            }
            previous = current;
            current = current->next;
        }

        return nullptr;
    }
};
void giftExchange(SherlockBag* sherlockBag, WatsonBag* watsonBag);
class StudyPinkProgram {
private:
    // Sample attributes
    Configuration* config;
    Sherlock* sherlock;
    Watson* watson;
    Criminal* criminal;
    Map* map;
    ArrayMovingObject* arr_mv_objs;

public:
    StudyPinkProgram(const string& config_file_path);
    virtual bool isStop() const {
        return true;
    }
    virtual void run();
    virtual ~StudyPinkProgram();
};



// ////////////////////////////////////////////////
// /// END OF STUDENT'S ANSWER
// ////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
