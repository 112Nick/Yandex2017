//a = 1 неактивна
//a = 2 стабильна
//a = 3 нестабильна
// > 1 в стабильном => стабильная
// не первое условие и >= 1 в стабильном или нестабильном =>  нестабильня
// не первое и не второе => неактивная
 #include <iostream>

 int neighboursStable(int** field, int n, int m, int i, int j) {
    int cnt = 0;
    if (i != n - 1) {
        if (field[i + 1][j] == 2) {
            cnt++;
        }
    }
    if (i != 0) {
        if (field[i - 1][j] == 2) {
            cnt++;
        }
    }
    if (j != m - 1) {
        if (field[i][j + 1] == 2) {
            cnt++;
        }
    }
    if (j != 0) {
        if (field[i][j - 1] == 2) {
            cnt++;
        }
    }

    return cnt;
 }

  int neighboursActive(int** field, int n, int m, int i, int j) {
    int cnt = 0;

    if (i != n - 1) {
        if (field[i + 1][j] != 1) {
            cnt++;
        }
    }
    if (i != 0) {
        if (field[i - 1][j] != 1) {
            cnt++;
        }
    }
    if (j != m - 1) {
        if (field[i][j + 1] != 1) {
            cnt++;
        }
    }
    if (j != 0) {
        if (field[i][j - 1] != 1) {
            cnt++;
        }
    }
    return cnt;
 }

 int** game(int** fieldPrev, int n, int m, int k) {
    int** fieldCur = new int* [n];
    for (int i = 0; i < n; i++) {
        fieldCur[i] = new int [m];
    }
    int** result = new int* [n];
    for (int i = 0; i < n; i++) {
        result[i] = new int [m];
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
        }
    }
    for (int x = 0 ; x < k; x++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (neighboursStable(fieldPrev, n, m, i, j) > 1) {
                    fieldCur[i][j] = 2;
                }
                else if (neighboursActive(fieldPrev, n, m, i, j) >= 1) {
                    fieldCur[i][j] = 3;                
                }
                else {
                    fieldCur[i][j] = 1;                
                }
                if(fieldPrev[i][j] != fieldCur[i][j]) {
                    result[i][j]++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) { 
                fieldPrev[i][j] = fieldCur[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        delete[] fieldCur[i];
    }
    delete[] fieldCur;
    return result; 
 }


 int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    int** field = new int* [n];
    for (int i = 0; i < n; i++) {
        field[i] = new int [m];
    } 
    int** result;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> field[i][j];
        }
    }
    result = game(field, n, m ,k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << result[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < n; i++) {
        delete[] field[i];
    }
    delete[] field;
    return 0;
 }
