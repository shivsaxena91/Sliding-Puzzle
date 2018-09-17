#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <tuple>
#include <deque>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <ctime>

using namespace std;
typedef vector<vector<int>> md_vector;

int rows, cols;
md_vector init_state;
static bool found = false;
int max_depth = 1;

void displayVectorByPointer(md_vector*);

void displayVectorByReference(const md_vector&);

class Block {
    private:
        int id,
            startx, starty,
            endx, endy;


    public:
        static int total_blocks;
        static int getTotalBlocks();

        bool moves[4];              //Sequence --> Up, Down, Left, Right

        int getId() {
            return id;
        }

        int getx1() {
            return startx;
        }

        int getx2() {
            return endx;
        }

        int gety1() {
            return starty;
        }

        int gety2() {
            return endy;
        }

        int getWidth() {
            return (starty - startx) + 1;
        }

        int getHeight() {
            return (endy - endx) + 1;
        }

        void setId(int id) {
            this->id = id;
            total_blocks++;
        }

        void setStart(int x, int y) {
            startx = x;
            starty = y;
        }

        void setEnd(int x, int y) {
            endx = x;
            endy = y;
        }

        void setAll(int id, int x1, int y1, int x2, int y2) {
            this->id = id;

            startx = x1; starty = y1;
            endx = x2; endy = y2;
            total_blocks++;
        }

        bool canMoveUp(const md_vector& vec) {
            for(int i = starty; i <= endy; i++) {
                if(id == 2) {
                    if(vec[startx - 1][i] != 0 && vec[startx - 1][i] != -1)
                        return false;
                }

                else if(vec[startx - 1][i] != 0)
                    return false;

            }
            return true;
        }

        void moveUp(md_vector& vec) {
            for(int i = starty; i <= endy; i++)
                vec[endx][i] = 0;

            startx -= 1;
            endx -= 1;

            for(int i = startx; i <= endx; i++)
                for(int j = starty; j <= endy; j++)
                    vec[i][j] = id;
        }

        bool canMoveDown(const md_vector& vec) {
            for(int i = starty; i <= endy; i++)
                if(id == 2) {
                    if(vec[endx + 1][i] != 0 && vec[endx + 1][i] != -1)
                        return false;
                }
                else if(vec[endx + 1][i] != 0)
                    return false;

            return true;
        }

        void moveDown(md_vector& vec) {
            for(int i = starty; i <= endy; i++)
                vec[startx][i] = 0;

            startx += 1;
            endx += 1;

            for(int i = startx; i <= endx; i++)
                for(int j = starty; j <= endy; j++)
                    vec[i][j] = id;
        }

        bool canMoveLeft(const md_vector& vec) {
            for(int i = startx; i <= endx; i++)
                if(id == 2) {
                    if(vec[i][starty - 1] != 0 && vec[i][starty - 1] != -1)
                        return false;
                }
                else if(vec[i][starty - 1] != 0)
                    return false;

            return true;
        }

        void moveLeft(md_vector& vec) {

            for(int i = startx; i <= endx; i++)
                vec[i][endy] = 0;

            starty -= 1;
            endy -= 1;

            for(int i = startx; i <= endx; i++)
                for(int j = starty; j <= endy; j++)
                    vec[i][j] = id;
        }

        bool canMoveRight(const md_vector& vec) {
            for(int i = startx; i <= endx; i++)
                if(id == 2) {
                    if(vec[i][endy + 1] != 0 && vec[i][endy + 1] != -1)
                        return false;
                }
                else if(vec[i][endy + 1] != 0)
                    return false;

            return true;
        }

        void moveRight(md_vector& vec) {

            for(int i = startx; i <= endx; i++)
                vec[i][starty] = 0;

            starty += 1;
            endy += 1;

            for(int i = startx; i <= endx; i++)
                for(int j = starty; j <= endy; j++)
                    vec[i][j] = id;
        }


};

int Block::total_blocks = 0;
int Block::getTotalBlocks() {
    return total_blocks;
}




