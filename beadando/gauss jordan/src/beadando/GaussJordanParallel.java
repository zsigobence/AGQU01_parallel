package beadando;

import java.util.concurrent.CountDownLatch;

public class GaussJordanParallel extends GaussJordan implements Runnable {
	
	private final CountDownLatch latch;
	private final int startRow;
	private final int endRow;
	

	public GaussJordanParallel(double[][] matrix, int startRow, int endRow, CountDownLatch latch) {
		super(matrix);
		this.latch = latch;
		this.startRow = startRow;
		this.endRow = endRow;
	}

	@Override
	public void run() {
		gaussJordanElimination(startRow,endRow);
		latch.countDown();
	}

	public static void gaussJordanEliminationParallel(double[][] matrix, int numThreads) {
		int matrix_length = matrix.length;
		CountDownLatch latch = new CountDownLatch(numThreads);
		Thread[] threads = new Thread[numThreads];

		for (int i = 0; i < numThreads; i++) {
			int startRow = i * matrix_length / numThreads;
			int endRow = (i + 1) * matrix_length / numThreads;
			threads[i] = new Thread(new GaussJordanParallel(matrix, startRow, endRow, latch));
			threads[i].start();
		}

		try {
			latch.await();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		if (matrix_length < 11) {
			for (int i = 0; i < matrix_length; i++) {
				for (int j = 0; j < matrix_length; j++) {
					System.out.print(matrix[j][i] + " ");
				}
				System.out.println();
			}
		}
	}
}
