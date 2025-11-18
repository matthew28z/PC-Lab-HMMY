#include "pzhelp"

REAL** matrix;

const int rows = READ_INT();
const int columns = READ_INT();

bool isValid(int val) {
	return (val >= 1 && val <= 100);
}

REAL averageOfList(REAL* list, int length) {
	REAL sum = 0;

	for (int i = 0; i < length; i++) {
		sum += list[i];
	}

	return sum / length;
}

REAL* selectList(int index, bool isRow) {
	REAL* list;
	int length;

	if (isRow) {
		list = NEW(REAL, columns);
		length = columns;

		for (int i = 0; i < columns; i++) {
			list[i] = matrix[index][i];
		}
	} else {
		list = NEW(REAL, rows);
		length = rows;

		for (int i = 0; i < rows; i++) {
			list[i] = matrix[i][index];
		}
	}

	return list;
}

void fillWithAvs(REAL* arrayToFill, int length, bool isRow) {
	int length2;

	if (isRow) {
		length2 = columns;
	} else {
		length2 = rows;
	}

	for (int i = 0; i < length; i++) {
		arrayToFill[i] = averageOfList(selectList(i, isRow), length2);
	}
}

PROGRAM {
	if (isValid(rows) && isValid(columns)) {
		matrix = NEW(REAL*, rows);

		for (int i = 0; i < rows; i++) {
			matrix[i] = NEW(REAL, columns);

			//Passes the values onto the matrix
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = READ_REAL();
			}
		}
		//These will store the average values
		REAL* avOfRows = NEW(REAL, rows);
		fillWithAvs(avOfRows, rows, true);

		REAL* avOfColumns = NEW(REAL, columns);
		fillWithAvs(avOfColumns, columns, false);

		WRITELN(FORM(averageOfList(avOfRows, rows), 0, 3));
		WRITELN(FORM(averageOfList(avOfColumns, columns), 0, 3));

	}
}