bool compareVectorStates(const md_vector&, const md_vector&);

list<int> getBlocks(md_vector&);

vector<Block> createBlockObjects(md_vector&, list<int>&);

bool checkAndAddState(const md_vector&, vector<string>&);
bool checkState(const md_vector&, vector<string>&);

void convertStringStateToVector(string, md_vector&, int, int, bool b = false);

bool isPuzzleSolved(const md_vector&);

vector<tuple<Block, string>> generateMovesVector(vector<Block>&, md_vector&);

void generateMovesVector(vector<Block>&, md_vector&, vector<tuple<Block, string>>& v);

void generateMovesVector(vector<Block>&, md_vector&, vector<tuple<md_vector, Block, string, vector<tuple<Block, string>>>>&,
                         vector<tuple<Block, string>>, int parent_id, string parent_dir);

void generateMovesQueue(vector<Block>&, md_vector&, deque<tuple<md_vector, Block, string>>&);

void readFile(string, int&, int&, md_vector&);

void normalizeVector(md_vector&);

void swapIdx(int,int, md_vector& );

void randomWalk(md_vector&, vector<string>&, vector<tuple<Block, string>>&, int);

void performDFS(md_vector&, list<int>&, vector<Block>&, vector<string>&, vector<md_vector>, vector<tuple<Block, string>>&, int&);

int performBFS(md_vector&, list<int>&, vector<Block>&, vector<string>&, vector<md_vector>,
               vector<tuple<Block, string>>&, vector<tuple<md_vector, Block, string, vector<tuple<Block, string>>>>&,
                int&, string&, int&);

void performIDS(md_vector&, list<int>&, vector<Block>&, vector<string>&, vector<md_vector>,
                vector<tuple<Block, string>>&, vector<string>&, int, int&);

void performRandomWalk();

void displayVectorWithMoves(md_vector&, vector<tuple<Block, string>>, list<int>&, vector<Block>, string, int, double);

void initializeAndImplementDFS();

void initializeAndImplementBFS();

void initializeAndImplementIDS();


void displayVectorWithMovesRandomWalk(md_vector& vec, vector<tuple<Block, string>> v_moves, list<int> l_block_ids) {
    cout << endl << "# Random walk" << endl;

    displayVectorByReference(vec);

    vector<Block> v_block_objs;
    v_block_objs = createBlockObjects(vec, l_block_ids);


    for(int i = 0; i < v_moves.size(); i++) {

        Block b = get<0>(v_moves[i]);
        string move = get<1>(v_moves[i]);

        cout << "(" << b.getId() << "," << move << ")" << endl << endl;

        for(int j = 0; j < v_block_objs.size(); j++)
        {
            if(v_block_objs[j].getId() == b.getId())
            {
                if(move == "UP") {
                    v_block_objs[j].moveUp(vec);
                }
                else if(move == "DOWN") {
                    v_block_objs[j].moveDown(vec);
                }
                else if(move == "LEFT") {
                    v_block_objs[j].moveLeft(vec);
                }
                else if(move == "RIGHT") {
                    v_block_objs[j].moveRight(vec);
                }
                break;
            }
        }
        displayVectorByReference(vec);

    }
}

int main() {

    md_vector clone_state;

    //performRandomWalk();

    readFile("SBP-level1.txt", rows, cols, clone_state);
    normalizeVector(clone_state);
    init_state = clone_state;

    initializeAndImplementDFS();
    found = false;

    initializeAndImplementBFS();
    found = false;

    initializeAndImplementIDS();

    return 0;
}

void performRandomWalk() {
    md_vector clone_state;
    readFile("SBP-level0.txt", rows, cols, clone_state);
    init_state = clone_state;

    displayVectorByReference(clone_state);
    list<int> l_block_ids = getBlocks(clone_state);
    vector<string> v_visited_states;
    vector<tuple<Block, string>> v_moves;
    randomWalk(clone_state, v_visited_states,  v_moves, 3);
    clone_state = init_state;

    displayVectorWithMovesRandomWalk(clone_state, v_moves, l_block_ids);
}

