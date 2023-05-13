package beadando;

import java.util.concurrent.CountDownLatch;

public class GaussJordanParallel implements Runnable{
	
	private static final double EPSILON = 0.00000000001;
    private final double[][] matrix;
    private final int n;
    private final CountDownLatch latch;
    private final int startRow;
    private final int endRow;

    public GaussJordanParallel(double[][] matrix, int startRow, int endRow, CountDownLatch latch) {
        this.matrix = matrix;
        this.n = matrix.length;
        this.latch = latch;
        this.startRow = startRow;
        this.endRow = endRow;
    }
    
    @Override
    public void run() {
        for (int pivotRow = 0; pivotRow < n; pivotRow++) {
            if (pivotRow >= startRow && pivotRow < endRow) {
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
                    swapRows(pivotRow, maxCoefficientRow);
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
        }
        latch.countDown();
    }

    private void swapRows(int i, int j) {
        double[] temp = matrix[i];
        matrix[i] = matrix[j];
        matrix[j] = temp;
    }

    public static void gaussJordanElimination(double[][] matrix, int numThreads) {
        int n = matrix.length;
        CountDownLatch latch = new CountDownLatch(numThreads);
        Thread[] threads = new Thread[numThreads];

        
        for (int i = 0; i < numThreads; i++) {
            int startRow = i * n / numThreads;
            int endRow = (i + 1) * n / numThreads;
            threads[i] = new Thread(new GaussJordanParallel(matrix, startRow, endRow, latch));
            threads[i].start();
        }

       
        try {
            latch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

       
        if(n < 11) {
            for(int i = 0;i<n;i++) {
            	for(int j = 0; j < n;j++) {
            		System.out.print(matrix[j][i] + " " );
            	}
            	System.out.println();
            	
            }}  
    }
}
