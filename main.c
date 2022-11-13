#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"

// functie pentru calcularea numarului
// de structuri din *arr in functie de lungime
int CountElem(void *arr, int len)
{

    int count = 0;
    int len_gen_cur = 0;
    while (len_gen_cur < len)
    {
        int step;
        memmove(&step, arr + 5 + len_gen_cur, sizeof(int));
        len_gen_cur += 5 + step;
        count++;
    }
    return count;
}

// functia adauga zona de memorie dintr-un data_structure
// la finalul *arr si creste len(marimea in octeti) cu
// marimea lui data
int add_last(void **arr, int *len, data_structure *data)
{
    if (*len == 0)
    {
        *arr = malloc(5 + data->header->len);
    }
    else
    {
        *arr = realloc(*arr, *len + 5 + data->header->len);
    }

    memmove(*arr + *len, &data->header->type, sizeof(char));
    memmove(*arr + *len + 1, &data->header->len, sizeof(int));
    memmove(*arr + *len + 5, data->data, data->header->len);

    *len += 5 + data->header->len;
}

// functia adauga zona de memoria dintr-un data_structure
// dupa un block de memorie (primita ca parametru prin index)
// si creste marimea lui len cu marimea lui data
int add_at(void **arr, int *len, data_structure *data, int index)
{
    int len_gen_cur = 0;

    if (index > CountElem(arr, len))
        len_gen_cur = *len;
    else
    {

        for (int i = 0; i < index; i++)
        {
            unsigned int step;
            memmove(&step, *arr + 1 + len_gen_cur, sizeof(unsigned int));
            len_gen_cur += 5 + step;
        }
    }

    *arr = realloc(*arr, *len + 5 + data->header->len);
    memmove(*arr + len_gen_cur + 5 + data->header->len, *arr + len_gen_cur, *len - len_gen_cur);

    memmove(*arr + len_gen_cur, &data->header->type, sizeof(char));
    memmove(*arr + len_gen_cur + 1, &data->header->len, sizeof(int));
    memmove(*arr + len_gen_cur + 5, data->data, data->header->len);

    *len += 5 + data->header->len;
}

// afiseaza zona de memorie de la index, in formadtul
// specific tipului de data
void find(void *data_block, int len, int index)
{
    int len_gen_cur = 0;
    for (int i = 0; i < index; i++)
    {
        unsigned int step;
        memmove(&step, data_block + 1 + len_gen_cur, sizeof(unsigned int));
        len_gen_cur += 5 + step;
    }

    unsigned char type;
    memmove(&type, data_block + len_gen_cur, sizeof(unsigned char));

    if (type == '1')
    {
        printf("Tipul %c\n", type);
        printf("%s pentru %s\n", data_block + 5 + len_gen_cur, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + 2 * sizeof(int8_t) + len_gen_cur);

        int8_t b1, b2;
        memmove(&b1, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int8_t));
        memmove(&b2, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int8_t), sizeof(int8_t));

        printf("%" PRId8 "\n", b1);
        printf("%" PRId8 "\n\n", b2);
    }
    else if (type == '2')
    {
        printf("Tipul %c\n", type);
        printf("%s pentru %s\n", data_block + 5 + len_gen_cur, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + sizeof(int16_t) + sizeof(int32_t) + len_gen_cur);

        int16_t b1;
        int32_t b2;

        memmove(&b1, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int16_t));
        memmove(&b2, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int16_t), sizeof(int32_t));

        printf("%" PRId16 "\n", b1);
        printf("%" PRId32 "\n\n", b2);
    }
    else if (type == '3')
    {
        int32_t b1, b2;

        printf("Tipul %c\n", type);
        printf("%s pentru %s\n", data_block + 5 + len_gen_cur, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + 2 * sizeof(int32_t) + len_gen_cur);

        memmove(&b1, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int32_t));
        memmove(&b2, data_block + 5 + strlen(data_block + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int32_t), sizeof(int32_t));

        printf("%" PRId32 "\n", b1);
        printf("%" PRId32 "\n\n", b2);
    }
}

// functia sterge o zona de memoria la index
// si o inlocuieste cu memoria ramasa in *arr
// scade marimea lui len si realloca *arr
int delete_at(void **arr, int *len, int index)
{
    int len_gen_cur = 0;
    for (int i = 0; i < index; i++)
    {
        unsigned int step;
        memmove(&step, *arr + 1 + len_gen_cur, sizeof(unsigned int));
        len_gen_cur += 5 + step;
    }

    int len_del;
    memmove(&len_del, *arr + len_gen_cur + 1, sizeof(int));
    len_del += 5;

    memmove(*arr + len_gen_cur, *arr + len_gen_cur + len_del, *len - len_gen_cur - len_del);
    *len -= len_del;
    *arr = realloc(*arr, *len);
}