void normalizeVector(md_vector& vec) {
    int nextIdx = 3;
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[0].size(); j++) {
            if (vec[i][j] == nextIdx)
                nextIdx++;
            else if (vec[i][j] > nextIdx) {
                swapIdx(nextIdx, vec[i][j], vec);
                nextIdx++;
            }
        }
    }
}

void swapIdx(int idx1,int idx2, md_vector& vec) {
    for(int i = 0;i < vec.size();i++) {
        for(int j = 0; j < vec[0].size(); j++) {
            if (vec[i][j]==idx1)
                vec[i][j]=idx2;

            else if (vec[i][j]==idx2)
                vec[i][j]=idx1;
        }
    }
}

//Displays the vector onto the console
void displayVectorByPointer(md_vector* vec) {
    for(int i = 0; i < (*vec).size(); i ++) {
        for(int j = 0; j < (*vec)[0].size(); j++) {
            cout << (*vec)[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

//Displays the vector onto the console
void displayVectorByReference(const md_vector& vec) {
    cout << "(" << cols << "," << rows << ")" << endl;
    for(int i = 0; i < vec.size(); i ++) {
        for(int j = 0; j < vec[0].size(); j++) {
            cout << vec[i][j] << ",";
        }
        cout << endl;
    }
    cout << endl;
}

//Compares values of two vectors. May not be used anymore
bool compareVectorStates(const md_vector& first_vector, const md_vector& second_vector) {
    bool isSame = true;
    for(int i = 0; i < first_vector.size(); i ++) {
        for(int j = 0; j < first_vector.size(); j++) {
            if(first_vector[i][j] == second_vector[i][j])
                continue;
            else {
                isSame = false;
                break;
            }
        }
    }
    if(isSame)
        return true;
    else
        return false;
}

//Gets all the distinct blocks in the puzzle
list<int> getBlocks(md_vector& vec){
    set<int> s;
    for(int i = 0; i < vec.size(); i++)
        for(int j = 0; j < vec[0].size(); j++)
            if(vec[i][j] > 1)
                s.insert(vec[i][j]);

    list<int> l(s.begin(), s.end());
    l.sort();
    return l;
}

//Creates a vector of block objects in the puzzle
vector<Block> createBlockObjects(md_vector& vec, list<int>& lt) {
    int f_x = 0, f_y = 0, l_x = 0, l_y = 0;
    vector<Block> l_blocks;
    for(list<int>::iterator it = lt.begin(); it != lt.end(); it++) {
        for(int i = 0; i < vec.size(); i++) {
            for(int j = 0; j < vec[0].size(); j++) {
                if(vec[i][j] == *it) {
                    if(f_x == 0 && f_y == 0) {
                        f_x = i;
                        f_y = j;
                    }
                    else {
                        l_x = i;
                        l_y = j;
                    }
                }
            }
        }

        if(l_x == 0 && l_y == 0) {
            l_x = f_x;
            l_y = f_y;
        }

        Block block;
        block.setAll(*it, f_x, f_y, l_x, l_y);
        l_blocks.push_back(block);

        f_x = 0, f_y = 0, l_x = 0, l_y = 0;
    }
    return l_blocks;
}

//Splits the string by a delimiter
void splitString(string &s, char delimiter, vector<string> &elements) {
    stringstream n_str;
    n_str.str(s);
    string strbeforeDelim;
    while (getline(n_str, strbeforeDelim, delimiter)) {
        elements.push_back(strbeforeDelim);
    }
}

//Converts the string back to vector form.
void convertStringStateToVector(string state, md_vector& vec, int rows, int cols, bool is_file_string) {
    vector<string> vec_s;
    vector<int> row;
    splitString(state, ',', vec_s);

    int counter = 0;
    if(is_file_string) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                row.push_back(stoi(vec_s[counter]));
                counter++;
            }
            vec.push_back(row);
            row.clear();
        }
    }
    else {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                vec[i][j] = stoi(vec_s[counter]);
                counter++;
            }
        }
    }

}

