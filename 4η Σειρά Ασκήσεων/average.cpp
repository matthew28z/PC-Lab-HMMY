#include "pzhelp"

#include <bits/stdc++.h>
using namespace std;

//Global
REAL** matrix;

//Functions
bool goodInput(int val) {
	bool isGood = true;

	if (val < 1 || val > 100) {
		isGood = false;
	}

	return isGood;
}

REAL* createSubMetrix(int lengthOfSM, int otherLength, bool isRow, int index) {
	REAL* subMatrix = NEW(REAL, lengthOfSM);

	for (int i = 0; i < lengthOfSM; i++) {
		if (isRow) {
			subMatrix[i] = matrix[index][i];
		} else {
			subMatrix[i] = matrix[i][index];
			WRITELN(subMatrix[i], i, index);
		}

	}

	return subMatrix;
}

REAL average(REAL* values, int length) {
	REAL sum = 0;

	for (int i = 0; i < length; i++) {
		sum += values[i];
	}

	return sum / length;
}

void fillMatrix(REAL* matrixToFill, int subMatrixLength, int otherLength, bool isRow) {
	for (int i = 0; i < subMatrixLength; i++) {
		REAL* subMatrix = createSubMetrix(subMatrixLength, otherLength, isRow, i);

		matrixToFill[i] = average(subMatrix, otherLength);

		DELETE(subMatrix);
	}
}

PROGRAM {
	auto start = chrono::high_resolution_clock::now();

	const int rows = READ_INT();
	const int columns = READ_INT();

	if (goodInput(rows) && goodInput(columns)) {
		matrix = NEW(REAL*, rows);

		for (int x = 0; x < rows; x++) {
			matrix[x] = NEW(REAL, columns);

			for (int y = 0; y < columns; y++) {
				matrix[x][y] = READ_REAL();
			}
		}

		REAL* avRows = NEW(REAL, rows);
		fillMatrix(avRows, rows, columns, true);

		for (int j = 0; j < rows; j++) {
			WRITE("ROW");
			WRITE("-");
			WRITE(j);
			WRITE(":", avRows[j], '\n');
		}

		REAL* avColumns = NEW(REAL, columns);
		fillMatrix(avColumns, columns, rows, false);

		for (int j = 0; j < rows; j++) {
			WRITE("COLUMN");
			WRITE("-");
			WRITE(j);
			WRITE(":", avColumns[j], '\n');
		}

		WRITELN(FORM(average(avRows, rows), 0, 3));
		WRITELN(FORM(average(avColumns, columns), 0, 3));
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end - start;

	cerr << "Execution time: " << elapsed.count() << " seconds\n";
}
