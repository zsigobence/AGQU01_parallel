package beadando;


public class GaussJordan {
	private static final double EPSILON = 0.0000000001;
 

    public static void gaussJordanElimination(double[][] matrix) {
        int n = matrix.length;

        for (int pivotRow = 0; pivotRow < n; pivotRow++) {
            int pivotCol = pivotRow;

            
            double maxCoefficient = Math.abs(matrix[pivotRow][pivotCol]);
            int maxCoefficientRow = pivotRow;
            for (int i = pivotRow + 1; i < n; i++) {
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
            for (int j = pivotCol; j < n; j++) {
                matrix[pivotRow][j] /= pivotElement;
            }

           
            for (int i = 0; i < n; i++) {
                if (i != pivotRow) {
                    double factor = matrix[i][pivotCol];
                    for (int j = pivotCol; j < n; j++) {
                        matrix[i][j] -= factor * matrix[pivotRow][j];
                    }
                }
            }
        }
        if(n<11) {
        for(int i = 0;i<n;i++) {
        	for(int j = 0; j < n;j++) {
        		System.out.print(matrix[j][i] + " " );
        	}
        	System.out.println();
        	
        }}
    }

    private static void swapRows(double[][] matrix, int i, int j) {
        double[] temp = matrix[i];
        matrix[i] = matrix[j];
        matrix[j] = temp;
    }

	
}