//Converts vector to string.
bool checkAndAddState(const md_vector& vec, vector<string>& state_list) {
    string state_string;
    md_vector normalized_vector = vec;
    normalizeVector(normalized_vector);
    for(int i = 0; i < normalized_vector.size(); i++)
        for(int j = 0; j < normalized_vector[0].size(); j++)
            state_string +=  to_string(normalized_vector[i][j]) + ',';

    if(find(state_list.begin(), state_list.end(), state_string) != state_list.end())
        return false;       //duplicate state
    else {
        state_list.push_back(state_string);
        return true;        //valid state, so continue
    }
}

bool checkState(const md_vector& vec, vector<string>& state_list) {
    string state_string;
    md_vector normalized_vector = vec;
    normalizeVector(normalized_vector);
    for(int i = 0; i < normalized_vector.size(); i++)
        for(int j = 0; j < normalized_vector[0].size(); j++)
            state_string +=  to_string(normalized_vector[i][j]) + ',';

    if(find(state_list.begin(), state_list.end(), state_string) != state_list.end())
        return false;       //duplicate state
    else
        return true;        //valid state, so continue

}

//Checks if puzzle is in the final state
bool isPuzzleSolved(const md_vector& vec) {
    bool solved = true;
    for(int i = 0; i < vec.size(); i++)
        for(int j = 0; j < vec[0].size(); j++)
            if(vec[i][j] != -1) continue;
            else {
                solved = false;
                break;
            }
    return solved;
}

//Reads file and creates a vector
void readFile(string file_name, int& rows, int& cols, md_vector& vec) {
    string curr_line, entire_string;
    int line_no = 0;

    ifstream data_file(file_name);



    if(!data_file) {
        cout << "Was unable to open the file" << endl;
    }
    else {      //data_file.is_open())
        vector<string> dimention_vector;
        while(getline(data_file, curr_line)) {
            line_no++;
            if(line_no == 1) {
                splitString(curr_line, ',', dimention_vector);
                cols = stoi(dimention_vector[0]);
                rows = stoi(dimention_vector[1]);
            }
            else
                entire_string += curr_line;
        }
        data_file.close();
        convertStringStateToVector(entire_string, vec, rows, cols, true);
        //cout << entire_string << endl;
    }
}

//Generates posible moves in the puzzle
vector<tuple<Block, string>> generateMovesVector(vector<Block>& v_block_objs, md_vector& vec)
{
    //param @blocks --> vector of all the existing blocks
    //param @vec --> the md vector within which moves are generated
    //param @l_moves --> list of moves
    vector<tuple<Block, string>> v;
    for(int i = 0; i < v_block_objs.size(); i++) {
        if(v_block_objs[i].canMoveUp(vec))
            v.push_back(make_tuple(v_block_objs[i], "UP"));
        if(v_block_objs[i].canMoveDown(vec))
            v.push_back(make_tuple(v_block_objs[i], "DOWN"));
        if(v_block_objs[i].canMoveLeft(vec))
            v.push_back(make_tuple(v_block_objs[i], "LEFT"));
        if(v_block_objs[i].canMoveRight(vec))
            v.push_back(make_tuple(v_block_objs[i], "RIGHT"));
    }
    return v;
}

void generateMovesVector(vector<Block>& v_block_objs, md_vector& vec, vector<tuple<Block, string>>& v)
{
    //param @blocks --> vector of all the existing blocks
    //param @vec --> the md vector within which moves are generated
    //param @l_moves --> list of moves
    for(int i = 0; i < v_block_objs.size(); i++) {
        if(v_block_objs[i].canMoveUp(vec))
            v.push_back(make_tuple(v_block_objs[i], "UP"));
        if(v_block_objs[i].canMoveDown(vec))
            v.push_back(make_tuple(v_block_objs[i], "DOWN"));
        if(v_block_objs[i].canMoveLeft(vec))
            v.push_back(make_tuple(v_block_objs[i], "LEFT"));
        if(v_block_objs[i].canMoveRight(vec))
            v.push_back(make_tuple(v_block_objs[i], "RIGHT"));
    }
}

