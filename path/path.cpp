#include "path.h"
#include <random>
#include <chrono>
#include <algorithm>
#define _MAX_NUM_GENERATION 10
#define _MAX_NUM_GENOTYPES 10
#define _NUM_UNCHANGED_GENERATIONS 10

using namespace std;

path::path(int sizeX, int sizeY, int** map, unsigned int forbidden_value) :path_base(sizeX, sizeY, map),forbidden_val(forbidden_value) {
	/*
	set directions[n][XY]

	0 - 1 - 2
	| \ | / |
	3 - x - 4
	| / | \ |
	5 - 6 - 7
	*/


	directions[0][0] = -1;
	directions[0][1] = -1;

	directions[1][0] = 0;
	directions[1][1] = -1;

	directions[2][0] = 1;
	directions[2][1] = -1;

	directions[3][0] = -1;
	directions[3][1] = 0;

	directions[4][0] = 1;
	directions[4][1] = 0;

	directions[5][0] = -1;
	directions[5][1] = 1;

	directions[6][0] = 0;
	directions[6][1] = 1;

	directions[7][0] = 1;
	directions[7][1] = 1;


    /*---generator type---*/

    auto seed = chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    generator=knuth_b(seed);
}

vector<coordinates> path::find_path(coordinates start, coordinates stop) {
    /*---declaration of array to store drawn paths, array to store their costs, array to store id of <_MAX_NUM_GENOTYPES> optimal paths--*/

    vector<coordinates> path_array[_MAX_NUM_GENERATION];
    unsigned int costs_array[_MAX_NUM_GENERATION];
    unsigned int min_index[_MAX_NUM_GENERATION];

	/*---check start&stop coordinates correctness---*/

	if (this->map[start.get_x()][start.get_y()] == this->forbidden_val || this->map[stop.get_x()][stop.get_y()] == this->forbidden_val)
		return path_array[0];

	/*---draw a path--*/

    for(unsigned int i=0;i<_MAX_NUM_GENERATION;i++) {
        draw_path(&start, &stop, &path_array[i]);
    }


	unsigned int last_cost=0;

    min_index[0]=0;
    costs_array[min_index[0]]=0;

    unsigned int counter=_NUM_UNCHANGED_GENERATIONS;
	unsigned int l;

	int k=0;

	do {
        /*---assign last lowest cost---*/

        last_cost = costs_array[min_index[0]];

        /*---calculate cost of paths---*/

        for (unsigned int i = 0; i < _MAX_NUM_GENERATION; i++)
            costs_array[i] = calculate_cost(&path_array[i]);

        /*---clear min_index array---*/

        for (unsigned int i = 0; i < _MAX_NUM_GENERATION; i++)
            min_index[i] = i;

        /*---sort array of paths by costs---*/

        sort_array(min_index, _MAX_NUM_GENERATION, costs_array);

        /*---create an hybrid of 2 paths---*/

        for (l = 0; l < (_MAX_NUM_GENOTYPES / 2); l += 2)
            path_array[min_index[l / 2]] = hybrid(&path_array[min_index[l]], &path_array[min_index[l + 1]]);

        /*---draw a new generation of paths---*/

        for (unsigned int i = 1; i < _MAX_NUM_GENERATION; i++)
            draw_path(&start, &stop, &path_array[min_index[i]]);

        /*---check changes of last _NUM_UNCHANGED_GENERATIONS generations---*/

        if (last_cost == costs_array[min_index[0]]){
            counter--;
        }
        else {
            counter = _NUM_UNCHANGED_GENERATIONS;
        }

        k++;

	}while(counter!=0&&k<1000000);

	return path_array[min_index[0]];

}

vector<coordinates>* path::draw_path(coordinates *start, coordinates *stop, vector<coordinates> *path_coordinates) {

    /*---draw a new path---*/


    /*---clear vector of coordinates---*/

    path_coordinates->clear();

    /*----set random generator----*/

	uniform_int_distribution<int> distribution(0,7);

	coordinates temp(start->get_x(),start->get_y());

	path_coordinates->push_back(temp);

	unsigned int draw_x, draw_y;
	unsigned short int r;

	do {
		do {
			r = (unsigned short int)distribution(generator);
			draw_x = temp.get_x() + directions[r][0];
			draw_y = temp.get_y() + directions[r][1];
		} while ((draw_x == temp.get_x() && draw_y == temp.get_y()) || !is_inside_map(&draw_x, &draw_y) || is_forbidden(&draw_x,&draw_y));

		temp.set_coordinates(draw_x, draw_y);

		path_coordinates->push_back(temp);

	} while (temp.get_x() != stop->get_x() || temp.get_y() != stop->get_y());

	optimize(path_coordinates);

	return path_coordinates;
}

bool path::is_inside_map(unsigned int *x,unsigned int *y) {

    /*---check correctness of coordinates---*/

	if ((*x >= 0 && *x < sizeX) && (*y >= 0 && *y < sizeY))
		return true;
	else
		return false;
}