// printeaza toate structurile sub formatul
// corespunzator tipului
void print(void *arr, int len)
{
    int len_gen_cur = 0;
    while (len_gen_cur < len)
    {
        unsigned char type;
        memmove(&type, arr + len_gen_cur, sizeof(unsigned char));

        if (type == '1')
        {
            printf("Tipul %c\n", type);
            printf("%s pentru %s\n", arr + 5 + len_gen_cur, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + 2 * sizeof(int8_t) + len_gen_cur);

            int8_t b1, b2;
            memmove(&b1, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int8_t));
            memmove(&b2, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int8_t), sizeof(int8_t));

            printf("%" PRId8 "\n", b1);
            printf("%" PRId8 "\n\n", b2);
        }
        else if (type == '2')
        {
            printf("Tipul %c\n", type);
            printf("%s pentru %s\n", arr + 5 + len_gen_cur, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + sizeof(int16_t) + sizeof(int32_t) + len_gen_cur);

            int16_t b1;
            int32_t b2;

            memmove(&b1, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int16_t));
            memmove(&b2, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int16_t), sizeof(int32_t));

            printf("%" PRId16 "\n", b1);
            printf("%" PRId32 "\n\n", b2);
        }
        else if (type == '3')
        {
            int32_t b1, b2;

            printf("Tipul %c\n", type);
            printf("%s pentru %s\n", arr + 5 + len_gen_cur, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + 2 * sizeof(int32_t) + len_gen_cur);

            memmove(&b1, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur, sizeof(int32_t));
            memmove(&b2, arr + 5 + strlen(arr + 5 + len_gen_cur) + 1 + len_gen_cur + sizeof(int32_t), sizeof(int32_t));

            printf("%" PRId32 "\n", b1);
            printf("%" PRId32 "\n\n", b2);
        }
        unsigned int step;
        memmove(&step, arr + 1 + len_gen_cur, sizeof(unsigned int));
        len_gen_cur += 5 + step;
    }
}

// functia citeste valorile intr-un buffer
// si le seprara cu strtok apoi muta memoria
// in variabele corespunzatoare si se calculeaza
// memoria pentru data_block si muta numele si
// bancnotele in data.data
data_structure *GetData()
{
    char *buffer = malloc(256);
    data_structure *data = malloc(sizeof(data_structure));
    scanf("%s", buffer);
    data->header = malloc(sizeof(head));
    data->header->type = *buffer;

    if (data->header->type == '1')
    {
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char *n1, *n2;
        int8_t b1, b2;

        n1 = strtok(buffer, " ");
        b1 = (int8_t)atoi(strtok(NULL, " "));
        b2 = (int8_t)atoi(strtok(NULL, " "));
        n2 = strtok(NULL, " ");

        data->header->len = strlen(n1) + 1 + 2 * sizeof(int8_t) + strlen(n2) + 1;

        data->data = malloc(data->header->len);

        memmove(data->data, n1, strlen(n1) + 1);
        memmove(data->data + strlen(n1) + 1, &b1, sizeof(int8_t));
        memmove(data->data + strlen(n1) + 2, &b2, sizeof(int8_t));
        memmove(data->data + strlen(n1) + 3, n2, strlen(n2) + 1);
    }
    else if (data->header->type == '2')
    {
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char *n1, *n2;
        int16_t b1;
        int32_t b2;

        n1 = strtok(buffer, " ");
        b1 = (int16_t)atoi(strtok(NULL, " "));
        b2 = (int32_t)atoi(strtok(NULL, " "));
        n2 = strtok(NULL, " ");

        data->header->len = strlen(n1) + 1 + sizeof(int16_t) + sizeof(int32_t) + strlen(n2) + 1;

        data->data = malloc(data->header->len);

        memmove(data->data, n1, strlen(n1) + 1);
        memmove(data->data + strlen(n1) + 1, &b1, sizeof(int16_t));
        memmove(data->data + strlen(n1) + 3, &b2, sizeof(int32_t));
        memmove(data->data + strlen(n1) + 7, n2, strlen(n2) + 1);
    }
    else if (data->header->type == '3')
    {
        fgets(buffer, 256, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char *n1, *n2;
        int32_t b1, b2;

        n1 = strtok(buffer, " ");
        b1 = (int32_t)atoi(strtok(NULL, " "));
        b2 = (int32_t)atoi(strtok(NULL, " "));
        n2 = strtok(NULL, " ");

        data->header->len = strlen(n1) + 1 + 2 * sizeof(int32_t) + strlen(n2) + 1;

        data->data = malloc(data->header->len);

        memmove(data->data, n1, strlen(n1) + 1);
        memmove(data->data + strlen(n1) + 1, &b1, sizeof(int32_t));
        memmove(data->data + strlen(n1) + 5, &b2, sizeof(int32_t));
        memmove(data->data + strlen(n1) + 9, n2, strlen(n2) + 1);
    }

    free(buffer);

    return data;
}

int main()
{
    // the vector of bytes u have to work with
    // good luck :)
    void *arr = NULL;
    int len = 0;
    char *buffer = malloc(256);

    // se citeste primul cuvant si se apeleaza functia
    // corespunzatoare. La citirea comenzii exit iese
    // si elibereaza memoria de la buffer si arr
    while (strcmp(buffer, "exit") != 0)
    {
        scanf("%s", buffer);
        if (strcmp(buffer, "insert") == 0)
        {
            data_structure *data = GetData();
            add_last(&arr, &len, data);
            free(data->data);
            free(data->header);
            free(data);
        }
        if (strcmp(buffer, "insert_at") == 0)
        {

            int index;
            scanf("%d", &index);
            data_structure *data = GetData();
            add_at(&arr, &len, data, index);
            free(data->data);
            free(data->header);
            free(data);
        }
        if (strcmp(buffer, "delete_at") == 0)
        {
            int index;
            scanf("%d", &index);
            delete_at(&arr, &len, index);
        }
        if (strcmp(buffer, "find") == 0)
        {
            int index;
            scanf("%d", &index);
            find(arr, len, index);
        }
        if (strcmp(buffer, "print") == 0)
        {
            print(arr, len);
        }
    }

    free(buffer);
    free(arr);

    return 0;
}