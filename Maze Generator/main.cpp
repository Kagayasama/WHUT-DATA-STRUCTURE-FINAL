#include <cassert>
#include <cstdlib>
#include <iostream>
class Disjoint_sets {
public:
    Disjoint_sets( int );
    ~Disjoint_sets();
    int find( int ) const;
    int disjoint_sets() const;
    void set_union( int, int );
private:
    int array_size;
    int *parent;
    int *tree_height;
    int max_height;
    int num_disjoint_sets;
};
Disjoint_sets::Disjoint_sets( int n ):
        array_size( std::max( 1, n ) ),
        parent( new int[array_size] ),
        tree_height( new int[array_size] ),
        max_height( 0 ),
        num_disjoint_sets( array_size )
{
    for ( int i = 0; i < array_size; ++i ) {
        parent[i] = i;
        tree_height[i] = 0;
    }
}

Disjoint_sets::~Disjoint_sets() {
    delete [] parent;
    delete [] tree_height;
}
int Disjoint_sets::find( int n ) const {
    assert( n >= 0 && n < array_size );

    int k = n;

    while ( parent[k] != k ) {
        k = parent[k];
    }

    parent[n] = k;

    return k;
}

int Disjoint_sets::disjoint_sets() const {
    return num_disjoint_sets;
}
void Disjoint_sets::set_union( int m, int n ) {
    assert( n >= 0 && n < array_size );
    assert( m >= 0 && m < array_size );
    m = find( m );
    n = find( n );
    if ( m == n ) {
        return;
    }
    --num_disjoint_sets;
    if ( tree_height[m] >= tree_height[n] ) {
        parent[n] = m;

        if ( tree_height[m] == tree_height[n] ) {
            ++( tree_height[m] );

            max_height = std::max(
                    max_height, tree_height[m]
            );
        }
    } else {
        parent[m] = n;
    }
}
class Permutation {
private:
    int capacity;
    int *bound;
    int *array;

public:
    Permutation( int );
    ~Permutation();
    int next();

};
Permutation::Permutation( int n ):
        capacity( n ),
        bound( new int( capacity ) ),
        array( new int[capacity] ) {
    for ( int i = 0; i < capacity; ++i ) {
        array[i] = i;
    }
}

Permutation::~Permutation() {
    delete bound;
    delete [] array;
}

int Permutation::next() {
    if ( *bound == 0 ) {
        return 0;
    }
    int index = rand() % *bound;
    int result = array[index];
    --*bound;
    array[index] = array[*bound];

    return result;
}
void find_adjacent_rooms( int room[2], int wall, int n ) {
    int row =    wall / (2*n - 1);
    int column = wall % (2*n - 1);
    if ( column < n - 1 ) {
        room[0] = n*row + column;
        room[1] = n*row + column + 1;
    } else {
        column += 1 - n;
        room[0] = n* row      + column;
        room[1] = n*(row + 1) + column;
    }
}
void generate_maze( int m, int n ) {
    m--;
    n--;
    Disjoint_sets rooms( m*n );
    int number_of_walls = 2*m*n - m - n;
    bool is_wall[number_of_walls];
    Permutation untested_walls( number_of_walls );
    for ( int i = 0; i < number_of_walls; ++i ) {
        is_wall[i] = true;
    }
    while ( rooms.disjoint_sets() > 1 ) {
        int wall = untested_walls.next();
        int room[2];
        find_adjacent_rooms( room, wall, n );
        if ( rooms.find( room[0] ) != rooms.find( room[1] ) ) {
            is_wall[wall] = false;
            rooms.set_union( room[0], room[1] );
        }
    }
    std::cout << "x  x";
    for ( int i = 0; i < n - 1; ++i ) {
        std::cout << " -x";
    }
    std::cout << std::endl;
    int wall_counter = 0;
    for ( int i = 0; i < m - 1; ++i ) {
        std::cout << "|";
        for ( int j = 0; j < n - 1; ++j ) {
            if ( is_wall[wall_counter] ) {
                std::cout << "  |";
            } else {
                std::cout << "   ";
            }

            ++wall_counter;
        }
        std::cout << "  |" << std::endl;
        std::cout << "x";
        for ( int j = 0; j < n; ++j ) {
            if ( is_wall[wall_counter] ) {
                std::cout << " -x";
            } else {
                std::cout << "  x";
            }
            ++wall_counter;
        }
        std::cout << std::endl;
    }
    std::cout << "|";
    for ( int j = 0; j < n - 1; ++j ) {
        if ( is_wall[wall_counter] ) {
            std::cout << "  |";
        } else {
            std::cout << "   ";
        }
        ++wall_counter;
    }

    std::cout << "  |" << std::endl;
    for ( int i = 0; i < n - 1; ++i ) {
        std::cout << "x- ";
    }
    std::cout << "x  x" << std::endl;
}
int main(){
    generate_maze( 5, 5 );//输入迷宫想要的行和列
    return 0;
}