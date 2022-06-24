def reverse_matrix(matrix, umatrix):
    i=0
    for row in matrix:
        #for k in [0,1,2]:
            #print(f"{matrix[k]} | {umatrix[k]}")
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
            #print("")
            #print(f"w{i+1}*{tmp1[i] ** (-1)}")
            #print("~")
            #print("")
            #for k in [0,1,2]:
            #    print(f"{matrix[k]} | {umatrix[k]}")
        #print("")
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
                #print(f"w{j+1} - w{i+1}*{tmp[i]}")
        #print("~")
        #print("")
        i += 1
        #if i == 3:
        #    for k in [0,1,2]:
        #        print(f"{matrix[k]} | {umatrix[k]}")   
    return 0

if __name__ == "__main__":
    alpha = -3
    #print("Wprowadz wartosc alpha z przedzialu [-2, 2]:")
    ranged =  [x * 0.001 for x in range(-2000,2000)]
    #print(ranged)
    for alpha in ranged: 
    #[-2.0,-1.9,-1.8,-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,0.333,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0]:    
        #alpha = float(input())
        matrix = [[1, 0.5, alpha],[0.5, alpha, 0.25],[alpha, 0.25, 0.2]]
        umatrix = []

        for row in matrix:
            tmp = []
            for element in row:
                tmp.append(element)
            umatrix.append(tmp)
        
        max1 = -50
        for column in matrix:
            sum = 0
            for i in [0,1,2]:
                sum += abs(column[i])
            if sum > max1:
                max1 = sum  


        rmatrix = [[1,0,0],[0,1,0],[0,0,1]]
        reverse_matrix(umatrix, rmatrix)

        max2 = -50
        for column in rmatrix:
            sum = 0
            for i in [0,1,2]:
                sum += abs(column[i])
            if sum > max2:
                max2 = sum  
        #print(f"max1 = {max1}, max2= {max2}, max1*max2 = {max1 * max2}")
        if max1 * max2 >= 5000.0:
            print(f"alpha = {alpha}")
            print("")
            print("A = ")
            for row in matrix:
                print(row)
            print("")
            for row in umatrix:
                print(row)
            print("")
            print("A^(-1) = ")
            for row in rmatrix:
                print(row)
            print("")
            print(f"wspolczynnik uwarunkowania = {max1 * max2}")
            print("")
            print("")