void generateMovesVector(vector<Block>& v_block_objs, md_vector& vec,
                         vector<tuple<md_vector, Block, string, vector<tuple<Block, string>>>>& v,
                         vector<tuple<Block, string>> v_block_dir,
                         int parent_id, string parent_dir)
{
    //param @blocks --> vector of all the existing blocks
    //param @vec --> the md vector within which moves are generated
    //param @l_moves --> list of moves
    Block b;
    b.setId(parent_id);
    v_block_dir.push_back(make_tuple(b, parent_dir));

    for(int i = 0; i < v_block_objs.size(); i++) {
        if(v_block_objs[i].canMoveUp(vec))
            v.push_back(make_tuple(vec, v_block_objs[i], "UP", v_block_dir));
        if(v_block_objs[i].canMoveDown(vec))
            v.push_back(make_tuple(vec, v_block_objs[i], "DOWN", v_block_dir));
        if(v_block_objs[i].canMoveLeft(vec))
            v.push_back(make_tuple(vec, v_block_objs[i], "LEFT", v_block_dir));
        if(v_block_objs[i].canMoveRight(vec))
            v.push_back(make_tuple(vec, v_block_objs[i], "RIGHT", v_block_dir));
    }
}

void generateMovesQueue(vector<Block>& v_block_objs, md_vector& vec, deque<tuple<md_vector, Block, string>>& dq)
{
    //param @blocks --> vector of all the existing blocks
    //param @vec --> the md vector within which moves are generated
    //param @l_moves --> list of moves

    for(int i = 0; i < v_block_objs.size(); i++) {
        if(v_block_objs[i].canMoveUp(vec))
            dq.push_back(make_tuple(vec, v_block_objs[i], "UP"));
        if(v_block_objs[i].canMoveDown(vec))
            dq.push_back(make_tuple(vec, v_block_objs[i], "DOWN"));
        if(v_block_objs[i].canMoveLeft(vec))
            dq.push_back(make_tuple(vec, v_block_objs[i], "LEFT"));
        if(v_block_objs[i].canMoveRight(vec))
            dq.push_back(make_tuple(vec, v_block_objs[i], "RIGHT"));
    }
}


void initializeAndImplementIDS() {


    clock_t startTime = clock();


    md_vector clone_state;
    vector<string> v_visited_states;
    list<int> l_block_ids;
    vector<Block> v_block_objs;
    vector<md_vector> v_md_states;
    vector<tuple<Block, string>>  path_taken;
    int depth = 0;
    int count = 0;
    while(!found) {
        clone_state = init_state;
        v_visited_states.clear();
        checkAndAddState(clone_state, v_visited_states);

        l_block_ids = getBlocks(clone_state);
        v_block_objs = createBlockObjects(clone_state, l_block_ids);

        v_md_states.clear();
        path_taken.clear();
        vector<string> path_str;
        count = 0;
        performIDS(clone_state, l_block_ids, v_block_objs, v_visited_states, v_md_states, path_taken, path_str, depth, count);
        max_depth++;
    }

    double duration =  (clock() - startTime ) / (double) CLOCKS_PER_SEC;

    clone_state = init_state;
    l_block_ids = getBlocks(clone_state);
    v_block_objs = createBlockObjects(clone_state, l_block_ids);

    displayVectorWithMoves(clone_state, path_taken, l_block_ids, v_block_objs, "IDS", count, duration);
}

