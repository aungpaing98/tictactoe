#include <stdio.h>

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }
    return b;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int argmax(int a[], int len_a)
{
    int ret = 0;
    for (int i = 1; i < len_a; i++)
    {
        if (a[i] > a[ret])
        {
            ret = i;
        }
    }
    return ret;
}

int check_input_valid(int available_moves[], int total_available_move, int move_id_)
{
    // Input type : Int, input value in available_moves
    // 0 - invalid input
    // 1 - valid input
    int valid = 0;
    // TODO : Check for string input.
    for (int i = 0; i < total_available_move; i++)
    {
        if (available_moves[i] == move_id_)
        {
            valid = 1;
        }
    }
    return valid;
}