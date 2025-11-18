#include "pzhelp"

//Global
int** matrix;

//Functions
bool goodInput(int val) {
	bool isGood = true;

	if (val < 1 || val > 100) {
		isGood = false;
	}

	return isGood;
}

int compare(int* values, int length, char comp) {
	int result = values[0];

    //skips the first iteration
	for (int i = 1; i < length; i++) {
		const int currentValue = values[i];

		if (comp == '>') {
			if (result < currentValue) {
				result = currentValue;
			}
		} else { //'<'
			if (result > currentValue) {
				result = currentValue;
			}
		}
	}

	return result;
}

void fillCompArray (int* compArray, int compArrayLength, int otherLength, char comp, bool isRow) {
	for (int i = 0; i < compArrayLength; i++) {
		int* other = NEW(int, otherLength);

		//Gemizei to compArray
		for (int j = 0; j < otherLength; j++) {
		    if (isRow) {
		        other[j] = matrix[i][j];
		    } else {
		        other[j] = matrix[j][i];
		    }
			
		}

		compArray[i] = compare(other, otherLength, comp);

		//Katharizei thn mnhmh
		DELETE(other);
	}
}

PROGRAM {
  const int rows = READ_INT();
	const int columns = READ_INT();

	if (goodInput(rows) && goodInput(columns)) {
	    matrix = NEW(int*, rows);
	    
		for (int x = 0; x < rows; x++) {
			matrix[x] = NEW(int, columns);

			for (int y = 0; y < columns; y++) {
				matrix[x][y] = READ_INT();
			}
		}

		int* maxColumns = NEW(int, columns);
		fillCompArray(maxColumns, columns, rows, '>', false);
		
		int* minRows = NEW(int, rows);
		fillCompArray(minRows, rows, columns, '<', true);
		
		WRITELN(compare(maxColumns, columns, '<'));
		WRITELN(compare(minRows, rows, '>'));
	}
}