unsigned int path::calculate_cost(vector<coordinates> * drawn_path) {

    /*---calculate cost of drawn path---*/

	unsigned int cost=0;

	for(auto i:*drawn_path)
		cost+=map[i.get_x()][i.get_y()];

	return cost;
}

vector<coordinates> path::hybrid(vector<coordinates> * A,vector<coordinates> * B) {

    /*---create a hybrid of two paths---*/

	vector<coordinates> temp;

	/*---check which vector is shorter---*/

    if(A->size()<B->size()){

        /*---draw a start point---*/
        uniform_int_distribution<int> distribution(1,A->size()-2);
        auto start_point=distribution(generator);

        unsigned int i;
        vector<coordinates>::iterator it,it_temp;
        bool is_not_found=false;

        /*---find max series of similar coordinates---*/

        for(i=(unsigned int)start_point;i<A->size()-1;i++){
            it_temp=search(B->begin(),B->end(),A->begin()+start_point,A->begin()+i+1);

            if(it_temp==B->end()&&i==start_point){
                is_not_found=true;
                break;
            }
            else if(it_temp==B->end())
                break;

            it=it_temp;
        }

        /*---if no coordinate is similar---*/

        if(is_not_found){
            temp.assign(A->begin(),A->end());
            A->clear();
            B->clear();
            return temp;
        }

        /*---set length of similar part---*/

        const unsigned int length=i-start_point;

        /*---exchange front of path---*/
        if(distance(B->begin(),it)<distance(A->begin(),A->begin()+start_point)){
            temp.assign(B->begin(),it);
            temp.insert(temp.end(),A->begin()+start_point,A->end());
        }
        /*---exchange back of path---*/
        else if(distance(it+length,B->end())<distance(A->begin()+i,A->end())){
            temp.assign(A->begin(),A->begin()+start_point);
            temp.insert(temp.end(),it,B->end());
        }
        /*---do not exchange---*/
        else{
            temp.assign(A->begin(),A->end());
        }

    }
    else if(B->size()<A->size()){

        /*---draw a start point---*/

        uniform_int_distribution<int> distribution(1,B->size()-2);
        auto start_point=distribution(generator); // draw a start point

        unsigned int i;
        vector<coordinates>::iterator it,it_temp;
        bool is_not_found=false;

        /*---find max series of similar coordinates---*/

        for(i=(unsigned int)start_point;i<B->size()-1;i++){
            it_temp=search(A->begin(),A->end(),B->begin()+start_point,B->begin()+i+1);

            if(it_temp==A->end()&&i==start_point){
                is_not_found=true;
                break;
            }
            else if(it_temp==A->end())
                break;

            it=it_temp;
        }

        /*---if no coordinate is similar---*/

        if(is_not_found){
            temp.assign(B->begin(),B->end());
            A->clear();
            B->clear();
            return temp;
        }

        /*---set length of similar part---*/

        const unsigned int length=i-start_point;

        /*---exchange front of path---*/
        if(distance(B->begin(),B->begin()+start_point)<distance(A->begin(),it)){
            temp.assign(B->begin(),B->begin()+start_point);
            temp.insert(temp.end(),it,A->end());
        }
        /*---exchange back of path---*/
        else if(distance(B->begin()+start_point+length,B->end())<distance(A->begin()+i,A->end())){
            temp.assign(A->begin(),it);
            temp.insert(temp.end(),B->begin()+start_point,B->end());
        }
        /*---do not exchange---*/
        else{
            temp.assign(A->begin(),A->end());
        }
    }
    else
        temp.assign(A->begin(),A->end());

    /*---clear parents---*/

    A->clear();
    B->clear();

    return temp;
}

void path::sort_array(unsigned int * array, unsigned int size, unsigned int *costs_array) {

    /*---sort array by cost_array fields---*/

    unsigned int minZ,minP,x;

    for(unsigned int i = 0; i < size - 1; i++)
    {
        minZ = costs_array[array[i]];
        minP = i;
        for(unsigned j = i + 1; j < size; j++)
            if(costs_array[array[j]] < minZ)
            {
                minZ = costs_array[array[j]];
                minP = j;
            }
        x = array[i];
        array[i] = array[minP];
        array[minP] = x;
    }
}

bool path::is_forbidden(unsigned int *x, unsigned int *y) {

    if(map[*x][*y]==forbidden_val)
        return true;
    else
        return false;
}

void path::optimize(vector<coordinates> *path_coordinates) {

    /*---optimize path---*/

    coordinates temp;
    vector<coordinates>::iterator it;

    for(unsigned int i=0;i<path_coordinates->size()-2;i++){

        temp=path_coordinates->at(i);
        it=path_coordinates->begin()+i;

        do{
            path_coordinates->erase(path_coordinates->begin()+i,it);
            it = find(path_coordinates->begin()+i+1,path_coordinates->end(),temp);
        }while(it!=path_coordinates->end());
    }
}