#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 3000017  

typedef struct {
    int* keys;
    char* used;
    int count;
} HashSet;

void hashInit(HashSet* hs) {
    hs->keys = (int*)calloc(HASH_SIZE, sizeof(int));
    hs->used = (char*)calloc(HASH_SIZE, sizeof(char));
    hs->count = 0;
}

void hashInsert(HashSet* hs, int val) {
    unsigned int hash = (unsigned int)val % HASH_SIZE;
    while (hs->used[hash]) {
        if (hs->keys[hash] == val) return; 
        hash = (hash + 1) % HASH_SIZE;     
    }
    hs->keys[hash] = val;
    hs->used[hash] = 1;
    hs->count++;
}

void hashFree(HashSet* hs) {
    free(hs->keys);
    free(hs->used);
}

int subarrayBitwiseORs(int* arr, int arrSize) {
    if (arrSize == 0) return 0;

    HashSet total_set;
    hashInit(&total_set);

    int cur_set[32];
    int next_set[32];
    int cur_size = 0;

    for (int i = 0; i < arrSize; i++) {
        int next_size = 0;
 
        next_set[next_size++] = arr[i];
        hashInsert(&total_set, arr[i]);

        for (int j = 0; j < cur_size; j++) {
            int or_val = cur_set[j] | arr[i];
          
            int is_duplicate = 0;
            for (int k = 0; k < next_size; k++) {
                if (next_set[k] == or_val) {
                    is_duplicate = 1;
                    break;
                }
            }
            
            if (!is_duplicate) {
                next_set[next_size++] = or_val;
                hashInsert(&total_set, or_val);
            }
        }

     
        cur_size = next_size;
        for (int j = 0; j < cur_size; j++) {
            cur_set[j] = next_set[j];
        }
    }

    int result = total_set.count;
    hashFree(&total_set);
    
    return result;
}