void initializeAndImplementDFS() {


    clock_t startTime = clock();


    md_vector clone_state = init_state;
    vector<string> v_visited_states;
    checkAndAddState(clone_state, v_visited_states);

    list<int> l_block_ids = getBlocks(clone_state);
    vector<Block> v_block_objs = createBlockObjects(clone_state, l_block_ids);
    vector<md_vector> v_md_states;
    vector<tuple<Block, string>>  path_taken;
    int count = 0;

    performDFS(clone_state, l_block_ids, v_block_objs, v_visited_states, v_md_states, path_taken, count);

    double duration =  (clock() - startTime ) / (double) CLOCKS_PER_SEC;

    clone_state = init_state;
    l_block_ids = getBlocks(clone_state);
    v_block_objs = createBlockObjects(clone_state, l_block_ids);

    displayVectorWithMoves(clone_state, path_taken, l_block_ids, v_block_objs, "DFS", count, duration);
}

void initializeAndImplementBFS() {


    clock_t startTime = clock();


    md_vector clone_state = init_state;
    vector<string> v_visited_states;
    checkAndAddState(clone_state, v_visited_states);

    list<int> l_block_ids = getBlocks(clone_state);
    vector<Block> v_block_objs = createBlockObjects(clone_state, l_block_ids);
    vector<md_vector> v_md_states;
    vector<tuple<Block, string>>  path_taken;

    vector<tuple<md_vector, Block, string, vector<tuple<Block, string>>>> dq_to_visit;
    int parent_id = 0;
    string parent_dir = "";
    int count = 0;

    int index = performBFS(clone_state, l_block_ids, v_block_objs, v_visited_states, v_md_states, path_taken, dq_to_visit, parent_id, parent_dir, count);


    double duration =  (clock() - startTime ) / (double) CLOCKS_PER_SEC;

    clone_state = init_state;
    l_block_ids = getBlocks(clone_state);
    v_block_objs = createBlockObjects(clone_state, l_block_ids);
    displayVectorWithMoves(clone_state, path_taken, l_block_ids, v_block_objs, "BFS", count, duration);

}



int performBFS(md_vector& vec, list<int>& l_block_ids, vector<Block>& v_block_objs, vector<string>& v_visited_states,
                vector<md_vector> v_states, vector<tuple<Block, string>>& path_taken,
                vector<tuple<md_vector, Block, string, vector<tuple<Block, string>>>>& v_to_visit,
                int& parent_id, string& parent_dir, int& count) {

    int index = 0;
    if(found) return index;

    vector<tuple<Block, string>> path;

    Block b;
    string move;

    generateMovesVector(v_block_objs, vec, v_to_visit, path, parent_id, parent_dir);

    for(int i = 0; i < v_to_visit.size(); i++) {
        if(found) break;
        count++;
        vec = get<0>(v_to_visit[i]);
        b = get<1>(v_to_visit[i]);
        move = get<2>(v_to_visit[i]);
        path = get<3>(v_to_visit[i]);

        parent_id = b.getId();
        parent_dir = move;

        if(move == "UP")
            b.moveUp(vec);

        else if(move == "DOWN")
            b.moveDown(vec);

        else if(move == "LEFT")
            b.moveLeft(vec);

        else if(move == "RIGHT")
            b.moveRight(vec);


        //dq_to_visit.pop_front();


        if(checkAndAddState(vec, v_visited_states)) {
            if(isPuzzleSolved(vec)) {
                //node with id = 0 is the initial node
                index = i;
                get<3>(v_to_visit[i]).push_back(make_tuple(b, move));
                path_taken = get<3>(v_to_visit[i]);
                found = true;
                break;
            }
            else {
                v_block_objs.clear();
                v_block_objs = createBlockObjects(vec, l_block_ids);
                generateMovesVector(v_block_objs, vec, v_to_visit, path, parent_id, parent_dir);
            }
        }
    }

    return index;
}


