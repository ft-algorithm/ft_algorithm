// 3 * 3 크기의 한 블럭 검사
int isValidArea(char** board, int col, int row, int* hash)
{
    int     col_index;
    int     row_index;
    
    memset(hash, 0, sizeof(int) * 10);
    col_index = -1;
    while (++col_index < 3)
    {
        row_index = -1;
        while (++row_index < 3)
        {
            if (board[col + col_index][row + row_index] == '.')
                continue ;
            if (hash[board[col + col_index][row + row_index] - '0']++ > 0)
                return (0);
        }
    }
    return (1);
}

// (0,0) 부터 시작해서 (1,1).. 대각선 좌표 전달해서 가로/세로 확인
int isValidLine(char** board, int diagonal, int* hash)
{
    int index;
    
    // check row
    memset(hash, 0, sizeof(int) * 10);
    index = -1;
    while (++index < 9)
    {
        if (board[diagonal][index] == '.')
            continue ;
        if(hash[board[diagonal][index] - '0']++ > 0)
            return (0);
    }
    
    // check column
    memset(hash, 0, sizeof(int) * 10);
    index = -1;
    while (++index < 9)
    {
        if (board[index][diagonal] == '.')
            continue ;
        if(hash[board[index][diagonal] - '0']++ > 0)
            return (0);
    }
    return (1);
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    int     col;
    int     row;
    int*    hash;
    
    hash = (int*)calloc(10, sizeof(int));  // 0~9 사용됐는지 체크용
    col = -1;
    while (++col < 3)  // 3 * 3 크기씩 확인
    {
        row = -1;
        while (++row < 3)
        {
            if (!isValidArea(board, 3 * col, 3 * row, hash))
            {
                free(hash);
                return (false);
            }
        }
    }
    col = -1;
    while (++col < 9)
    {
        if (!isValidLine(board, col, hash))
        {
            free(hash);
            return (false);
        }
    }
    return (true);
}