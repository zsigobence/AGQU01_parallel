package beadando;

public class GaussJordan {
	private static final double EPSILON = 0.0000000001;
	private final double[][] matrix;
	private final int matrix_length;

	public GaussJordan(double[][] matrix) {
		this.matrix = matrix;
		this.matrix_length = matrix.length;
	}

	public void gaussJordanElimination(int startRow,int endRow) {
		for (int pivotRow = 0; pivotRow < matrix_length; pivotRow++) {
			if (pivotRow >= startRow && pivotRow < endRow) {
			int pivotCol = pivotRow;

			double maxCoefficient = Math.abs(matrix[pivotRow][pivotCol]);
			int maxCoefficientRow = pivotRow;
			for (int i = pivotRow + 1; i < matrix_length; i++) {
				double coefficient = Math.abs(matrix[i][pivotCol]);
				if (coefficient > maxCoefficient) {
					maxCoefficient = coefficient;
					maxCoefficientRow = i;
				}
			}

			if (maxCoefficientRow != pivotRow) {
				swapRows(matrix, pivotRow, maxCoefficientRow);
			}

			double pivotElement = matrix[pivotRow][pivotCol];
			if (Math.abs(pivotElement) < EPSILON) {
				continue;
			}
			for (int j = pivotCol; j < matrix_length; j++) {
				matrix[pivotRow][j] /= pivotElement;
			}

			for (int i = 0; i < matrix_length; i++) {
				if (i != pivotRow) {
					double factor = matrix[i][pivotCol];
					for (int j = pivotCol; j < matrix_length; j++) {
						matrix[i][j] -= factor * matrix[pivotRow][j];
						}
					}
				}
			}
			if (matrix_length < 11) {
				for (int i = 0; i < matrix_length; i++) {
					for (int j = 0; j < matrix_length; j++) {
						System.out.print(matrix[j][i] + " ");
					}
					System.out.println();
				}
			}
		}}

	private static void swapRows(double[][] matrix, int i, int j) {
		double[] temp = matrix[i];
		matrix[i] = matrix[j];
		matrix[j] = temp;
	}
}