void performDFS(md_vector& vec, list<int>& l_block_ids, vector<Block>& v_block_objs, vector<string>& v_visited_states,
                  vector<md_vector> v_states, vector<tuple<Block, string>>& path_taken, int& count)
{
    if(found) return;

    //generates posible moves onto v_block_moves
    //vector<tuple<Block, string>> v_block_moves = generateMovesVector(v_block_objs, vec);
    vector<tuple<Block, string>> v_block_moves;
    generateMovesVector(v_block_objs, vec, v_block_moves);

    v_states.push_back(vec);

    for(int i = 0; i < v_block_moves.size(); i++) {
        if(found) break;
        count++;
        Block b = get<0>(v_block_moves[i]);         //-->     Block object
        string move = get<1>(v_block_moves[i]);     //-->     Move direction

        vec = v_states[v_states.size() - 1];

        if(move == "UP")
            b.moveUp(vec);

        else if(move == "DOWN")
            b.moveDown(vec);

        else if(move == "LEFT")
            b.moveLeft(vec);

        else if(move == "RIGHT")
            b.moveRight(vec);

        path_taken.push_back(make_tuple(b, move));

        if(checkAndAddState(vec, v_visited_states)) {
            //continue with depth
            if(isPuzzleSolved(vec)) {
                found = true;
                break;
            }
            else {
                v_block_objs.clear();
                v_block_objs = createBlockObjects(vec, l_block_ids);    //for updating the coordinates
                performDFS(vec, l_block_ids, v_block_objs, v_visited_states, v_states, path_taken, count);

                if(found) break;

                if(i == v_block_moves.size() - 1)
                    path_taken.pop_back();
            }
        }
        else {
            //undo changes. Reverse action
            if(move == "UP")
                b.moveDown(vec);

            else if(move == "DOWN")
                b.moveUp(vec);

            else if(move == "LEFT")
                b.moveRight(vec);

            else if(move == "RIGHT")
                b.moveLeft(vec);

            path_taken.pop_back();

            if(i == v_block_moves.size() - 1)
                path_taken.pop_back();
        }
    }
}


void performIDS(md_vector& vec, list<int>& l_block_ids, vector<Block>& v_block_objs, vector<string>& v_visited_states,
                  vector<md_vector> v_states, vector<tuple<Block, string>>& path_taken, vector<string>& path_str, int depth, int& count)
{
    if(found) return;
    depth++;
    vector<tuple<Block, string>> v_block_moves;

    generateMovesVector(v_block_objs, vec, v_block_moves);

    v_states.push_back(vec);

    for(int i = 0; i < v_block_moves.size(); i++) {
        if(found) break;
        count++;
        Block b = get<0>(v_block_moves[i]);         //-->     Block object
        string move = get<1>(v_block_moves[i]);     //-->     Move direction

        vec = v_states[v_states.size() - 1];

        if(move == "UP")
            b.moveUp(vec);

        else if(move == "DOWN")
            b.moveDown(vec);

        else if(move == "LEFT")
            b.moveLeft(vec);

        else if(move == "RIGHT")
            b.moveRight(vec);

        if(b.getId() == 4 && move == "LEFT" && depth == 5) {
            move = "LEFT";
        }

        path_taken.push_back(make_tuple(b, move));
        path_str.push_back(to_string(b.getId()) + ", " + move);

        if(isPuzzleSolved(vec)) {
            found = true;
            break;
        }



        if(depth == max_depth) {
            path_taken.pop_back();
            path_str.pop_back();

        }



        if(depth < max_depth) {
//*region1      /*check states*/

            if(checkAndAddState(vec, v_visited_states)) {
                //continue with depth
                if(isPuzzleSolved(vec)) {
                    found = true;
                    break;
                }
                else {
                    v_block_objs.clear();
                    v_block_objs = createBlockObjects(vec, l_block_ids);    //for updating the coordinates
                    performIDS(vec, l_block_ids, v_block_objs, v_visited_states, v_states, path_taken, path_str, depth, count);

                    if(found) break;

                    path_taken.pop_back();
                    path_str.pop_back();
                }
            }
            else {
                //undo changes. Reverse action
                if(move == "UP")
                    b.moveDown(vec);

                else if(move == "DOWN")
                    b.moveUp(vec);

                else if(move == "LEFT")
                    b.moveRight(vec);

                else if(move == "RIGHT")
                    b.moveLeft(vec);

                path_taken.pop_back();
                path_str.pop_back();
            }
//* end region

//*region2      /*not to check states*/
//            if(isPuzzleSolved(vec)) {
//                found = true;
//                break;
//            }
//            else {
//                v_block_objs.clear();
//                v_block_objs = createBlockObjects(vec, l_block_ids);    //for updating the coordinates
//                performIDS(vec, l_block_ids, v_block_objs, v_visited_states, v_states, path_taken, path_str, depth);

//                if(found) break;

//                path_taken.pop_back();
//                path_str.pop_back();
//            }
//*end region
        }
    }
}

