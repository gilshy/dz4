//
// The main goal - find all multiple edges in input graph
// Input file - list of edges
// To find multiple edges program count all edges that have identical start vertex and end vertex (they can be reversed)
// Count of multiple edges keeps in list listOfMultipleEdge
// Output format - "numOfMultipleEdges edge(s) connects vertexes numOfStartVertex and numOfEndVertex"
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uint32_t start, end; // start - numOfStartVertex, end - numOfEndVertex
    uint32_t multipleEdges; // multipleEdges - numOfMultipleEdges
} MultipleEdge;

typedef struct{
    MultipleEdge** listOfMultipleEdges;
    size_t size; // memory size)))
    uint32_t numOfEdges; // num of edges in struct
} arrayOfMultipleEdges;

void freeList(arrayOfMultipleEdges* list){
    for (uint32_t i = 0; i < list->numOfEdges; ++i){
        free(list->listOfMultipleEdges[i]);
    }
    free(list);
}

void showMultipleEdges(arrayOfMultipleEdges* array){
    for (uint32_t i = 0; i < array->numOfEdges; ++i){
        if(array->listOfMultipleEdges[i]->multipleEdges != 1){
            if(array->listOfMultipleEdges[i]->start == array->listOfMultipleEdges[i]->end){
                printf("%d edge(s) connects vertex %d\n", array->listOfMultipleEdges[i]->multipleEdges,
                       array->listOfMultipleEdges[i]->start);
            }
            else printf("%d edge(s) connects vertexes %d and %d\n", array->listOfMultipleEdges[i]->multipleEdges,
                        array->listOfMultipleEdges[i]->start, array->listOfMultipleEdges[i]->end);
        }
    }
}

MultipleEdge* createElementOfList(uint32_t start, // creating element to add it to array
                                  uint32_t end){
    MultipleEdge* multipleEdge = malloc(sizeof(MultipleEdge));
    multipleEdge->start = start;
    multipleEdge->end = end;
    multipleEdge->multipleEdges = 1;
    return multipleEdge;
}

arrayOfMultipleEdges* countMultipleEdges(arrayOfMultipleEdges* array) {// array - listOfMultipleEdges
    FILE* file = fopen("../input_graph.txt", "r");
    uint32_t start, end;

    array = (arrayOfMultipleEdges*) malloc( sizeof(arrayOfMultipleEdges)); //malloc memory for 1 element
    array->listOfMultipleEdges = malloc(2 * sizeof(MultipleEdge*));
    array->size = 1;
    array->numOfEdges = 1;
    fscanf(file, "%d - %d", &start, &end);
    array->listOfMultipleEdges[0] = createElementOfList(start, end); //add 1 element

    while(fscanf(file, "%d - %d", &start, &end) != EOF) {
        bool flag = true; // to check if it's in array already, true - don't found, false - found
        for (uint32_t index = 0; index < array->numOfEdges; ++index){

            //find if listOfMultipleEdges have element with these vertexes
            if (((array->listOfMultipleEdges[index]->start == start) && (array->listOfMultipleEdges[index]->end == end))
                || ((array->listOfMultipleEdges[index]->start == end) && (array->listOfMultipleEdges[index]->end == start)))
            {
                array->listOfMultipleEdges[index]->multipleEdges++;
                flag = false;
            }
        }
        if(flag){ // if we haven't found edge in array, we add it
            array->size *= 2;
            array->listOfMultipleEdges = (MultipleEdge **) realloc (array->listOfMultipleEdges,
                                                                    array->size * sizeof(MultipleEdge *));
            array->listOfMultipleEdges[array->numOfEdges] = createElementOfList(start, end);
            array->numOfEdges++;
        }
    }
    fclose(file);
    return array;
}

int main() {
    arrayOfMultipleEdges* listOfMultipleEdges = malloc(sizeof(MultipleEdge*));
    listOfMultipleEdges = countMultipleEdges(listOfMultipleEdges);
    showMultipleEdges(listOfMultipleEdges);
    freeList(listOfMultipleEdges);
    return 0;
}
