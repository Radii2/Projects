def reverse_matrix(matrix, umatrix):
    i=0
    for row in matrix:
        for k in [0,1,2]:
            print(f"{matrix[k]} | {umatrix[k]}")
        if row[i] != 1:
            if row[i] == 0:
                for j in range(len(matrix)):
                    if matrix[j] != row:
                        if matrix[j][i] != 0:
                            matrix[i], matrix[j] = matrix[j], matrix[i]
                            umatrix[i], umatrix[j] = umatrix[j], umatrix[i]
                            break
            else:
                for j in range (len(umatrix[i])):
                    umatrix[i][j] = umatrix[i][j] * (row[i] ** (-1))
                tmp1 = row.copy()
                for j in range(len(row)):
                    row[j] = row[j] * (tmp1[i] ** (-1))
            print("")
            print(f"w{i+1}*{tmp1[i] ** (-1)}")
            print("~")
            print("")
            for k in [0,1,2]:
                print(f"{matrix[k]} | {umatrix[k]}")
        print("")
        for j in range(len(matrix)):
            if j == i:
                continue
            if matrix[j][i] != 0:
                tmp = matrix[j].copy()
                for k in range(len(umatrix[j])):
                    sub = umatrix[i][k] * tmp[i]
                    umatrix[j][k] = umatrix[j][k] - sub
                for k in range(len(matrix[j])):
                    sub = matrix[i][k] * tmp[i]
                    matrix[j][k] = matrix[j][k] - sub
                print(f"w{j+1} - w{i+1}*{tmp[i]}")
        print("~")
        print("")
        i += 1
        if i == 3:
            for k in [0,1,2]:
                print(f"{matrix[k]} | {umatrix[k]}")   
    return 0

if __name__ == "__main__":
    alpha = -3
    print("Wprowadz wartosc alpha z przedzialu [-2, 2]:")
    while alpha < -2 or alpha > 2:    
        alpha = float(input())
    matrix = [[1, 0.5, alpha],[0.5, alpha, 0.25],[alpha, 0.25, 0.2]]
    original_matrix = []
    for row in matrix:
        tmp=[]
        for element in row:
            tmp.append(element)
        original_matrix.append(tmp)

    umatrix = [[1,0,0],[0,1,0],[0,0,1]]
    print("")
    reverse_matrix(matrix, umatrix)
    print("")
    print("A = ")
    for row in original_matrix:
        print(row)
    print("")
    print("A^(-1) = ")
    for row in umatrix:
        print(row)