void displayVectorWithMoves(md_vector& vec, vector<tuple<Block, string>> path_taken, list<int>& l_block_ids,
                            vector<Block> v_block_objs, string type, int count, double duration)
{
    cout << endl << "# Solution for " << type << endl << endl;
    if(type == "IDS")
        cout << "# This solution for IDS is achieved by maintaining previous states. Stateless solution will take lots of time" << endl
             << "# If stateless solution is required, search for 'region1' in sbp.cpp file and comment that region" << endl
             << "# Then search for 'region2' and uncomment that region. Save. And run makefile" << endl << endl;

    displayVectorByReference(vec);

    v_block_objs.clear();
    v_block_objs = createBlockObjects(vec, l_block_ids);

    int k = 0;
    for(int i = 0; i < path_taken.size(); i++) {

        Block b = get<0>(path_taken[i]);
        string move = get<1>(path_taken[i]);

        if(b.getId() == 0) continue;

        k++;
        cout << "(" << b.getId() << "," << move << ")" << endl << endl;

        for(int j = 0; j < v_block_objs.size(); j++)
        {
            if(v_block_objs[j].getId() == b.getId())
            {
                if(move == "UP") {
                    v_block_objs[j].moveUp(vec);
                }
                else if(move == "DOWN") {
                    v_block_objs[j].moveDown(vec);
                }
                else if(move == "LEFT") {
                    v_block_objs[j].moveLeft(vec);
                }
                else if(move == "RIGHT") {
                    v_block_objs[j].moveRight(vec);
                }
                break;
            }
        }
        displayVectorByReference(vec);

    }

    cout << "# " << to_string(count) << " nodes, " << to_string(duration) << " secs, " << k << " steps" << endl << endl;
}


void randomWalk(md_vector& vec, vector<string>& v_visited_states, vector<tuple<Block, string>>& v_block_moves, int number_of_walks) {
    /*
     * Write a function that, given a state and a positive integer N, performs the steps following:
     * 1) generates all moves that can be executed on the board in its current state,
     * 2) selects one at random,
     * 3) executes it,
     * 4) normalizes the resulting game state,
     * 5) if we have reached the goal, or if we have executed N moves, stops; otherwise, goes back to step (1)
    */
    if (number_of_walks == 0) { return; }

    list<int> l_block_ids = getBlocks(vec);
    vector<Block> v_block_objs = createBlockObjects(vec, l_block_ids);
    v_block_moves = generateMovesVector(v_block_objs, vec);        //generates posible moves onto v_block_moves

    tuple<Block, string> t;

    srand(time(NULL));
    int randomNumber = rand() % v_block_moves.size();

    t = v_block_moves[randomNumber];
    Block b = get<0>(t);
    string move = get<1>(t);

    v_block_moves.push_back(make_tuple(b, move));

    if(move == "UP")
        b.moveUp(vec);
    else if(move == "DOWN")
        b.moveDown(vec);
    else if(move == "LEFT")
        b.moveLeft(vec);
    else if(move == "RIGHT")
        b.moveRight(vec);


    if(isPuzzleSolved(vec)) {
        cout << "The puzzle has been solved." << endl;
        cout << "Walks left: " << --number_of_walks << endl;
    }
    else {
        randomWalk(vec, v_visited_states, v_block_moves, --number_of_walks);
    }
}
